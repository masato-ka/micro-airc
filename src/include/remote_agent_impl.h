#include <string.h>//memcpy
#include "interface/agent/agent.h"
#include "interface/parts/motor_driver.h"
#include "interface/parts/range_sensor.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#ifndef REMOTE_AGENT_IMPL_H
#define REMOTE_AGENT_IMPL_H

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


namespace airc{
class RemoteAgentImpl : public Agent, public BLEServerCallbacks, public BLECharacteristicCallbacks{
public:
    void initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor);
    void drive();
    void stop();
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);
    void onWrite(BLECharacteristic *pCharacteristic);
private:

    BLEServer* pServer = nullptr;
    BLEService *pService = nullptr;
    BLECharacteristic* txCharacteristic = nullptr;
    BLECharacteristic* rxCharacteristic = nullptr;
    bool deviceConnected = false;
    bool oldDeviceConnected = false;
//    BLEUUID SERVICE_UUID        = BLEUUID((uint16_t)0xFFF0);  // RCBController Service UUID
//    BLEUUID CHARACTERISTIC_UUID = BLEUUID((uint16_t)0xFFF1);  // RCBController Characteristic UUID
    MotorDriver* motorDriver;
    RangeSensor* rangeSensor;
    uint8_t txValue=0;
    float current_steering = 0.0;
    float current_throttle = 0.0;
};
}


#endif