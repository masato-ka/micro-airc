#include <Arduino.h>
#include "include/interface/parts/motor_driver.h"
#include "include/drv8835_impl.h"
#include "include/interface/parts/range_sensor.h"
#include "include/range_sensor_impl.h"
#include "include/interface/agent/agent.h"
#include "include/pid_agent_impl.h"
#include "include/remote_agent_impl.h"
#include "include/agent_factory_impl.h"

#include <TensorFlowLite_ESP32.h>
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

#include "model/airc_model.h"

namespace {
  tflite::ErrorReporter* error_reporter = nullptr;
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input = nullptr;
  TfLiteTensor* output = nullptr;
  int inference_count = 0;
  
  // Create an area of memory to use for input, output, and intermediate arrays.
  // Finding the minimum value for your model may require some trial and error.
  constexpr int kTensorArenaSize = 2 * 1024;
  uint8_t tensor_arena[kTensorArenaSize];
} 

airc::MotorDriver* motorDriver = nullptr; 
airc::RangeSensor* rangeSensor = nullptr;
airc::Agent* agent = nullptr;

void setup() {

  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;
  
  model = ::tflite::GetModel(converted_model_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report(
        "Model provided is schema version %d not equal "
        "to supported version %d.",
        model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }
  
  static tflite::ops::micro::AllOpsResolver resolver;
  
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena,
                                     kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;
  
  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    error_reporter->Report("AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);

  // Keep track of how many inferences we have performed.
  inference_count = 0;

  Serial.begin(115200);
  Serial.print(input->dims->size);
  Serial.print(input->dims->data[0]);
  Serial.print(input->dims->data[1]);

  // //Imlplements to factory class(MotorFactory).
  Serial.println("Initialize motor driver");
  motorDriver = new airc::DRV8835Impl();
  motorDriver->init();

  // //Imlplements to factory class(SensorFactory).
  Serial.println("Initialize range sensor");
  rangeSensor = new airc::RangeSensorImpl();
  rangeSensor->setAddress((uint8_t)21,(uint8_t)22,(uint8_t)20);

  //Imlplements to factory(AgentFactory).
  Serial.println("Initialize Agent");
  String agent_name = airc::AGENT_NAME;
  if(!strcmp(agent_name.c_str(), "nnagent")){
    agent = new airc::NNAgentImpl();
    ((airc::NNAgentImpl*)agent)->setModel(interpreter, error_reporter);
  }else{
    agent = new airc::PidAgentImpl();
  }
  agent->initialize(motorDriver, rangeSensor);


}

void loop() {
  Serial.println("Loop");
  agent->drive();
}
