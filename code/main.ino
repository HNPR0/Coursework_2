#include <avr/io.h>
#include "lm35.h"
#include <util/delay.h>
#include "lcd.h"
#include "led.h"
#include "ldr.h"
#include "button.h"



char intensity[] = "Intens: ";
char temp[] = "Temp: ";
char lower[] = "LL:";
char upper[] = "LH:";
char ok[] = "OK ";
char nok[] = "NOK";

uint8 temp_ubound = 45; // Upper bound for temperature
uint8 temp_lbound = 15; // Lower bound for temperature
uint8 temp_value;

uint8 ldr_ubound = 80; // Upper bound for LDR
uint8 ldr_lbound = 30; // Lower bound for LDR
uint16 ldr_value;

char button_val; // Variable to store button value

uint8 mode = 0; // 0 for Temperature mode, 1 for LDR mode

int main(void)
{
    led_init();     // Initialize LED
    buzz_init();    // Initialize buzzer
    ldr_init();     // Initialize LDR
    lcd_init();      // Initialize LCD

    _delay_ms(500); // Give time for Serial Monitor to connect
    
    while(1)
    {
        button_val = analogue_button_read();    // Read analogue button value

        if (button_val == 'S') // Select button to switch modes
        {
            mode = !mode; // Toggle mode between 0 and 1
            _delay_ms(100); // Debounce delay
            buzz_off(); // Turn off buzzer when mode is switched
            led_off(); // Turn off LED when mode is switched
            lcd_clear_screen(); // Clear LCD screen
        }

        if(mode == 0)
        {
            temp_value = lm35_get_temp();    // Fetch temperature value

            lcd_display_string_row_column(0,0,temp);    // Display "Temp: " on LCD
            lcd_intger_to_string(temp_value);         // Display temperature value on LCD
            
            lcd_display_string_row_column(1,0,lower);   // Display "LB: "
            lcd_intger_to_string(temp_lbound);         // Display lower bound value
            lcd_display_string_row_column(1,8,upper);   // Display "UB: "
            lcd_intger_to_string(temp_ubound);         // Display upper bound value
            
            button_val = analogue_button_read(); // Read button value

            switch (button_val) // Check which button was pressed
            {
                case 'U': // Up
                    temp_ubound++; // Increment upper bound
                    break;
                case 'D': // Down
                    temp_ubound--; // Decrement upper bound
                    break;
                case 'R': // Right
                    temp_lbound++; // Increment lower bound
                    break;
                case 'L': // Left
                    temp_lbound--; // Decrease lower bound
                    break;
                default:
                    break;
                }
            if(temp_value < temp_lbound || temp_value > temp_ubound) // Check if temperature is out of bounds
            {
                //Trun on alerts
                led_on(); // Turn on LED
                buzz_on(); // Turn on buzzer
                lcd_display_string_row_column(0,12,nok);
            }
            else
            {   // Turn off alerts
                led_off(); // Turn off LED
                buzz_off(); // Turn off buzzer
                lcd_display_string_row_column(0,12,ok);
            }
        }
        else // LDR mode
        {
            ldr_value = ldr_get_light_intensity();           // Fetch temperature value
            lcd_display_string_row_column(0,0,intensity);    // Display "Intensity: " on LCD
            lcd_intger_to_string(ldr_value);                 // Display light intensity value on LCD

            lcd_display_string_row_column(1,0,lower);   // Display "LB: "
            lcd_intger_to_string(ldr_lbound);          // Display lower bound value
            lcd_display_string_row_column(1,8,upper);   // Display "UB: "
            lcd_intger_to_string(ldr_ubound);          // Display upper bound value

            button_val = analogue_button_read(); // Read button value

            switch (button_val) // Check which button was pressed
            {
                case 'U': // Up
                    ldr_ubound += 10; // Increment upper bound
                    break;
                case 'D': // Down
                    ldr_ubound -= 10; // Decrement upper bound
                    break;
                case 'R': // Right
                    ldr_lbound += 10; // Increment lower bound
                    break;
                case 'L': // Left
                    ldr_lbound -= 10; // Decrease lower bound
                    break;
                default:
                    break;
            }
            if(ldr_ubound < 100)
            {
                // Clear extra digit if bound exeeds 2 digits then falls back to 2 digits
                lcd_display_string_row_column(1,13," ");
            } 
            if (ldr_value < ldr_lbound || ldr_value > ldr_ubound) // Check if LDR value is out of bounds
            {
                // Turn on alerts
                led_on(); // Turn on LED
                buzz_on(); // Turn on buzzer
                lcd_display_string_row_column(0,12,nok); // Display "NOK" declaring that the value is out of bounds
            }
            else
            {   // Turn off alerts
                led_off(); // Turn off LED
                buzz_off(); // Turn off buzzer
                lcd_display_string_row_column(0,12,ok); // Display "OK" declaring that the value is within bounds
            }
        }

    }

    return 0;
}
