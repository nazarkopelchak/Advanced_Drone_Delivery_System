#ifndef DEAD_DRONE_LISTENER_H
#define DEAD_DRONE_LISTENER_H

#include "IEventListener.h"
#include "DeliveryDrone.h"

/**
 * @brief For ChargingDrones to determine when DeliveryDrones
 * have died
 */
class DeadDroneListener: public IEventListener {
  public:
    /**
     * @brief Constructor that sets the homeLocation.
     */
    DeadDroneListener(Vector3 location_);
    /**
     * @brief Update the isDead parameter to be true and set
     * the deadDrone field to point to the calling drone
     * 
     * @param deadDrone position of invoking dead drone
     */
    void Update(IEntity* entity);
    /**
     * @brief Reset the listener to await new dead drone updates
     */
    void Reset();
    /**
     * @brief Determine whether or not the drone that is being
     * listened to is dead
     */
    bool GetIsDead();
    /**
     * @brief Get the dead done for communication
     */
    DeliveryDrone* GetDeadDrone();
    /**
     * @brief Get the location of the deadDroneListener's owner
     */
    Vector3 GetLocation();
  private:  
    /**
     * @brief reference to a dead DeliveryDrone
     */
    DeliveryDrone* deadDrone = nullptr;
    /**
     * @brief location of listener's owner 
     */
    Vector3 location;
};

#endif