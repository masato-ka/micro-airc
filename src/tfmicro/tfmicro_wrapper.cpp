#include "../include/tfmicro_wrapper.h"

namespace airc{

void TfMicroWrapper::initialize(){
    static tflite::MicroErrorReporter micro_error_reporter;
    this->error_reporter = &micro_error_reporter;
    
    this->model = ::tflite::GetModel(converted_model_tflite);
    if (this->model->version() != TFLITE_SCHEMA_VERSION) {
        this->error_reporter->Report(
            "Model provided is schema version %d not equal "
            "to supported version %d.",
            this->model->version(), TFLITE_SCHEMA_VERSION);
        return;
    }
    
    static tflite::ops::micro::AllOpsResolver resolver;
    
    static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena,
                                        kTensorArenaSize, error_reporter);
    this->interpreter = &static_interpreter;
    
    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = this->interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        this->error_reporter->Report("AllocateTensors() failed");
        return;
    }
};


TfLiteTensor* TfMicroWrapper::getInput(){
    return this->interpreter->input(0);
};

TfLiteTensor* TfMicroWrapper::getOutput(){
    return this->interpreter->output(0);
};


void TfMicroWrapper::invoke(){
    TfLiteStatus invoke_status = this->interpreter->Invoke();
    if (invoke_status != kTfLiteOk) {
        this->error_reporter->Report("Invoke failed on 1.: %f\n",
                            static_cast<double>(1.));
        return;
    }
};



}
