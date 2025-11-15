#include "gpio.h"
#include "led.h"

void led_init(void)
{
    gpio_setup_pin_direction(1, 4, 1); // set led pin to be output
}

void led_on(void)
{
    gpio_write_pin(1, 4, 1); // Write 1 on led pin to turn it on
}

void led_off(void)
{
    gpio_write_pin(1, 4, 0); // Write 0 on led pin to turn it off 
}