# Grove Multichannel Gas Sensor for ESP32

This project is meant to rewrite the existing Grove multichannel gas sensor, that is written for the Arduino, into ESP-IDF for the ESP32. Anyone who uses ESP-IDF for the ESP32
will be able to use this code to use this sensor.

## Getting Started

You would need a ESP32 and a Grove Multichannel Gas Sensor for this code.

### Prerequisites

You need to install ESP-IDF to get started. Here is a guide to get started: https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html

### Installing

Here are the steps to install:

```
git clone https://github.com/timolchondra/MultiChannelGasSensor-esp-idf.git


make menuconfig         //edit some configurations with your ESP32.

make flash monitor
```

