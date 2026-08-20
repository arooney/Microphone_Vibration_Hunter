/**
Using KY-037 microphone module on a raspberry pico via the ADC.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "pico/binary_info.h"

#define ADC_NUM 0
#define ADC_PIN (26 + ADC_NUM)
#define ADC_VREF 3.3
#define ADC_RANGE (1 << 12)
#define ADC_CONVERT (ADC_VREF / (ADC_RANGE - 1))

int main() {
    stdio_init_all();
    printf("Microphone on..\n");

    adc_init();
    adc_gpio_init( ADC_PIN);
    adc_select_input( ADC_NUM);

    uint adc_raw;
    while (1) {
        adc_raw = adc_read(); // raw voltage from ADC
        absolute_time_t next = get_absolute_time(); // using accurate timing
        printf("%llu, %.2f\n", next, adc_raw * ADC_CONVERT);
        
        next = delayed_by_ms(next, 10);
        sleep_until(next);
    }
}
// Use python code to save data from serial monitor as it arrives.
