#include "../include/drv8835_impl.h"

namespace airc{

void DRV8835Impl::init(){
// Initialize motor driver
    ledcSetup(0, 490, RESOLUTION);
    ledcSetup(1, 490, RESOLUTION);
    ledcSetup(2, 960, RESOLUTION);
    ledcSetup(3, 960, RESOLUTION);
    ledcAttachPin(STEERING_MOTOR_CH1, 0);
    ledcAttachPin(STEERING_MOTOR_CH2, 1);
    ledcAttachPin(THROTTLE_MOTOR_CH1, 2);
    ledcAttachPin(THROTTLE_MOTOR_CH2, 3);
}

void DRV8835Impl::cmd(float steering, float throttle){
    if(1.0 < steering || steering < -1.0){
        return;
    }

    if(1.0 < throttle || throttle < -1.0){
        return;
    }
    
    int steering_value = abs((int)(255 * steering));
    int throttle_value = abs((int)(255 * throttle));

    if(steering > 0){
        ledcWrite(0, steering_value);
        ledcWrite(1, 0);
    }else{
        ledcWrite(0, 0);
        ledcWrite(1, steering_value);
    }

    if(throttle > 0){
        ledcWrite(2, throttle_value);
        ledcWrite(3, 0);
    }else{        
        ledcWrite(2, 0);
        ledcWrite(3, throttle_value);
    }

}

void DRV8835Impl::lock(){
    int value = 255;
    ledcWrite(0, value);
    ledcWrite(1, value);
    ledcWrite(2, value);
    ledcWrite(3, value);
}

void DRV8835Impl::stop(){
    ledcWrite(0, 0);
    ledcWrite(1, 0);
    ledcWrite(2, 0);
    ledcWrite(3, 0);
}


}