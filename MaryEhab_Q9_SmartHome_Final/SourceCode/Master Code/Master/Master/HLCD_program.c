

/************************************************************************/
/*                              Includes                                */
/************************************************************************/

#include "STD_TYPES.h"
#include "LBIT_MATH.h"
#include "DIO.h"
#include "HLCD_private.h"
#include "HLCD_interface.h"

#define F_CPU 16000000UL
#include "util/delay.h"

/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/

static void hlcd_sendCMD(uint8 au8_cmd)
{
	/*Writing over LCD*/
	DIO_write(HLCD_CONTROL_PORT, HLCD_RW, 0);
	
	/*Sending command over LCD*/	
	DIO_write(HLCD_CONTROL_PORT, HLCD_RS, 0);
	
	/*Transferring the 1 nibble bits*/
	DIO_write(HLCD_DATA_PORT, HLCD_DB7, DIO_u8read(au8_cmd, 7));
	DIO_write(HLCD_DATA_PORT, HLCD_DB6, DIO_u8read(au8_cmd, 6));
	DIO_write(HLCD_DATA_PORT, HLCD_DB5, DIO_u8read(au8_cmd, 5));
	DIO_write(HLCD_DATA_PORT, HLCD_DB4, DIO_u8read(au8_cmd, 4));
	
	/*Trigger writing over the LCD*/
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 0);
	_delay_us(50);
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 1);

	/*Transferring the 0 nibble bits*/	
	DIO_write(HLCD_DATA_PORT, HLCD_DB7, DIO_u8read(au8_cmd, 3));
	DIO_write(HLCD_DATA_PORT, HLCD_DB6, DIO_u8read(au8_cmd, 2));
	DIO_write(HLCD_DATA_PORT, HLCD_DB5, DIO_u8read(au8_cmd, 1));
	DIO_write(HLCD_DATA_PORT, HLCD_DB4, DIO_u8read(au8_cmd, 0));

	/*Trigger writing over the LCD*/	
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 0);
	_delay_us(50);
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 1);	
	
	/*Return from this function*/
	return;
}

static void hlcd_sendData(uint8 au8_data)
{
	/*Writing over LCD*/
	DIO_write(HLCD_CONTROL_PORT, HLCD_RW, 0);
	
	/*Sending display data over LCD*/
	DIO_write(HLCD_CONTROL_PORT, HLCD_RS, 1);
	
	/*Transferring the 1 nibble bits*/
	DIO_write(HLCD_DATA_PORT, HLCD_DB7, DIO_u8read(au8_data, 7));
	DIO_write(HLCD_DATA_PORT, HLCD_DB6, DIO_u8read(au8_data, 6));
	DIO_write(HLCD_DATA_PORT, HLCD_DB5, DIO_u8read(au8_data, 5));
	DIO_write(HLCD_DATA_PORT, HLCD_DB4, DIO_u8read(au8_data, 4));
	
	/*Trigger writing over the LCD*/
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 0);
	_delay_us(50);
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 1);

	/*Transferring the 0 nibble bits*/
	DIO_write(HLCD_DATA_PORT, HLCD_DB7, DIO_u8read(au8_data, 3));
	DIO_write(HLCD_DATA_PORT, HLCD_DB6, DIO_u8read(au8_data, 2));
	DIO_write(HLCD_DATA_PORT, HLCD_DB5, DIO_u8read(au8_data, 1));
	DIO_write(HLCD_DATA_PORT, HLCD_DB4, DIO_u8read(au8_data, 0));

	/*Trigger writing over the LCD*/
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 0);
	_delay_us(50);
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 1);

	/*Return from this function*/
	return;
}

void hlcd_init(void)
{
	/*LCD data pins initialization as 1*/
	DIO_vsetPINDir(HLCD_DATA_PORT, (HLCD_DB4 | HLCD_DB5 | HLCD_DB6 | HLCD_DB7), 1);	
	
	/*LCD control pins initialization as 1*/
	DIO_vsetPINDir(HLCD_CONTROL_PORT, (HLCD_RS | HLCD_RW | HLCD_EN), 1);
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 1);
	
	/*Wait until Vdd rises to 4.5v*/
	_delay_ms(50);
	
	/*Writing over LCD*/
	DIO_write(HLCD_CONTROL_PORT, HLCD_RW, 0);
	
	/*Sending command over LCD*/
	DIO_write(HLCD_CONTROL_PORT, HLCD_RS, 0);
	
	/*Transferring the function set instruction header (4-bits)*/
	DIO_write(HLCD_DATA_PORT, HLCD_DB7, 0);
	DIO_write(HLCD_DATA_PORT, HLCD_DB6, 0);
	DIO_write(HLCD_DATA_PORT, HLCD_DB5, 1);
	DIO_write(HLCD_DATA_PORT, HLCD_DB4, 0);
	
	/*Trigger writing over the LCD*/
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 0);
	_delay_us(50);
	DIO_write(HLCD_CONTROL_PORT, HLCD_EN, 1);
	
	/*Sending the function set instruction*/
	hlcd_sendCMD(0x2C);
	
	/*Delay for 1 millisecond*/
	_delay_ms(1);

	/*Sending the display ON/OFF control instruction*/
	hlcd_sendCMD(0x0F);
	
	/*Delay for 1 millisecond*/
	_delay_ms(1);
	
	/*Sending the clearing display instruction*/
	hlcd_sendCMD(0x01);
	
	/*Delay for 2 millisecond*/
	_delay_ms(2);
	
	/*Sending the entry mode set instruction*/
	hlcd_sendCMD(0x06);
	
	/*Delay for 1 millisecond*/
	_delay_ms(1);

	/*Return from this function*/
	return;
}

void hlcd_writeChar(uint8 au8_charData)
{
	/*Sending the character data over LCD*/
	hlcd_sendData(au8_charData);
	
	/*Return from this function*/
	return;
}

void hlcd_writeString(uint8 pu8_stringData)
{
	/*Looping over string characters*/
	while(*int pu8_stringData != '\0')
	{
		/*Sending the character data*/
		hlcd_sendData(*int pu8_stringData);
		
		/*Increment the pointer current address*/
		pu8_stringData++;
	}
	
	/*Return from this function*/
	return;
}

void hlcd_clearLCD(void)
{
	/*Sending the clearing display instruction*/
	hlcd_sendCMD(0x01);
		
	/*Delay for 2 millisecond*/
	_delay_ms(2);

	/*Return from this function*/
	return;
}


void hlcd_goToRowCol(uint8 au8_row,uint8 au8_col)
{
	    
		hlcd_sendCMD(au8_row | au8_col);

	/*Return from this function*/
	return ;
}
