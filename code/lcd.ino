#include <util/delay.h> 
#include "macros_types.h"
#include "lcd.h"
#include "gpio.h"
#include <avr/io.h>


void lcd_init(void)
{
	// Set the direction for RS and E pins as output
	gpio_setup_pin_direction(LCD_RS_PORT,LCD_RS_PIN, 1);
	gpio_setup_pin_direction(LCD_E_PORT,LCD_E_PIN, 1);

	_delay_ms(20);	// 20ms delya, LCD takes 15ms to turn on

	// Set LCD data pins direction as output
	gpio_setup_pin_direction(LCD_DATA_PORT,LCDD_B4_PIN,1);
	gpio_setup_pin_direction(LCD_DATA_PORT,LCDD_B5_PIN,1);
	gpio_setup_pin_direction(LCD_DATA_PORT,LCDD_B6_PIN,1);
	gpio_setup_pin_direction(LCD_DATA_PORT,LCDD_B7_PIN,1);

	//Send for 4 bit initialization of LCD 
	lcd_send_command(LCD_FOUR_BITS_MODE_INIT1);
	lcd_send_command(LCD_FOUR_BITS_MODE_INIT2);

	// use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode
	lcd_send_command(LCD_FOUR_BITS_MODE); 

	lcd_send_command(LCD_CURSOR_OFF); 			// Turn cursor off 
	lcd_send_command(LCD_ClEAR_COMMAND); 		// Clear LCD at the beginning
}

void lcd_send_command(uint8 Command)
{
 	gpio_write_pin(LCD_RS_PORT,LCD_RS_PIN,0); 			// Instruction Mode RS=0 
 	_delay_ms(1); 							// delay for processing 
 	gpio_write_pin(LCD_E_PORT,LCD_E_PIN,1);				// Enable LCD
 	_delay_ms(1); 							// delay for processing
 
	
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B4_PIN,GETBIT(Command,4));
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B5_PIN,GETBIT(Command,5));
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B6_PIN,GETBIT(Command,6));
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B7_PIN,GETBIT(Command,7));
 
 	_delay_ms(1);							// delay for processing 
 	gpio_write_pin(LCD_E_PORT,LCD_E_PIN,0); 			// Disable LCD 
 	_delay_ms(1); 							// delay for processing 
 	gpio_write_pin(LCD_E_PORT,LCD_E_PIN,1); 			// Enable LCD 
 	_delay_ms(1); 							// delay for processing
 
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B4_PIN,GETBIT(Command,0));
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B5_PIN,GETBIT(Command,1));
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B6_PIN,GETBIT(Command,2));
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B7_PIN,GETBIT(Command,3));
 
 	_delay_ms(1);							// delay for processing 
 	gpio_write_pin(LCD_E_PORT,LCD_E_PIN,0); 			// Disable LCD 
 	_delay_ms(1); 							// delay for processing 
 
}

void lcd_display_character(uint8 Data)
 {
 	gpio_write_pin(LCD_RS_PORT,LCD_RS_PIN,1); 		// Data Mode RS=1 
 	_delay_ms(1); 									// delay for processing 
 	gpio_write_pin(LCD_E_PORT,LCD_E_PIN,1);			// Enable LCD E=1 
 	_delay_ms(1); 									// delay for processing  
 
 
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B4_PIN,GETBIT(Data,4));
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B5_PIN,GETBIT(Data,5));
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B6_PIN,GETBIT(Data,6));
 	gpio_write_pin(LCD_DATA_PORT,LCDD_B7_PIN,GETBIT(Data,7));
 
 	_delay_ms(1); 							// delay for processing
 	gpio_write_pin(LCD_E_PORT,LCD_E_PIN,0); 			// Disable LCD E=0
 	_delay_ms(1); 							// delay for processing
 	gpio_write_pin(LCD_E_PORT,LCD_E_PIN,1); 			// Enable LCD E=1 
 	_delay_ms(1); 							// delay for processing
 
 	gpio_write_pin(LCD_DATA_PORT, LCDD_B4_PIN , GETBIT(Data,0) );
 	gpio_write_pin(LCD_DATA_PORT, LCDD_B5_PIN , GETBIT(Data,1) );
 	gpio_write_pin(LCD_DATA_PORT, LCDD_B6_PIN , GETBIT(Data,2) );
 	gpio_write_pin(LCD_DATA_PORT, LCDD_B7_PIN , GETBIT(Data,3) );
 
 	_delay_ms(1);								// delay for processing
 	gpio_write_pin(LCD_E_PORT,LCD_E_PIN,0); 	// Disable LCD
 	_delay_ms(1); 								// delay for processing
 
}

void lcd_display_string(const char *Str)
{
	uint8 i = 0; // Initialize string index
 	while(Str[i] != '\0') // Loop until null character is reached
 	{
 		lcd_display_character(Str[i]); // Display the current character
 		i++; // Increment index
 	}
}


void lcd_move_cursor(uint8 row,uint8 col)
{
	uint8 Lcd_memory_address; // Variable to hold the LCD DDRAM address

	// Calculate the required address in the LCD DDRAM
	switch(row)
	{
		case 0:
			Lcd_memory_address=col;
				break;
		case 1:
			Lcd_memory_address=col+0x40;
				break;
		case 2:
			Lcd_memory_address=col+0x10;
				break;
		case 3:
			Lcd_memory_address=col+0x50;
				break;
	}
	// Move the LCD cursor to this specific address 
	lcd_send_command(Lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}


void lcd_display_string_row_column(uint8 row,uint8 col,const char *Str)
{
 	lcd_move_cursor(row,col); 						// Go to to the required LCD position 
 	lcd_display_string(Str); 						// Display the string 
}


void lcd_intger_to_string(int Data)
{
	char buff[16]; 								// Buffer to hold the ASCII value
	itoa(Data,buff,10); 						// Use itoa function to convert the integer to string
	lcd_display_string(buff); 					// Display the string 
}


void lcd_clear_screen(void)
{
	lcd_send_command(LCD_ClEAR_COMMAND); // Send clear display Command
}
