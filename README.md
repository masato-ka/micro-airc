# airc-micro

## Overview

airc-micro is most tiny AI RC Car project. No camera, no powerful cpu and AI accelerator.

Using simple distance sensor and cheap cpu board such as ESP32, STM32F1xx.

NN is learning on cloud. And deploy to microcontroller by [tensorflow lite for microcontroller](https://www.tensorflow.org/lite/microcontrollers).

## Install 

Now, this software target is ESP32-WROOM-D. You can use Arduino IDE.

### Install Library

* [Arduino_TensorFlowLite_ESP32](https://github.com/tanakamasayuki/Arduino_TensorFlowLite_ESP32).
* [Polol VL53L0X Library](https://github.com/pololu/vl53l0x-arduino).

## Usage


### Collect training data.

1. Enable to PidAgent

Setting pidagent to config.h AGENT_NAME.

```
const String AGENT_NAME="pidagent";
const String BLUETOOTH_SUFFIX="AircMicro";
```

Then build and flush to Your own car.

2. Collect Data

Your car send telemetry data by Bluetooth Serial. Connect to the ESP32 from your laptop. And run below command.

```
$ python tools/logger.py -p <BluetoothSerial port> -f <Path to save training data>
```

### NN learning on Google Colaboratory.

[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/masato-ka/micro-airc/blob/master/tools/airccar_micro_tensorflow_keras.ipynb)

You can using airccar_micro_tensorflow_keras.ipy nb for training. This notebook train NN with your own dataset. Open notebook with colab. Then upload your traing dataset. And You run all cells. At end of notebook you can download trained model as model of TensorFlow lite for microcontoroller.  Further get min_value and max_value for using to normalization.

Simulation version is here:
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/masato-ka/micro-airc/blob/master/tools/simple_airccar_simulation_tensorflow_keras.ipynb)

### Deploy model file

Replace micro-airc/src/model/airc_model.cpp with the download file. And overwrite min_value and max_value in airc_model.h

### Compile and Write to Board

Setting nnagent to config.h AGENT_NAME.

```
const String AGENT_NAME="nnagent";
const String BLUETOOTH_SUFFIX="AircMicro";
```
Then build and flush to your ESP32.

## Release note

Now is experimental project. If you interest to this project. Please contact me.

## Contribution

If you find bug or want to new functions, please write issue.
If you fix your self, please fork and send pull request.

## LICENSE

his software license under MIT licence.

## Special Thanks.

* RumiCar Projects.
* TensorFlow lite for microcontroller
* Arduino_TensorFlowLite_ESP32 by tanakamasayuki

## Autor 

[masato-ka](https://github.com/masato-ka/airc-rl-agent)