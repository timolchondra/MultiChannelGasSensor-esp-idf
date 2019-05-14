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

#define TASK_STACK_DEPTH    2048

using namespace std;

MultiChannelGasSensor gas;

void grove_task(void *args) {
    float c;

    while(1) {
        c = gas.measure_CO();
        printf("The concentration of CO: ");
        if(c>=0)
            printf("%f ppm\n",c);
        else
            printf("invalid\n");

        c = gas.measure_NH3();
        printf("The concentration of NH3: ");
        if(c>=0)
            printf("%f ppm\n", c);
        else
            printf("invalid\n");

        c = gas.measure_NO2();
        printf("The concentration of NO2: ");
        if(c>=0)
            printf("%f ppm\n", c);
        else
            printf("invalid\n");

        c = gas.measure_C3H8();
        printf("The concentration of C3H8: ");
        if(c>=0)
            printf("%f ppm\n", c);
        else
            printf("invalid\n");

        c = gas.measure_C4H10();
        printf("The concentration of C4H10: ");
        if(c>=0)
            printf("%f ppm\n", c);
        else
            printf("invalid\n");

        c = gas.measure_CH4();
        printf("The concentration of CH4: ");
        if(c>=0)
            printf("%f ppm\n",c);
        else
            printf("invalid\n");

        c = gas.measure_H2();
        printf("The concentration of H2: ");
        if(c>=0)
            printf("%f ppm\n", c);
        else
             printf("invalid\n");

        c = gas.measure_C2H5OH();
        printf("The concentration of C2H5OH: ");
        if(c>=0)
            printf("%f ppm\n", c);
        else
            printf("invalid\n");
        
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}
extern "C" void app_main(void) {
    gas.begin(0x04);
    gas.powerOn();
    
    xTaskCreate(grove_task, "grove_task", TASK_STACK_DEPTH, NULL, 2, NULL);

}
