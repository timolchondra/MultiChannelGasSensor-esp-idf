# Grove Multichannel Gas Sensor for ESP32

This project is meant to rewrite the existing Grove multichannel gas sensor, that is written for the Arduino, into ESP-IDF for the ESP32. Anyone who uses ESP-IDF for the ESP32
will be able to use this code to use this sensor.

## Getting Started

You would need a ESP32 and a Grove Multichannel Gas Sensor for this code.

### Prerequisites

You need to install ESP-IDF to get started. Here is a guide to get started: [Get Started With ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html)

### Installing

Here are the steps to install:

```
git clone https://github.com/timolchondra/MultiChannelGasSensor-esp-idf.git

make menuconfig         //edit some configurations with your ESP32.

make flash monitor
```
### Functions that were implemented so far:

```
begin(int address);
begin();
getVersion();
changeI2CAddr(uint8_t newAddr);
powerOn(void);
powerOff(void);
doCalibrate(void);
get_addr_dta(unsigned char addr_reg);
get_addr_dta(unsigned char addr_reg, unsigned char __dta);
write_i2c(unsigned char addr, unsigned char *dta, unsigned char dta_len);
sendI2C(unsigned char dta);
readData(uint8_t cmd);
readR0(void);
readR(void);
calcGas(int gas);           //includes all the gas calculations
getR0(unsigned char ch);
getRs(unsigned char ch);
```

### Functions that I haven't written

```
display_eeprom();
factory_setting();
change_i2c_address(unsigned char addr);
```
