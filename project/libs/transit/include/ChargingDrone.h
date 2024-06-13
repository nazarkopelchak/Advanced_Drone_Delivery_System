#ifndef CHARGING_DRONE_H_
#define CHARGING_DRONE_H_

#include "util/json.h"
#include "IChargeableEntity.h"
#include "math/vector3.h"
#include "IStrategy.h"
#include "DeadDroneListener.h"

#include <vector>

class ChargingDrone : public IChargeableEntity {
public:
    ChargingDrone(JsonObject obj);

    ~ChargingDrone();

    void AddDeadDroneListener(DeadDroneListener* deadDroneListener) { deadDroneListeners.push_back(deadDroneListener); }

    void Update(double dt, std::vector<IEntity*> scheduler);

    Vector3 GetHomePosition() { return homePos; }
    void SetHomePosition(Vector3 homePosition) { homePos = homePosition; }

private:
    void DoWork(double dt);
    void ScheduleCharging();
    void ChargeDeadDrone(double dt);

    Vector3 homePos;

    IStrategy* toDronePosStrategy = nullptr;
    IStrategy* toStationStrategy = nullptr;

    std::vector<DeadDroneListener*> deadDroneListeners;
    DeadDroneListener* activeListener = nullptr;
};

#endif
