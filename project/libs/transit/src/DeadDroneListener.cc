#include "../include/DeadDroneListener.h"

DeadDroneListener::DeadDroneListener(Vector3 location_) {
    location = location_;
}


void DeadDroneListener::Update(IEntity* entity) {
    deadDrone = dynamic_cast<DeliveryDrone*>(entity);
}


void DeadDroneListener::Reset() {
    deadDrone = nullptr;
}


bool DeadDroneListener::GetIsDead() {
    return deadDrone != nullptr;
}


DeliveryDrone* DeadDroneListener::GetDeadDrone() {
    return deadDrone;
}


Vector3 DeadDroneListener::GetLocation() {
    return location;
}