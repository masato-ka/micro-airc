#ifndef CONFIG_H
#define CONFIG_H

namespace airc{

// DRV8835 motor settings.
const int STEERING_MOTOR_CH1 = 04;
const int STEERING_MOTOR_CH2 = 26;
const int THROTTLE_MOTOR_CH1 = 27;
const int THROTTLE_MOTOR_CH2 = 25;
const int RESOLUTION = 8;
const int FREQ = 312;

//VL53L0X RangeSensor settings.
const int SHUT0 = 19;
const int SHUT1 = 18;
const int SHUT2 = 05;
const int LEFT_SENSOR = 0;
const int CENTER_SENSOR = 1;
const int RIGHT_SENSOR = 2;
const uint8_t LEFT_SENSOR_ADDRESS = 20;
const uint8_t CENTER_SENSOR_ADDRESS = 21;
const uint8_t RIGHT_SENSOR_ADDRESS = 22;

//Mode
const String AGENT_NAME="ragent";// ragent, pidagent or nnagent.
const String BLUETOOTH_SUFFIX="AircMicro";

}

#endif