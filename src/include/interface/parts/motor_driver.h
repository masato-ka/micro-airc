
#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

namespace airc{

class MotorDriver {
public:
    virtual void init() = 0;
    virtual void cmd(float steering, float throttle) = 0;
    virtual void lock() = 0;
    virtual void stop() = 0;
};

}

#endif


