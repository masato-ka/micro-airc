#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "../include/remote_agent_impl.h"

namespace airc{


void RemoteAgentImpl::onConnect(BLEServer* pServer) {
    printf("connectionCallback\n\r");
};

void RemoteAgentImpl::onDisconnect(BLEServer* pServer) {
  printf("disconnectionCallback\n\r");
};

void RemoteAgentImpl::onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();

    if (value.length() >= 10) {
       printf("Data received: length = %d, data = 0x",value.length());
       for(int x=0; x < value.length(); x++) {
           printf("%02x", value[x]);
       }
       printf("\n\r");
    }
};

void RemoteAgentImpl::initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor){
    this->motorDriver = motorDriver;
    this->rangeSensor = rangeSensor;

    BLEDevice::init("aircmicro");
    
    // Create the BLE Server
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(this);

    // Create the BLE Service
    BLEService *pService = pServer->createService(this->SERVICE_UUID);

    // Create a BLE Characteristic
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                            this->CHARACTERISTIC_UUID,
                                            BLECharacteristic::PROPERTY_WRITE |
                                            BLECharacteristic::PROPERTY_WRITE_NR
                                        );

    pCharacteristic->setCallbacks(this);

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();


};


void RemoteAgentImpl::drive(){
   delay(2000);
};

void RemoteAgentImpl::stop(){
    this->motorDriver->stop();
};

}