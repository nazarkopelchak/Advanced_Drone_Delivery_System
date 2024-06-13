#ifndef STATION_FACTORY_H_
#define STATION_FACTORY_H_

#include "entity.h"
#include "IEntityFactory.h"
#include "station.h"

#include <vector>

class StationFactory : public IEntityFactory {
  public:
    virtual ~StationFactory() {}
    IEntity* CreateEntity(JsonObject& entity);
};

#endif
