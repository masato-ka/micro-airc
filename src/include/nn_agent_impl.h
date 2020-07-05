#include "interface/agent/agent.h"
#include "interface/parts/motor_driver.h"
#include "interface/parts/range_sensor.h"
#include "tfmicro_wrapper.h"
#ifndef NN_AGENT_IMPL_H
#define NN_AGENT_IMPL_H

namespace airc{
class NNAgentImpl : public Agent {
public:
    void initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor);
    void initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor, TfMicroWrapper* tfMicroWrapper);
    void setModel(tflite::MicroInterpreter* interpreter, tflite::ErrorReporter* error_reporter);
    void drive();
    void stop();
private:
    tflite::MicroInterpreter* interpreter = nullptr;
    tflite::ErrorReporter* error_reporter = nullptr;
    TfLiteTensor*  input = nullptr;
    TfLiteTensor*  output = nullptr;
    MotorDriver* motorDriver = nullptr;
    RangeSensor* rangeSensor = nullptr;
    TfMicroWrapper* tfMicroWrapper = nullptr;

};

}


#endif