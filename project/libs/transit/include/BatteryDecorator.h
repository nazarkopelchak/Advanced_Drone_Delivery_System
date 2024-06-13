#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include <vector>
#include "CelebrationDecorator.h"
#include "IStrategy.h"

class BatteryDecorator: public CelebrationDecorator {
    public:
        BatteryDecorator(IStrategy *strategy_) : CelebrationDecorator(strategy_) {batteryLevel = 100.0f;}
        bool IsCompleted();
        void Move(IEntity* entity, double dt);
        bool IsDepleted();
        void SetBatteryLevel(float newBatteryLevel);
        float GetBatteryLevel();
    private:
        float batteryLevel;
        //bool charged;
}; //close class 

#endif // BATTERY_DECORATOR_H_
