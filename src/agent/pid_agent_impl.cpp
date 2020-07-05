#include "../include/pid_agent_impl.h"

namespace airc{
BluetoothSerial SerialBT;
const float LEFT = 1.0;
const float  RIGHT = -1.0;
const int DIFF = 50;

void PidAgentImpl::initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor){
    this->motorDriver = motorDriver;
    this->rangeSensor = rangeSensor;
    SerialBT.begin(BLUETOOTH_SUFFIX);
};


void PidAgentImpl::drive(){
    uint16_t data[3] = {0,0,0};
    this->rangeSensor->getData(data, 3);
    float nu = 1.0;
    int value = data[2]-data[0];
    float omega = 0.0;
    if(abs(value) > 50){
       omega = value > 0.0 ? LEFT : RIGHT;
    }
    this->motorDriver->cmd(omega, nu);
    SerialBT.print(data[0]);SerialBT.print(",");
    SerialBT.print(data[1]);SerialBT.print(",");
    SerialBT.print(data[2]);SerialBT.print(",");
    SerialBT.print(omega);SerialBT.print(",");
    SerialBT.println(nu);
};

void PidAgentImpl::stop(){
    this->motorDriver->stop();
};

}