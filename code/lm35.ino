#include "lm35.h"
#include "adc.h"
#include <avr/io.h>

uint8 lm35_get_temp()
{
  	uint8 temp_value = 0; // Set initial temp value to zero

  	uint16 adc_value = 0; // Set initial adc value to zero

  	adc_value = adc_read_channel(LM35_ANALOGUE_CHANNEL); //Read LM35 ADC value from channel 1

	// Calculate temperature value from ADC reading 
  	temp_value = (uint8)(((uint32)adc_value*150*5)/(1023*1.5));

  	return temp_value; // Return Temp value
}