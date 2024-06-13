#include "../include/IChargeableEntity.h"
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

IChargeableEntity::IChargeableEntity(JsonObject obj, float maxBattery_) : details(obj) { 
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];

    state = AWAITING;
    batteryLevel = maxBattery_;
    maxBattery = maxBattery_;
}


void IChargeableEntity::Rotate(double angle){
    direction.x = direction.x*std::cos(angle) - direction.z*std::sin(angle);
    direction.z = direction.x*std::sin(angle) + direction.z*std::cos(angle);
}


bool IChargeableEntity::Charge(float amount) {
    batteryLevel += amount;

    if (batteryLevel >= maxBattery) {
        batteryLevel = maxBattery;
        state = CHARGING_COMPLETE;
        std::cout << name << ": charging completed." << std::endl;
        return true;
    }
    PrintProgress(batteryLevel/maxBattery);
    return false;
}


void IChargeableEntity::PrintProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("%s: %3d%% [%.*s%*s]\n", name.c_str(), val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}