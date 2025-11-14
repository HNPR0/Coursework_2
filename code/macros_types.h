#define GETBIT(REG, BIT)      (((REG) >> (BIT)) & 1)      
#define SET_BIT(REG, BIT)     (REG |= (1<<BIT))           
#define CLEAR_BIT(REG, BIT)   (REG &= (~(1<<BIT)))        
#define BIT_IS_SET(REG,BIT)   (REG & (1<<BIT) )           
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )


#define NULL_PTR    ((void*)0)
#define OUTPUT_PORT      0xFF
#define INPUT_PORT       0x00

typedef unsigned char         uint8;
typedef signed char           sint8;
typedef unsigned short        uint16;
typedef signed short          sint16;
typedef unsigned long         uint32;
typedef signed long           sint32;

