#include "../parts/motor_driver.h"
#include "../parts/range_sensor.h"

#ifndef I_AGENT
#define I_AGENT
namespace airc{

class Agent{
public:
    virtual void initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor) = 0;
    virtual void drive() = 0;
    virtual void stop() = 0 ;
};

}

#endif