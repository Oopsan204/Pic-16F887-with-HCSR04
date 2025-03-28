/* Microchip Technology Inc. and its subsidiaries.  You may use this software
 * and any derivatives exclusively with Microchip products.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
 * TERMS.
 */

/*
 * File:
 * Author: oopsan1112
 * Comments:
 * Revision history:
 */

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <xc.h> // include processor files - each processor file is guarded.

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>

    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>

    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage
// live documentation

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C
    // linkage so the functions can be used by the c code.

#define _XTAL_FREQ 12000000

#define I2C_BaudRate 100000
#define SCL_D TRISC3
#define SDA_D TRISC4

#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00
#define LCD_FIRST_ROW 0x80
#define LCD_SECOND_ROW 0xC0
#define LCD_THIRD_ROW 0x94
#define LCD_FOURTH_ROW 0xD4
#define LCD_CLEAR 0x01
#define LCD_RETURN_HOME 0x02
#define LCD_ENTRY_MODE_SET 0x04
#define LCD_CURSOR_OFF 0x0C
#define LCD_UNDERLINE_ON 0x0E
#define LCD_BLINK_CURSOR_ON 0x0F
#define LCD_MOVE_CURSOR_LEFT 0x10
#define LCD_MOVE_CURSOR_RIGHT 0x14
#define LCD_TURN_ON 0x0C
#define LCD_TURN_OFF 0x08
#define LCD_SHIFT_LEFT 0x18
#define LCD_SHIFT_RIGHT 0x1E
#define LCD_TYPE 2 // 0 -> 5x7 | 1 -> 5x10 | 2 -> 2 lines

    //-----------[ Functions' Prototypes ]--------------

    //---[ I2C Routines ]---

    void I2C_Master_Init();
    void I2C_Master_Wait();
    void I2C_Master_Start();
    void I2C_Master_RepeatedStart();
    void I2C_Master_Stop();
    void I2C_ACK();
    void I2C_NACK();
    unsigned char I2C_Master_Write(unsigned char data);
    unsigned char I2C_Read_Byte(void);

    //---[ LCD Routines ]---

    void LCD_Init(unsigned char I2C_Add);
    void IO_Expander_Write(unsigned char Data);
    void LCD_Write_4Bit(unsigned char Nibble);
    void LCD_CMD(unsigned char CMD);
    void LCD_Set_Cursor(unsigned char ROW, unsigned char COL);
    void LCD_Write_Char(char);
    void LCD_Write_String(char *);
    void Backlight();
    void noBacklight();
    void LCD_SR();
    void LCD_SL();
    void LCD_Clear();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // LCD_I2C_H
