#include "DeliveryDroneFactory.h"

IEntity* DeliveryDroneFactory::CreateEntity(JsonObject& entity){
  std::string type = entity["type"];
  if(type.compare("delivery_drone") == 0){
    DeliveryDrone* droneTemp = new DeliveryDrone(entity);
    std::cout << "Delivery Drone Created" << std::endl;
    return droneTemp;
  }
  return nullptr;
}
