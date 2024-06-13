#include "BatteryDecorator.h"

bool BatteryDecorator::IsCompleted(){
    if (batteryLevel > 100.0f) {batteryLevel == 100.0f;}
    return batteryLevel == 100.0f;
}

bool BatteryDecorator::IsDepleted(){
    if (batteryLevel < 0.0f) {batteryLevel = 0.0f;}
    return batteryLevel == 0.0f;
}

void BatteryDecorator::Move(IEntity* entity, double dt){
    if(!IsDepleted()) {
        batteryLevel -= dt;
        strategy->Move(entity, dt);
    }
}

void BatteryDecorator::SetBatteryLevel(float newBatteryLevel) {batteryLevel == newBatteryLevel;}

float BatteryDecorator::GetBatteryLevel() {return batteryLevel;}
