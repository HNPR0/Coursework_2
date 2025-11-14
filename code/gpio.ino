#include "gpio.h"
#include <avr/io.h>

void gpio_setup_pin_direction(uint8 port_num, uint8 pin_num, uint8 direction)
{
	switch(port_num)
	{
	case 1:
		if(direction == 1)
		{
			SET_BIT(DDRB,pin_num);
		}
		else
		{
			CLEAR_BIT(DDRB,pin_num);
		}
		break;
	case 2:
		if(direction == 1)
		{
			SET_BIT(DDRC,pin_num);
		}
		else
		{
			CLEAR_BIT(DDRC,pin_num);
		}
		break;
	case 3:
		if(direction == 1)
		{
			SET_BIT(DDRD,pin_num);
		}
		else
		{
			CLEAR_BIT(DDRD,pin_num);
		}
		break;
	}
}

void gpio_write_pin(uint8 port_num, uint8 pin_num, uint8 value)
{
   	if(value == 1)
    {
    	switch(port_num)
    	{
    	case 1:
    		SET_BIT(PORTB,pin_num); 
    		break;
    	case 2:
    		SET_BIT(PORTC,pin_num);
    		break;
    	case 3:
    		SET_BIT(PORTD,pin_num);
    		break;
    	}
    }
    else
    {
    	switch(port_num)
    	{
    	case 1:
    		CLEAR_BIT(PORTB,pin_num);
    		break;
    	case 2:
    		CLEAR_BIT(PORTC,pin_num);
    		break;
    	case 3:
    		CLEAR_BIT(PORTD,pin_num);
    		break;
    	}
    }
}


uint8 gpio_read_pin(uint8 port_num, uint8 pin_num)
{
    uint8 pin_value = 0;
	switch(port_num)
	{
	    case 1:
	    	if(BIT_IS_SET(PINB,pin_num))
	    	{
	    		pin_value = 1;
	    	}
	    	else
	    	{
	    		pin_value = 0;
	    	}
	    	break;
	    case 2:
	    	if(BIT_IS_SET(PINC,pin_num))
	    	{
	    		pin_value = 1;
	    	}
	    	else
	    	{
	    		pin_value = 0;
	    	}
	    	break;
	    case 3:
	    	if(BIT_IS_SET(PIND,pin_num))
	    	{
	    		pin_value = 1;
	    	}
	    	else
	    	{
	    		pin_value = 0;
	    	}
	    	break;
	}
    return pin_value;
}

void gpio_setup_port_direction(uint8 port_num, uint8 direction)
{
	switch(port_num)
	{
	case 1:
		DDRB = direction;
		break;
	case 2:
		DDRC = direction;
		break;
	case 3:
		DDRD = direction;
		break;
	}
}


void gpio_write_port(uint8 port_num, uint8 value)
{
	switch(port_num)
	{
	case 1:
		PORTB = value;
		break;
	case 2:
		PORTC = value;
		break;
	case 3:
		PORTD = value;
		break;
	}
}


uint8 gpio_read_port(uint8 port_num)
{
	uint8 value = 0;
	switch(port_num)
	{
	case 1:
		value = PINB;
		break;
	case 2:
		value = PINC;
		break;
	case 3:
		value = PIND;
		break;
	}
	return value;
}
