#include "../include/remote_agent_impl.h"

namespace airc{


void RemoteAgentImpl::onConnect(BLEServer* pServer) {
    printf("connectionCallback\n\r");
    this->deviceConnected = true;
};

void RemoteAgentImpl::onDisconnect(BLEServer* pServer) {
    printf("disconnectionCallback\n\r");
    this->deviceConnected = false;
};

void RemoteAgentImpl::onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();

    if(rxValue.length() == 8){
        const char* rxbuf = rxValue.c_str();
        this->current_throttle = *((float*) rxbuf);
        this->current_steering = *((float*) (rxbuf+4));
        this->motorDriver->cmd(this->current_steering*-1.0, this->current_throttle);
    }

    
};

void RemoteAgentImpl::initialize(MotorDriver* motorDriver, RangeSensor* rangeSensor){
    this->motorDriver = motorDriver;
    this->rangeSensor = rangeSensor;

    BLEDevice::init("aircmicro");
    
    // Create the BLE Server
    this->pServer = BLEDevice::createServer();
    this->pServer->setCallbacks(this);

    // Create the BLE Service
    this->pService = pServer->createService(SERVICE_UUID);

    // Create a setup txCharacteristic
    this->txCharacteristic = pService->createCharacteristic(
                                            CHARACTERISTIC_UUID_TX,
                                            BLECharacteristic::PROPERTY_NOTIFY
                                        );
    this->txCharacteristic->addDescriptor(new BLE2902());
    // Setup a rxCharacteritic
    this->rxCharacteristic = pService->createCharacteristic(
                                            CHARACTERISTIC_UUID_RX,
                                            BLECharacteristic::PROPERTY_WRITE
                                        );

    this->rxCharacteristic->setCallbacks(this);

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();


};


void RemoteAgentImpl::drive(){
    if (this->deviceConnected) {
        //send sensorvalue
        uint16_t data[3] = {0,0,0};
        this->rangeSensor->getData(data, 6);
        unsigned char bytes[14];
        memcpy(bytes,data,6);
        memcpy((bytes+6), &(this->current_steering), 4);
        memcpy((bytes+10), &(this->current_throttle), 4);
        this->txCharacteristic->setValue(bytes,14);
        this->txCharacteristic->notify();
		delay(10); // bluetooth stack will go into congestion, if too many packets are sent
	  }

    // disconnecting
    if (!this->deviceConnected && this->oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        this->pServer->startAdvertising(); // restart advertising
        this->oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (this->deviceConnected && !this->oldDeviceConnected) {
		// do stuff here on connecting
        this->oldDeviceConnected = this->deviceConnected;
    }


};

void RemoteAgentImpl::stop(){
    this->motorDriver->stop();
};

}