#ifndef STATION_H_
#define STATION_H_

#include "entity.h"
#include "math/vector3.h"
#include "IChargeableEntity.h"

#include <vector>

// Represents a station in a physical system.

class Station : public IEntity {
public:
    //  are created with a name
    Station(JsonObject obj);
    // Destructor
    ~Station();

    // Gets the  position
    Vector3 GetPosition() const { return position; }

    Vector3 GetDirection() const { return direction; }

    Vector3 GetDestination() const { return Vector3(); }

    JsonObject GetDetails() const { return details; }

    float GetSpeed() const {return 0;}

    bool GetAvailability() const {return true;}

    std::string GetStrategyName() const {return NULL;}

    // Removing the copy constructor and assignment operator
    // so that  cannot be coppied.
    Station(const Station& station) = delete;
    Station& operator=(const Station& station) = delete;

    void Update(double dt, std::vector<IEntity*> scheduler);

    void AddWorker(IChargeableEntity* worker) { workers.push_back(worker); }

private:
    JsonObject details;
    Vector3 position;
    Vector3 direction;
    
    std::vector<IChargeableEntity*> workers;
};

#endif
