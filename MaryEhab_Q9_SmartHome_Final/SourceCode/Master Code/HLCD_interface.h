

/*Header file guard*/
#ifndef HLCD_INTERFACE_H_
#define HLCD_INTERFACE_H_


/************************************************************************/
/*                           Interfacing macros                         */
/************************************************************************/
/*LCD Rows*/
#define HLCD_ROW0 (0x80)
#define HLCD_ROW1 (0xC0)

/*LCD COLUMNS*/
#define HLC_COL0  (0)
#define HLC_COL1  (1)
#define HLC_COL2  (2)
#define HLC_COL3  (3)
#define HLC_COL4  (4)
#define HLC_COL5  (5)
#define HLC_COL6  (6)
#define HLC_COL7  (7)
#define HLC_COL8  (8)
#define HLC_COL9  (9)
#define HLC_COL10 (10)
#define HLC_COL11 (11)
#define HLC_COL12 (12)
#define HLC_COL13 (13)
#define HLC_COL14 (14)
#define HLC_COL15 (15)


/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/

/*This function is used in initializing the LCD module*/
void hlcd_init(void);

/*This functions moves the cursor to a specified row and column*/
void hlcd_goToRowCol(uint8 au8_row,uint8 au8_col);

/*This function is used in writing a character over LCD*/
void hlcd_writeChar(uint8 au8_charData);

/*This function is used in writing a string of characters over LCD*/
void hlcd_writeString(uint8 pu8_stringData);

/*This function is used in clearing LCD*/
void hlcd_clearLCD(void);

#endif /* HLCD_INTERFACE_H_ */