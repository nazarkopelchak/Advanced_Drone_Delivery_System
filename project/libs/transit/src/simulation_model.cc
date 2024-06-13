#include "simulation_model.h"
#include "DroneFactory.h"
#include "RobotFactory.h"
#include "StationFactory.h"
#include "Beeline.h"
#include "AstarStrategy.h"


SimulationModel::SimulationModel(IController& controller) : controller(controller){
  compFactory = new CompositeFactory();
  compFactory->AddFactory(new DeliveryDroneFactory());
  compFactory->AddFactory(new ChargingDroneFactory());
  compFactory->AddFactory(new RobotFactory());
  compFactory->AddFactory(new StationFactory());
}

/// Creates a simulation entity
void SimulationModel::CreateEntity(JsonObject& entity) {
    // int id = entity["entityId"];
    std::string type = entity["type"];
    std::string name = entity["name"];
    JsonArray position = entity["position"];
    std::cout << name << ": " << position << std::endl;

    IEntity* myNewEntity = compFactory->CreateEntity(entity);

    ChargingDrone* cDrone = dynamic_cast<ChargingDrone*>(myNewEntity);
    if(cDrone) {
      // add self to a random station
      if (!stations.empty()) {
        std::cout << "Got here" << std::endl;
        int index = (std::rand() % stations.size()); 
        stations.at(index)->AddWorker(cDrone);
        // set home position to be this station
        cDrone->SetHomePosition(stations.at(index)->GetPosition());
      } else {
        // home position should be the starting location of the drone if there is no station
        cDrone->SetHomePosition(cDrone->GetPosition());
      }
      
     DeadDroneListener* deadDroneListener = new DeadDroneListener(cDrone->GetHomePosition());
     cDrone->AddDeadDroneListener(deadDroneListener);
      
      // subscribe to all delivery drones' DEAD_DRONE event
      for (DeliveryDrone* deliveryDrone : deliveryDrones) {
        deliveryDrone->Subscribe(DEAD_DRONE, deadDroneListener);
      }

      chargingDrones.push_back(cDrone);
    }

    myNewEntity->SetGraph(graph);
    // Add to the drone dictionary
    DeliveryDrone* dDrone = dynamic_cast<DeliveryDrone*>(myNewEntity);
    if(dDrone) {
      deliveryDrones.push_back(dDrone);
    }

 
    // Add to the robot dictionary
    Robot* robot = dynamic_cast<Robot*>(myNewEntity);
    if(robot) {
      robots.push_back(robot);
    }
    //Add station to station dictionary
    Station* station = dynamic_cast<Station*>(myNewEntity);
    if(station) {
      stations.push_back(station);
    }
    // Call AddEntity to add it to the view
    controller.AddEntity(*myNewEntity);
    entities.push_back(myNewEntity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
    std::string name = details["name"];
    JsonArray start = details["start"];
    JsonArray end = details["end"];
    std::cout << name << ": " << start << " --> " << end << std::endl;

    for(auto entity : entities){  // Add the entity to the scheduler
      JsonObject detailsTemp = entity->GetDetails();
      std::string nameTemp = detailsTemp["name"];
      std::string typeTemp = detailsTemp["type"];
      if(name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 && entity->GetAvailability()){
        std::string strategyName = details["search"];
        entity->SetStrategyName(strategyName);
        entity->SetDestination(Vector3(end[0], end[1], end[2]));
        scheduler.push_back(entity);
        break;
      }
    }
    controller.SendEventToView("TripScheduled", details);
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
    // Call controller to update changed entities
    for (int i = 0; i < entities.size(); i++) {
      entities[i]->Update(dt, scheduler);
      controller.UpdateEntity(*entities[i]);
    }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
