#include "interface/agent/agent.h"
#include "interface/parts/motor_driver.h"
#include "interface/parts/range_sensor.h"
#include <TensorFlowLite_ESP32.h>
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "model/airc_model.h"

#ifndef NN_AGENT_IMPL_H
#define NN_AGENT_IMPL_H

namespace airc{
class NNAgentImpl : public Agent {
public:
    void initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor);
    void setModel(tflite::MicroInterpreter* interpreter, tflite::ErrorReporter* error_reporter);
    void drive();
    void stop();
private:
    tflite::MicroInterpreter* interpreter = nullptr;
    tflite::ErrorReporter* error_reporter = nullptr;
    TfLiteTensor*  input = nullptr;
    TfLiteTensor*  output = nullptr;
    MotorDriver* motorDriver;
    RangeSensor* rangeSensor;
};

}


#endif