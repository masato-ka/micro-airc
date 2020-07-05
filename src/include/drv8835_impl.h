#include <Wire.h>
#include "../include/interface/parts/motor_driver.h"
#include "../include/config.h"

#ifndef DRV8835_I_H
#define DRV8835_I_H

namespace airc {


class DRV8835Impl : public MotorDriver {
    public :
        void init();
        void cmd(float steering, float throttle);
        void lock();
        void stop();
};

}
#endif 