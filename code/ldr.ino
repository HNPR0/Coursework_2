#include <avr/io.h>
#include "ldr.h"

void ldr_init(void)
{
    adc_init(); // initialize ADC
}

uint16 ldr_get_light_intensity(void)
{

    // Read ADC value from LDR channel
    uint16 adcValue = adc_read_channel(LDR_ANALOGUE_CHANNEL);

    // Convert ADC value to voltage
    float voltage = ((float)adcValue / 1023) * 5;

    // Inverse relationship: higher voltage = lower light intensity
    float intensity = (1.0 - (voltage / 5)) * 100;

    // Set limit to the result between 0 and 100
    if (intensity < 0)
        intensity = 0;
    if (intensity > 100)
        intensity = 100;

    return (uint16)intensity;
}