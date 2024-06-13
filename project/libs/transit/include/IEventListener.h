#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "math/vector3.h"
#include "entity.h"

enum Event {
    DEAD_DRONE
};

class IEventListener {
  public:
    virtual void Update(IEntity* entity) = 0;
    virtual Vector3 GetLocation() = 0;
};

#endif