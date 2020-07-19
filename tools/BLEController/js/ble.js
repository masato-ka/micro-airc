const BLESerialServiceUUID = "6e400001-b5a3-f393-e0a9-e50e24dcca9e" 
const TxUUID = "6e400002-b5a3-f393-e0a9-e50e24dcca9e"
const RxUUID = "6e400003-b5a3-f393-e0a9-e50e24dcca9e"

let bleDevice
let deviceService;
let txCharacteristic;
let rxCharacteristic;

let isConnect = false;

let arrayBuffer = new ArrayBuffer(8)
 
            
let driving_log = []


function connectDevice(){
    navigator.bluetooth.requestDevice(
        {acceptAllDevices:true, optionalServices:[BLESerialServiceUUID] }
    ).then(device=>{
        bleDevice = device
        return device.gatt.connect()
    }).then(server=>server.getPrimaryService(BLESerialServiceUUID))
    .then(service=>{
        service.getCharacteristic(TxUUID).then(characteristic=>txCharacteristic=characteristic)
        service.getCharacteristic(RxUUID).then(characteristic=>{
            rxCharacteristic = characteristic;
            characteristic.addEventListener('characteristicvaluechanged', onRecvSensorData);
            characteristic.startNotifications();
        })
        isConnect = true;
    })    
}

function disconnectDevice(){
    isConnect = false;
    rxCharacteristic.removeEventListener('characteristicvaluechanged', onRecvSensorData)
    bleDevice.gatt.disconnect()
}

function onRecvSensorData(event){
    var characteristic = event.target;
    var value = characteristic.value;
    driving_log.push([value.getUint16(0, true),value.getUint16(2, true),value.getUint16(4, true),
            value.getFloat32(6, true), value.getFloat32(10, true)])
    console.log(value.getUint16(0, true)+', '+value.getUint16(2, true)+', '+value.getUint16(4, true))
    console.log(value.getFloat32(6, true)+', '+value.getFloat32(10, true))
}

        
