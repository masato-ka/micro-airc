#include <Wire.h>
#include <VL53L0X.h>
#include "include/interface/parts/range_sensor.h"

#ifndef RANGE_SENSOR_IMPL_H
#define RANGE_SENSOR_IMPL_H

namespace airc{

class RangeSensorImpl : public RangeSensor{
public:
    RangeSensorImpl();
    int getData(uint16_t* data, int size);
    void setAddress(uint8_t center_address, uint8_t right_address, uint8_t left_address);

private:
    VL53L0X sensors[3];
    void init_sensor(int position, int shut, uint8_t address);
};

}

#endif