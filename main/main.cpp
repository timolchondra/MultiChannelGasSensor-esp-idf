/* Timothy Olchondra
 *
 * This is a test program for the Seeed MultiChannelGasSensor
 * The goal of this program is to port the existing Arduino Library for the
 * sensor into ESP-IDF.
 */



#include <iostream>
#include "MultiChannelGasSensor.h"
#ifdef __cplusplus
extern "C" {
#endif

#include"freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"


#ifdef __cplusplus
}
#endif

MultiChannelGasSensor gas;


extern "C" void app_main(void) {
    gas.begin(0x04);
    gas.powerOn();

    for(int i = 0; i < 50; i++) {
        gas.ledOn();
        vTaskDelay(500/portTICK_RATE_MS);
        gas.ledOff();
        vTaskDelay(500/portTICK_RATE_MS);
    }

}
