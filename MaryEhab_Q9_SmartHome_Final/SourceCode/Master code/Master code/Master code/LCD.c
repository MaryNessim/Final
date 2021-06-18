/*
 * LCD.c
 *
 * Created: 2/23/2018 4:38:26 PM
 *  Author: Mohamed Zaghlol
 */ 

static void send_falling_edge(void); //prototype of the private function

#include "LCD.h" 
#include "LBIT_MATH.H"


void LCD_vInit(void)
{
	/*#if defined eight_bits_mode*/ //depend on pre-defined configurations which exist in lcd_config.h
	/* set LCD pins as output pins in case of 8 bit LCD*/
	/*DIO_vsetPINDir(LCD_PORT,LCD_FIRST_PIN,1);
	DIO_vsetPINDir(LCD_PORT,LCD_SECOND_PIN,1);
	DIO_vsetPINDir(LCD_PORT,LCD_THIRD_PIN,1);*/
	DIO_vsetPINDir(LCD_PORT,LCD_FOURTH_PIN,1);
	DIO_vsetPINDir(LCD_PORT,LCD_FIFTH_PIN,1);
	DIO_vsetPINDir(LCD_PORT,LCD_SIXTH_PIN,1);
	DIO_vsetPINDir(LCD_PORT,LCD_SEVENTH_PIN,1);
	/*DIO_vsetPINDir(LCD_PORT,LCD_EIGHTH_PIN,1);*/
	/*****************************/
	/* set LCD control pins as output pins in case of 8 bit LCD */
	DIO_vsetPINDir(LCD_CONTROL_PORT,LCD_EN_PIN,1);
	DIO_vsetPINDir(LCD_CONTROL_PORT,LCD_RW_PIN,1);
	DIO_vsetPINDir(LCD_CONTROL_PORT,LCD_RS_PIN,1);
	/*****************************/
	DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,1);
	_delay_ms(50); //small delay to ensure LCD finish the initialization
	
	DIO_write(LCD_CONTROL_PORT,LCD_RW_PIN,0); // enable write to LCD 
	DIO_write(LCD_CONTROL_PORT,LCD_RS_PIN,0);
	
	/*LCD_vSend_cmd(EIGHT_BIT_MODE); //enable 8 bit LCD Mode 
	LCD_vSend_cmd(CLR_SCREEN); // CLR LCD screen 
	LCD_vSend_cmd(DISPLAY_ON_CURSOR_ON); // enable cursor and display on 
*/
		DIO_vsetPINDir(LCD_PORT,LCD_FOURTH_PIN,0);
		DIO_vsetPINDir(LCD_PORT,LCD_FIFTH_PIN,1);
		DIO_vsetPINDir(LCD_PORT,LCD_SIXTH_PIN,0);
		DIO_vsetPINDir(LCD_PORT,LCD_SEVENTH_PIN,0);
		
		DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,0);
		
	_delay_ms(50); //small delay to ensure LCD finish the initialization
	DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,1);
	
	LCD_vSend_cmd(0X2C);
	
	_delay_ms(1);
	
	LCD_vSend_cmd(0X0F);
	
	_delay_ms(1);
	
	
	LCD_vSend_cmd(0X01);
	
	_delay_ms(2);
	
	LCD_vSend_cmd(0X06);
	
	_delay_ms(1);
	
/*	#elif defined four_bits_mode //depend on pre-defined configurations which exist in lcd_config.h
/* set LCD pins as output pins in case of 4 bit LCD*/
/*	DIO_vsetPINDir(LCD_PORT,LCD_FIFTH_PIN,1);
	DIO_vsetPINDir(LCD_PORT,LCD_SIXTH_PIN,1);
	DIO_vsetPINDir(LCD_PORT,LCD_SEVENTH_PIN,1);
	DIO_vsetPINDir(LCD_PORT,LCD_EIGHTH_PIN,1);
/*****************************/
/* set LCD control pins as output pins in case of 4 bit LCD */
/*	DIO_vsetPINDir(LCD_CONTROL_PORT,LCD_EN_PIN,1); 
	DIO_vsetPINDir(LCD_CONTROL_PORT,LCD_RW_PIN,1); 
	DIO_vsetPINDir(LCD_CONTROL_PORT,LCD_RS_PIN,1);
/*****************************/
/*	DIO_write(LCD_CONTROL_PORT,LCD_RW_PIN,0); // enable write to LCD 
	LCD_vSend_cmd(FOUR_BIT_MODE_I); //enable 4 bit LCD Mode 
	LCD_vSend_cmd(FOUR_BIT_MODE_II); //enable 4 bit LCD Mode 
	LCD_vSend_cmd(CLR_SCREEN); // CLR LCD screen 
	LCD_vSend_cmd(DISPLAY_ON_CURSOR_ON); // enable cursor and display on 
	_delay_ms(10); //small delay to ensure LCD finish the initialization*/
	
	/*#endif*/ 
	
	return;
} // end of LCD initialization


static void send_falling_edge(void)
{
	/* to enable printing the sent character to LCD ,we should send send falling edge to the lcd*/ 
	DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,1); // set enable pin to one
	_delay_ms(2); //period of high
	DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,0); // clear enable pin 
	_delay_ms(2); // period of low
	
	return;
}
void LCD_vSend_cmd(uint8 cmd)
{
	/*#if defined eight_bits_mode*/ //depend on pre-defined configurations which exist in lcd_config.h
	DIO_write(LCD_CONTROL_PORT,LCD_RW_PIN,0);
	/*DIO_write_port(LCD_PORT,cmd);*/ //send the command to LCD
	DIO_write(LCD_CONTROL_PORT,LCD_RS_PIN,0); //enable LCD to receive command 
	/*send_falling_edge();*/ //send falling edge
	DIO_write(LCD_CONTROL_PORT,LCD_SEVENTH_PIN,GET_BIT(cmd, 7));
	DIO_write(LCD_CONTROL_PORT,LCD_SIXTH_PIN,GET_BIT(cmd, 6));
	DIO_write(LCD_CONTROL_PORT,LCD_FIFTH_PIN,GET_BIT(cmd, 5));
	DIO_write(LCD_CONTROL_PORT,LCD_FOURTH_PIN,GET_BIT(cmd, 4));
	
	DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,0);
	_delay_us(50);
	DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,1);
	
		DIO_write(LCD_CONTROL_PORT,LCD_SEVENTH_PIN,GET_BIT(cmd, 3));
		DIO_write(LCD_CONTROL_PORT,LCD_SIXTH_PIN,GET_BIT(cmd, 2));
		DIO_write(LCD_CONTROL_PORT,LCD_FIFTH_PIN,GET_BIT(cmd, 1));
		DIO_write(LCD_CONTROL_PORT,LCD_FOURTH_PIN,GET_BIT(cmd, 0));
		
			DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,0);
			_delay_us(50);
			DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,1);
	
	/*#elif defined four_bits_mode //depend on pre-defined configurations which exist in lcd_config.h
	/* send command to LCD */
/*	clear_high_nibble(LCD_PORT,cmd);
	dio_write_highnibble(LCD_PORT,cmd&0xf0);
	DIO_write(LCD_CONTROL_PORT,LCD_RS_PIN,0); //enable LCD to receive command
	send_falling_edge(); //send falling edge
	clear_high_nibble(LCD_PORT,cmd);
	dio_write_highnibble(LCD_PORT,cmd<<4);
	DIO_write(LCD_CONTROL_PORT,LCD_RS_PIN,0); //enable LCD to receive command
	send_falling_edge(); //send falling edge
	/***************************************/
	/*#endif*/
	return;
}
void LCD_vSend_char(uint8 data)
{
	
	DIO_write(LCD_CONTROL_PORT,LCD_RW_PIN,0);
/*	#if defined eight_bits_mode //depend on pre-defined configurations which exist in lcd_config.h
	DIO_write_port(LCD_PORT,data);*/ //send the data to LCD
	
	DIO_write(LCD_CONTROL_PORT,LCD_RS_PIN,1); //enable LCD to receive data
	send_falling_edge(); //send falling edge
	
			DIO_write(LCD_CONTROL_PORT,LCD_SEVENTH_PIN,GET_BIT(data, 7));
			DIO_write(LCD_CONTROL_PORT,LCD_SIXTH_PIN,GET_BIT(data, 6));
			DIO_write(LCD_CONTROL_PORT,LCD_FIFTH_PIN,GET_BIT(data, 5));
			DIO_write(LCD_CONTROL_PORT,LCD_FOURTH_PIN,GET_BIT(data, 4));
			
			DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,0);
			_delay_us(50);
			DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,1);
			
			DIO_write(LCD_CONTROL_PORT,LCD_SEVENTH_PIN,GET_BIT(data, 3));
			DIO_write(LCD_CONTROL_PORT,LCD_SIXTH_PIN,GET_BIT(data, 2));
			DIO_write(LCD_CONTROL_PORT,LCD_FIFTH_PIN,GET_BIT(data, 1));
			DIO_write(LCD_CONTROL_PORT,LCD_FOURTH_PIN,GET_BIT(data, 0));
			
						DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,0);
						_delay_us(50);
						DIO_write(LCD_CONTROL_PORT,LCD_EN_PIN,1);
	
	/*#elif defined four_bits_mode //depend on pre-defined configurations which exist in lcd_config.h
	clear_high_nibble(LCD_PORT,data); //send the data to LCD
	/*send data to lcd*/
	/*dio_write_highnibble(LCD_PORT,data&0xf0);
	DIO_write(LCD_CONTROL_PORT,LCD_RS_PIN,1);//enable LCD to receive data
	send_falling_edge(); //send falling edge
	clear_high_nibble(LCD_PORT,data);
	dio_write_highnibble(LCD_PORT,data<<4);
	DIO_write(LCD_CONTROL_PORT,LCD_RS_PIN,1); //enable LCD to receive data
	send_falling_edge(); //send falling edge
	/******************************************/
	/*#endif*/
	return;
}

void LCD_vSend_string(uint8 *data)
{
	while((*data)!=0) //keep in the loop until the end of the string 
	{
		LCD_vSend_char(*data); // print the characters of the string 
		data++; // make the pointer points to the next character
	}
	return;
}

void LCD_clearscreen(void)
{
	/*LCD_vSend_cmd(CLR_SCREEN);*/ // clear the screen
	LCD_vSend_cmd(0X01);
	_delay_ms(2);
	return;
}
void LCD_movecursor(uint8 row,uint8 coloumn)
{
	uint8 data ; // the command which will set the position of the cursor
	/* in case of wrong input set the cursor to the first position of the LCD*/
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	/********************************************/
	/*set the postion of cursor depend on the selected row and coloumn*/
	if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	/**************************************/
	
	LCD_vSend_cmd(row|coloumn); //set the position  of the cursor
return;
}