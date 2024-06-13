#ifndef CHARGING_DRONE_FACTORY_H_
#define CHARGING_DRONE_FACTORY_H_

#include "entity.h"
#include "IEntityFactory.h"
#include "ChargingDrone.h"

#include <vector>

class ChargingDroneFactory : public IEntityFactory {
  public:
    virtual ~ChargingDroneFactory() {}
    IEntity* CreateEntity(JsonObject& entity);
};

#endif
