#include "station.h"
#include <cmath>
#include <limits>

Station::Station(JsonObject obj) : details(obj) {
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};
}


Station::~Station() {
    // Delete dynamically allocated variables
}


void Station::Update(double dt, std::vector<IEntity*> scheduler) {
    for (IChargeableEntity* worker : workers) {
        if (worker->GetState() == DEAD) {
            worker->Charge(0.5);
        }
    }
}