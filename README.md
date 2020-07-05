# airc-micro

## Overview

airc-micro is most tiny AI RC Car project. No camera, no powerful cpu and AI accelerator.

Using simple distance sensor and cheap cpu board such as ESP32, STM32F1xx.

NN is learning on cloud. And deploy to microcontroller by [tensorflow lite for microcontroller](https://www.tensorflow.org/lite/microcontrollers).

## Install 

Now, this software target is ESP32-WROOM-D. You can use Arduino IDE.

### Install Library

Install [Arduino_TensorFlowLite_ESP32](https://github.com/tanakamasayuki/Arduino_TensorFlowLite_ESP32).

## Usage

### NN learning on Google Colaboratory.

[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/masato-ka/micro-airc/blob/tools/airc_micro_tensorflow_keras.ipynb)

You can using simple_airccar_simulation_tensorflow_keras.ipynb. Open notebook with colab. This notebook simulate airc-micro. and running model training. At end of notebook you can download trained model as model of TensorFlow lite for microcontoroller .

Simulation version is here:
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/masato-ka/micro-airc/blob/tools/simple_airccar_simulation_tensorflow_keras.ipynb)

### Deploy model file

Replace micro-airc/src/model/airc_model.cpp with the download file.

### Compile and Write to Board

Open airc-micro.ino with Arduino IDE. Build projects and Write to target board.

## Release note

Now is experimental project. If you interest to this project. Please contact me.

## Contribution

If you find bug or want to new functions, please write issue.
If you fix your self, please fork and send pull request.

## LICENSE

his software license under MIT licence.

## Autor 

[masato-ka](https://github.com/masato-ka/airc-rl-agent)