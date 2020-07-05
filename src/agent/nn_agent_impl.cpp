#include "../include/nn_agent_impl.h"


namespace airc{

    void NNAgentImpl::initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor){
        this->motorDriver = motorDriver;
        this->rangeSensor = rangeSensor;
    }

    void NNAgentImpl::initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor, TfMicroWrapper* tfMicroWrapper){
        this->initialize(motorDriver, rangeSensor);
        //Loading NN Model
        this->tfMicroWrapper = tfMicroWrapper;
        this->input = this->tfMicroWrapper->getInput();
        this->output = this->tfMicroWrapper->getOutput();
    };

    void NNAgentImpl::drive(){
        uint16_t data[3] = {0,0,0};
        this->rangeSensor->getData(data, 3);
        float left = ((float)data[0]-min_value)/(max_value-min_value);
        float center = ((float)data[1]-min_value)/(max_value-min_value);
        float right = ((float)data[2]-min_value)/(max_value-min_value);
  
        this->input->data.f[0]=left ;// left
        this->input->data.f[1]=center;// center
        this->input->data.f[2]=right;// right

        this->tfMicroWrapper->invoke();

        float label_acc[3] = {this->output->data.f[0],this->output->data.f[1],this->output->data.f[2]};
        float max = label_acc[0];
        //Getting most high number label.
        int result = 0;
        for(int i=1; i < 3; i++){
            if(max < label_acc[i]){
            max = label_acc[i];
            result = i;
            }
        }

        motorDriver->cmd((float)(result-1) ,1.0);
    };

    void NNAgentImpl::stop(){
        this->motorDriver->stop();
    };


}