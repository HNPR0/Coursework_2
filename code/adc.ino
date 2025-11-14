#include <avr/io.h>
#include "adc.h"

uint16 adc_read_channel(uint8 ch_num)
{
	ADMUX &= 0xE0;
	ADMUX |= (ch_num &(0x07)); // Select ADC channel
	ADCSRA |= (1<<ADSC); // Start conversion
	while (!(ADCSRA & (1<<ADIF))){} // Clear interrupt flag
	ADCSRA |=(1<<4); // ADC Interrupt flag
	return ADC; // Return ADC value
}

void adc_init(void)
{
    ADMUX = (1 << REFS0); // AVCC with external capacitor at AREF
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADC interrupt flag / Prescalar = 128
}
