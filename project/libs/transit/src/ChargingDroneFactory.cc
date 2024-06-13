#include "ChargingDroneFactory.h"

IEntity* ChargingDroneFactory::CreateEntity(JsonObject& entity){
  std::string type = entity["type"];
  if (type.compare("charging_drone") == 0) {
    ChargingDrone* chargingDrone = new ChargingDrone(entity);
    std::cout << "Charging Drone Created" << std::endl;
    return chargingDrone;
  }
  return nullptr;
}
