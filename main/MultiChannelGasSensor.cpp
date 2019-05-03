/* Timothy Olchondra
 * This code is meant to re write the existing library for the Seeed MultichannelGasSensor
 * for the ESP32 using ESP-IDF
 *
 *
 */

#include <math.h>
#include "MultiChannelGasSensor.h"
#include <iostream>
#include "esp_task.h"
#include "driver/i2c.h"

using namespace std;
/*Function name:            begin
 *Description:              intialize I2C
 */

void MultiChannelGasSensor::begin(int address) {
    __version = 1;
    r0_inited = false;
    init_i2c();
    i2cAddress = address;
    __version = 1; 

}
unsigned char MultiChannelGasSensor::getVersion() {
    if(get_addr_dta(CMD_READ_EEPROM, ADDR_IS_SET) == 1126) {
        __version = 1;
        printf("version = 2\n");
        return 2;
    }

    __version = 1;
    printf("version = 1\n");
    return 1;

}

static void init_i2c() {
    i2c_port_t i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = (gpio_num_t) I2C_SDA_PIN;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = (gpio_num_t) I2C_SCL_PIN;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_SPEED_STANDARD;
  
    i2c_param_config((i2c_port_t) i2c_master_port, &conf);
  
    i2c_driver_install(i2c_master_port, conf.mode,
                    I2C_MASTER_RX_BUF_DISABLE,
                    I2C_MASTER_TX_BUF_DISABLE, 0);
}
void MultiChannelGasSensor::begin() {
    begin(DEFAULT_I2C_ADDR);
}
/* Function: sendI2C
 * Description: send one byte to I2C Wire
 *
 */

esp_err_t MultiChannelGasSensor::sendI2C(unsigned char dta) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DEFAULT_I2C_ADDR << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, (uint8_t)dta, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000/ portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;

}

unsigned int MultiChannelGasSensor::get_addr_dta(unsigned char addr_reg) {
    unsigned int dta = 0;
    unsigned char raw[10];

    sendI2C(addr_reg);

   //now request from the address
   //Read two bytes from the slave and store it into raw (some buffer with arbitrary size 10)
    esp_err_t ret = i2c_master_read_slave(raw, 2);
    if(ret != ESP_OK) {
        printf("I2C READ FAILED...%d\n", ret);
        return -1;
    }

   //now store those two bytes into an unsigned int, dta 
    dta = raw[0];
    dta <<= 8;
    dta += raw[1];

    switch(addr_reg) {
        case CH_VALUE_NH3:
            if(dta > 0) {
                adcValueR0_NH3_Buf = dta;
            } else {
                dta = adcValueR0_NH3_Buf;
            }
            break;
        case CH_VALUE_CO:
            if (dta > 0) {
                adcValueR0_CO_Buf = dta;
            } else {
                dta = adcValueR0_CO_Buf;
            }
            break;
        case CH_VALUE_NO2:
            if (dta > 0) {
                adcValueR0_NO2_Buf = dta;
            } else {
                dta = adcValueR0_NO2_Buf;
            }
            break;
        default:;

    }
    return dta;

}

unsigned int MultiChannelGasSensor::get_addr_dta(unsigned char addr_reg, unsigned char __dta) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DEFAULT_I2C_ADDR << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, addr_reg, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, __dta, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000/portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
   
    if (ret != ESP_OK)
        return -1;
    
    unsigned int dta = 0;
    unsigned char raw[10];

    ret = i2c_master_read_slave(raw, 2);

    if (ret != ESP_OK)
        return -1;

    dta = raw[0];
    dta <<= 8;
    dta += raw[1];

    return dta;
}
int16_t MultiChannelGasSensor::readData(uint8_t cmd) {
    uint16_t timeout = 0;
    uint8_t buffer[4];
    uint8_t checksum = 0;
    int16_t rtnData = 0;

    sendI2C(cmd);
    vTaskDelay(2);

    i2c_master_read_slave(buffer, 4);

    checksum = (uint8_t)(buffer[0] + buffer[1] + buffer[2]);
    if(checksum != buffer[3])
        return -4; //checksum wrong

    rtnData = ((buffer[1] << 8) + buffer[2]);

    return rtnData;

}
void MultiChannelGasSensor::write_i2c(unsigned char addr, unsigned char* dta, unsigned char dta_len) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write(cmd, dta, dta_len, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000/portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

}


void MultiChannelGasSensor::powerOn() {
    if(__version == 1)
        sendI2C(0x21);

}


static esp_err_t i2c_master_read_slave(uint8_t *data_rd, size_t size)
{
    if (size == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DEFAULT_I2C_ADDR << 1) | READ_BIT, ACK_CHECK_EN);
    if (size > 1) {
        i2c_master_read(cmd, data_rd, size - 1, (i2c_ack_type_t)ACK_VAL);
    }
    i2c_master_read_byte(cmd, data_rd + (size - 1), (i2c_ack_type_t)NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
