#include "ChargingDrone.h"
#include "AstarStrategy.h"
#include "DeliveryDrone.h"

#define CHARGE_TRANSFER 0.1
#define CHARGING_DRONE_NAME "ChargingDrone"

ChargingDrone::ChargingDrone(JsonObject obj): IChargeableEntity(obj, 500.0f) {  
    name = CHARGING_DRONE_NAME;
}

ChargingDrone::~ChargingDrone() {
    for (DeadDroneListener* deadDroneListener : deadDroneListeners) {
        delete deadDroneListener;
    }
}

void ChargingDrone::Update(double dt, std::vector<IEntity*> scheduler) {
    switch (state) {
        case AWAITING:
            // check all listeners for a dead drone
            for (DeadDroneListener* deadDroneListener : deadDroneListeners) {
                if (deadDroneListener->GetIsDead()) {
                    activeListener = deadDroneListener;
                    ScheduleCharging();
                    break;
                }
            }
            break;
        case WORKING:
            DoWork(dt);
            break;
        case DEAD:
            // await another ChargingDrone or be charged by station
            break;
        case CHARGING_COMPLETE:
            if (toDronePosStrategy || toStationStrategy) {
                // drone died while working
                state = WORKING;
            } else {
                // drone is charging after returning home
                state = AWAITING;
            }
            break;
    }
}


void ChargingDrone::DoWork(double dt) {
    if (batteryLevel <= 0) {
        state = DEAD;
        std::cout << "Charging Drone Battery is Dead" << std::endl;
        return;
    }
    if (toDronePosStrategy) {  
        // Move charging drone toward the delivery drone's position
        if (toDronePosStrategy->IsCompleted()) { 
            // Charging drone is at delivery drone's postion
            ChargeDeadDrone(dt);
        } else {  
            // Move to delivery drone's position
            toDronePosStrategy->Move(this, dt);
            batteryLevel -= 0.01f;
        }
    } else if (toStationStrategy) { 
        // Move charging drone back to the charging station
        if(toStationStrategy->IsCompleted()){
            delete toStationStrategy;
            toStationStrategy = nullptr;
            state = DEAD;
        } else {
            toStationStrategy->Move(this, dt);
            batteryLevel -= 0.01f;
        }
    }
    std::cout << "ChargingDrone battery: " << batteryLevel << std::endl;
}


void ChargingDrone::ScheduleCharging() {
    DeliveryDrone* deadDrone = activeListener->GetDeadDrone();

    SetDestination(deadDrone->GetPosition());
    toDronePosStrategy = new AstarStrategy(position, deadDrone->GetPosition(), graph);
    state = WORKING;
}


void ChargingDrone::ChargeDeadDrone(double dt) {
    bool isCharged = activeListener->GetDeadDrone()->Charge(CHARGE_TRANSFER); 
    batteryLevel -= CHARGE_TRANSFER;
    this->Rotate(dt);     

    // deliveryDrone is done charging
    if (isCharged) { 
        // clean up
        delete toDronePosStrategy;
        toDronePosStrategy = nullptr;
        activeListener->Reset();
        activeListener = nullptr;
        // return to station
        toStationStrategy = new AstarStrategy(position, homePos, graph);
    }
}