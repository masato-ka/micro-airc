#include "../include/range_sensor_impl.h"
#include "../include/config.h"
namespace airc{


RangeSensorImpl::RangeSensorImpl(){
    pinMode(SHUT0, OUTPUT);
    pinMode(SHUT1, OUTPUT);
    pinMode(SHUT2, OUTPUT);
    Wire.begin();
}

void RangeSensorImpl::setAddress(uint8_t center_address, uint8_t right_address, uint8_t left_address){
    digitalWrite(SHUT0, LOW);
    digitalWrite(SHUT1, LOW);
    digitalWrite(SHUT2, LOW);
    delay(150);
    this->init_sensor(LEFT_SENSOR, SHUT0,  CENTER_SENSOR_ADDRESS);
    this->init_sensor(CENTER_SENSOR, SHUT1,  RIGHT_SENSOR_ADDRESS);
    this->init_sensor(RIGHT_SENSOR, SHUT2,  LEFT_SENSOR_ADDRESS);
}

void RangeSensorImpl::init_sensor(int position, int shut, uint8_t address){
  //seonsor0
  pinMode(shut, INPUT);
  delay(150);
  this->sensors[position].init(true);
  delay(100);
  this->sensors[position].setAddress(address);
  this->sensors[position].setTimeout(500); 
  this->sensors[position].setMeasurementTimingBudget(20000);
}


int RangeSensorImpl::getData(uint16_t* data, int size){
    if(size < 3){ return -1; }
    for(int i=0; i < 3; i++){
        data[i] = this->sensors[i].readRangeSingleMillimeters();
        if(this->sensors[i].timeoutOccurred()){
            return i;
        }
    }
    return size;
}

}