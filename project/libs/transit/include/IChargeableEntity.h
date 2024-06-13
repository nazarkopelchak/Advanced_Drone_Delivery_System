#ifndef ICHARGEABLE_ENTITY_H
#define ICHARGEABLE_ENTITY_H

#include "entity.h"


enum EntityState {
    AWAITING,
    DEAD,
    CHARGING_COMPLETE,
    WORKING
};

class IChargeableEntity: public IEntity {
  public:

    IChargeableEntity(JsonObject obj, float maxBattery_);

    ~IChargeableEntity() {};

    virtual void Update(double dt, std::vector<IEntity*> scheduler) = 0;

    float GetBatteryLevel() { return batteryLevel; }

    Vector3 GetPosition() const { return position; }

    Vector3 GetDirection() const { return direction; }
    
    Vector3 GetDestination() const { return destination; }

    JsonObject GetDetails() const { return details; }
    
    float GetSpeed() const {return speed;}

    bool GetAvailability() const {return state == AWAITING;}

    std::string GetStrategyName() const {return strategyName;}

    EntityState GetState() {return state;}

    void SetPosition(Vector3 pos_) { position = pos_; }

    void SetDirection(Vector3 dir_) { direction = dir_; }

    void SetDestination(Vector3 des_) { destination = des_;}

    void SetStrategyName(std::string strategyName_) { strategyName = strategyName_;}
  
    void Rotate(double angle);

    void Dock();

    void Undock();

    /**
     * @brief Charge the entity
     * 
     * @param amount the amount to increment batteryLevel by
     * @return whether or not battery is full
     */
    bool Charge(float amount);

protected:
    void PrintProgress(double percentage);

    JsonObject details;
    Vector3 position;
    Vector3 direction;
    Vector3 destination;
    float speed;
    std::string strategyName;
    std::string name;

    EntityState state;
    float maxBattery;
    float batteryLevel;
};

#endif