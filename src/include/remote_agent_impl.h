#include "interface/agent/agent.h"
#include "interface/parts/motor_driver.h"
#include "interface/parts/range_sensor.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#ifndef REMOTE_AGENT_IMPL_H
#define REMOTE_AGENT_IMPL_H

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
    BLEUUID SERVICE_UUID        = BLEUUID((uint16_t)0xFFF0);  // RCBController Service UUID
    BLEUUID CHARACTERISTIC_UUID = BLEUUID((uint16_t)0xFFF1);  // RCBController Characteristic UUID
    MotorDriver* motorDriver;
    RangeSensor* rangeSensor;
};
}


#endif