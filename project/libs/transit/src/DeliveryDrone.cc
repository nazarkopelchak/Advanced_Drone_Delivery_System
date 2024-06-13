#include "DeliveryDrone.h"
#include "Beeline.h"
#include "AstarStrategy.h"
#include "DijkstraStrategy.h"
#include "DfsStrategy.h"
#include "SpinDecorator.h"

void DeliveryDrone::GetNearestEntity(std::vector<IEntity*> scheduler) {
    float minDis = std::numeric_limits<float>::max();
    for(auto entity : scheduler){
        if(entity->GetAvailability()){
            float disToEntity = this->position.Distance(entity->GetPosition());
            if(disToEntity <= minDis){
                minDis = disToEntity;
                nearestEntity = entity;
            }
        }
    }
    if(nearestEntity){                            // Set strategy for the nearest entity
        nearestEntity->SetAvailability(false);    // set availability to the entity that the drone is picking up
        state = WORKING;                          // set this drone state to WORKING
        SetDestination(nearestEntity->GetPosition());
        toTargetPosStrategy = new Beeline(this->GetPosition(), nearestEntity->GetPosition());
        std::string targetStrategyName = nearestEntity->GetStrategyName();
        if(targetStrategyName.compare("beeline") == 0){
            toTargetDesStrategy = new Beeline(nearestEntity->GetPosition(), nearestEntity->GetDestination());
        } else if (targetStrategyName.compare("astar") == 0){
            toTargetDesStrategy = new AstarStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
        } else if (targetStrategyName.compare("dfs") == 0){
            toTargetDesStrategy = new DfsStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
        } else if (targetStrategyName.compare("dijkstra") == 0){
            toTargetDesStrategy = new DijkstraStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
        } else {
            // If none of the strategy name matched, use beeline as default.
            toTargetDesStrategy = new Beeline(nearestEntity->GetPosition(), nearestEntity->GetDestination());
        }
    }
}

void DeliveryDrone::Update(double dt, std::vector<IEntity*> scheduler) {
    switch (state) {
        case AWAITING:
            GetNearestEntity(scheduler);
            break;
        case WORKING:
            DoWork(dt);
            break;
        case DEAD:
            // ChargingDrone will come and charge you
            break;
        case CHARGING_COMPLETE:
            // can only die while working. Charging is complete so finish work
            state = WORKING;
            DoWork(dt);
            break;
    }
}


void DeliveryDrone::DoWork(double dt) {
    if (batteryLevel <= 0) {
        state = DEAD;
        eventManager.NotifyClosest(DEAD_DRONE, this);
        return;   
    }

    if (toTargetPosStrategy) {  // Move drone toward the entity's position
        toTargetPosStrategy->Move(this, dt);
        batteryLevel -= 0.01f;
        if(toTargetPosStrategy->IsCompleted()){
            delete toTargetPosStrategy;
            toTargetPosStrategy = NULL;
        }
    } else if (toTargetDesStrategy) { // Move drone and entity toward the entity's destination
        toTargetDesStrategy->Move(this, dt);
        batteryLevel -= 0.02f;
        nearestEntity->SetPosition(this->GetPosition());
        nearestEntity->SetDirection(this->GetDirection());
        if(toTargetDesStrategy->IsCompleted()){
            delete toTargetDesStrategy;
            toTargetDesStrategy = NULL;
            state = AWAITING;
            nearestEntity = NULL;
        }
    }
    std::cout << "Delivery Drone Battery Level: " << batteryLevel << std::endl;
}


void DeliveryDrone::Subscribe(Event event, IEventListener* listener) { 
    eventManager.Subscribe(event, listener); 
}


void DeliveryDrone::Unsubscribe(Event event, IEventListener* listener) { 
    eventManager.Unsubscribe(event, listener); 
}