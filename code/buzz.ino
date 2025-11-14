#include "gpio.h"
#include "buzz.h"

void buzz_init(void)
{
    gpio_setup_pin_direction(1, 5, 1);// set buzzer pin to be output 
}

void buzz_on(void)
{
    gpio_write_pin(1, 5, 1); //write 1 on buzzer pin to turn it on
}

void buzz_off(void)
{
    gpio_write_pin(1, 5, 0); //wite 0 on buzzer pin to turn it on 
}