#include "StationFactory.h"

IEntity* StationFactory::CreateEntity(JsonObject& entity){
  std::string type = entity["type"];
  if(type.compare("station") == 0){
    Station* stationTemp = new Station(entity);
    std::cout << "Station Created" << std::endl;
    return stationTemp;
  }
  return nullptr;
}
