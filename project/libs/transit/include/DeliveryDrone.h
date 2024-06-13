#ifndef DELIVERY_DRONE_H_
#define DELIVERY_DRONE_H_

#include "util/json.h"
#include "entity.h"
#include "math/vector3.h"
#include "IStrategy.h"
#include "IChargeableEntity.h"
#include "EventManager.h"

#include <vector>

class DeliveryDrone : public IChargeableEntity {
public:
    DeliveryDrone(JsonObject& obj) : IChargeableEntity(obj, 100.0f) {
        name = "DeliveryDrone";
    }

    void Update(double dt, std::vector<IEntity*> scheduler);
    void GetNearestEntity(std::vector<IEntity*> scheduler);

    void Subscribe(Event event, IEventListener* listener);
    void Unsubscribe(Event event, IEventListener* listener);

    ~DeliveryDrone() override = default;

private:
    void DoWork(double dt);

    IStrategy* toTargetPosStrategy = NULL;
    IStrategy* toTargetDesStrategy = NULL;
    IEntity* nearestEntity = NULL;

    EventManager eventManager;
};

#endif
