#include "button.h"
#include <avr/io.h>
#include "adc.h"
#include <util/delay.h>

char analogue_button_read(void)
{
    uint16 adc_val = adc_read_channel(0); // Read ADC channel 0 to get button press value
    _delay_ms(50); // Debounce delay

    // Each button corresponds to a specific voltage range
    // Return character based on the voltage range
    if (adc_val < 50)
        return 'R'; // Right
    else if (adc_val < 195)
        return 'U'; // Up
    else if (adc_val < 380)
        return 'D'; // Down
    else if (adc_val < 555)
        return 'L'; // Left
    else if (adc_val < 790)
        return 'S'; // Select
    else
        return 0; // None
}