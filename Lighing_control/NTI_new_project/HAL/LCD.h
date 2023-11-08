 


#ifndef LCD_H_
#define LCD_H_

#include "STD_types.h"
#include "LCD_private.h"

#define  RS   PA3
#define  EN   PA2

#define  D4   PB0
#define  D5   PB1
#define  D6   PB2
#define  D7   PB4



void LCD_Init(void);


void LCD_WriteChar(u8 ch);
void LCD_WriteString(char *str);
void LCD_WriteString_multiLine(u8 *str);

void LCD_WriteNumber(s32 num);
void LCD_goto(u8 line ,u8 cell);

// void LCD_WriteBinary(s8 num);
// void LCD_WriteHex(s32 num);

// void LCD_WriteNumber_4D(u16 num);
// void LCD_WriteNumber_Digits(s32 num,u8 digit
// void LCD_ClearCell(u8 line ,u8 cell,u8 num);
void LCD_Clear(void);



void LCD_WriteIns(u8 ins);
void LCD_WriteData(u8 data);




// 
// void LCD_Init(void);
// 
// void LCD_write_instruction(LCD_instruction_t instruction);
// void LCD_write_data(u8 data);
// 
// void LCD_Write_char(u8 ch);
// void LCD_write_string(u8* ch);
// 
// void LCD_goto(u8 line, u8 column);





#endif /* LCD_H_ */