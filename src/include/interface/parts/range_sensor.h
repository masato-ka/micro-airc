#include <Wire.h>

#ifndef RANGE_SENSOR
#define RANGE_SENSOR

namespace airc{

class RangeSensor {
public :
    virtual int getData(uint16_t* data, int size) = 0;
    virtual void setAddress(uint8_t center_address, uint8_t right_address, uint8_t left_address) = 0;
};

}

#endif