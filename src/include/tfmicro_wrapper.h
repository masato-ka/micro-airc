#include <TensorFlowLite_ESP32.h>
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

#include "model/airc_model.h"

#ifndef TFMICRO_WRAPPER_H
#define TFMICRO_WRAPPER_H

namespace airc{

class TfMicroWrapper{
public:
    void initialize();
    TfLiteTensor* getInput();
    void invoke();
    TfLiteTensor* getOutput();
private:
  tflite::ErrorReporter* error_reporter = nullptr;
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input = nullptr;
  TfLiteTensor* output = nullptr;
  int inference_count = 0;
  const int kTensorArenaSize = 2 * 1024;
  uint8_t tensor_arena[2 * 1024];

};

}
#endif