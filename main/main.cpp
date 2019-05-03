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
    float c;

    while(1) {
        c = gas.measure_CO();
        printf("CO: %f ppm\n", c);

        vTaskDelay(500/portTICK_RATE_MS);


    }

}
