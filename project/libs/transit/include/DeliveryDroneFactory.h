#ifndef DELIVERY_DRONE_FACTORY_H_
#define DELIVERY_DRONE_FACTORY_H_

#include "entity.h"
#include "IEntityFactory.h"
#include "DeliveryDrone.h"

#include <vector>

class DeliveryDroneFactory : public IEntityFactory {
  public:
    virtual ~DeliveryDroneFactory() {}
    IEntity* CreateEntity(JsonObject& entity);
};

#endif
