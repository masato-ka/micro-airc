#include <Wire.h>
#include "config.h"
#include "BluetoothSerial.h"
#include "interface/agent/agent.h"
#include "interface/parts/motor_driver.h"
#include "interface/parts/range_sensor.h"


#ifndef PID_AGENT_IMPL_H
#define PID_AGENT_IMPL_H

namespace airc{
class PidAgentImpl : public Agent {
public:
    void initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor);
    void drive();
    void stop();
private:
    MotorDriver* motorDriver;
    RangeSensor* rangeSensor;
};

}


#endif