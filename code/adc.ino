#include <avr/io.h>
#include "adc.h"

uint16 adc_read_channel(uint8 ch_num)
{
	ADMUX &= 0xE0;
	ADMUX |= (ch_num &(0x07));
	ADCSRA |= (1<<ADSC);
	while (!(ADCSRA & (1<<ADIF))){}
	ADCSRA |=(1<<4);
	return ADC;
}

void adc_init(void)
{
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
