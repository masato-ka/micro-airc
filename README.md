# airc-micro

## 1. Overview

airc-micro is most tiny AI RC Car project. No camera, no powerful cpu and AI accelerator.

Using simple distance sensor and cheap cpu board such as ESP32, STM32F1xx.

NN is learning on cloud. And deploy to microcontroller by [tensorflow lite for microcontroller](https://www.tensorflow.org/lite/microcontrollers).

## 2. Requirement

* Hardware
    * Target MCU: ESP32-DevKit
    * Controller: USB Game pad

* Software
    * Develop Environment: [VisualStudio Code](https://azure.microsoft.com/ja-jp/products/visual-studio-code/) + [PlatformIO](https://platformio.org/)
    * Web browser: Google Chrome(Latest)

* Cloud
    * Cloud Environment: [Google coraboratoly](https://colab.research.google.com/notebooks/welcome.ipynb)



## 3. Install

### 3-1. Install VSCode and Platform IO

Setup VisualStudio Code in your PC. And then install PlatformIO plugin to VSCode.
See in [here](https://platformio.org/install/ide?install=vscode)

### 3-2. Libraly install

Install these libraries by using [library manager](https://docs.platformio.org/en/latest/librarymanager/)

* [Pololu VL53L0X](https://github.com/pololu/vl53l0x-arduino?utm_source=platformio&utm_medium=piohome)
* [Arduino_TensorFlowLite_ESP32](https://github.com/tanakamasayuki/Arduino_TensorFlowLite_ESP32).

### 3-3. Clone this project

Clone this repository and open top directory with VSCode.

## 4. Usage


### 4-1. Collect training data.

1. Enable to Agent

Setting remote_agent to config.h AGENT_NAME.

```
const String AGENT_NAME="remote_agent";
const String BLUETOOTH_SUFFIX="AircMicro";
```

Then build and flush to Your own car.

2. Collect Data

Your car send telemetry data by  Bluetooth Serial. Connect to the ESP32 from your laptop. And run below command.

```
$ python tools/logger.py -p <BluetoothSerial port> -f <Path to save training data>
```

### 4-2. NN learning on Google Colaboratory.

[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/masato-ka/micro-airc/blob/master/tools/airccar_micro_tensorflow_keras.ipynb)

You can using airccar_micro_tensorflow_keras.ipy nb for training. This notebook train NN with your own dataset. Open notebook with colab. Then upload your traing dataset. And You run all cells. At end of notebook you can download trained model as model of TensorFlow lite for microcontoroller.  Further get min_value and max_value for using to normalization.

Simulation version is here:
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/masato-ka/micro-airc/blob/master/tools/simple_airccar_simulation_tensorflow_keras.ipynb)

### 4-3. Deploy model file

Replace micro-airc/src/model/airc_model.cpp with the download file. And overwrite min_value and max_value in airc_model.h

### 4-4. Compile and Write to Board

Setting nnagent to config.h AGENT_NAME.

```
const String AGENT_NAME="nnagent";
const String BLUETOOTH_SUFFIX="AircMicro";
```
Then build and flush to your ESP32.

## 5. Release note

Now, This is experimental project. If you interest to this project. Please contact me.

## 6. Contribution

If you find bug or want to new functions, please write issue.

If you fix your self, please fork and send pull request.

## 7. LICENSE

This software license under MIT licence.

## 8. Special Thanks.

* RumiCar Projects.
* TensorFlow lite for microcontroller
* Arduino_TensorFlowLite_ESP32 by tanakamasayuki

## 9. Author 

[masato-ka](https://github.com/masato-ka/airc-rl-agent)