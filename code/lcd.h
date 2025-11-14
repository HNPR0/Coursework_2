#ifndef LCD_H_
#define LCD_H_

#include "macros_types.h"


/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT                 1
#define LCD_RS_PIN                  0

#define LCD_E_PORT                  1
#define LCD_E_PIN                   1



#define LCD_DATA_PORT              3      

#define LCDD_B4_PIN                4
#define LCDD_B5_PIN                5
#define LCDD_B6_PIN                6
#define LCDD_B7_PIN                7

#define BackLight               10

/* LCD Commands */
#define LCD_ClEAR_COMMAND                   0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_FOUR_BITS_MODE                   0x28
#define LCD_FOUR_BITS_MODE_INIT1              0x33
#define LCD_FOUR_BITS_MODE_INIT2              0x32
#define LCD_CURSOR_OFF                      0x0C
#define LCD_CURSOR_ON                       0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

void lcd_init(void);
void lcd_send_command(uint8 Command);
void lcd_display_character(uint8 Data);
void lcd_display_string(const char *Str);
void lcd_move_cursor(uint8 row,uint8 col);
void lcd_display_string_row_column(uint8 row,uint8 col,const char *Str);
void lcd_intger_to_string(int Data);
void lcd_clear_screen(void);

#endif /* LCD_H_ */