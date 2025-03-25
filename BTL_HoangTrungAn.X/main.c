/*
 * File:   main.c
 * Author: oopsan1112
 *
 * Created on February 12, 2025, 11:28 PM
 */
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS   // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON  // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF    // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF   // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF  // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF   // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF      // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "HCSR04_lib.h"
#include "I2C_LCD.h"
#include "UART.h"
#include "pic16f887.h"

// #include "software_PWM.h"

#define _XTAL_FREQ 12000000

#define PAUSE_BUTTON_PORT PORTD
#define PAUSE_BUTTON_TRIS TRISD
#define PAUSE_BUTTON_PIN 4

#define DEBOUNCE_DELAY 20

#define LED_PORT PORTC
#define LED_TRIS TRISC
#define LED_PIN 2

unsigned char isPaused = 0;
unsigned char lastButtonState = 0;

void BUTTON_Init(void)
{
    PAUSE_BUTTON_TRIS = PAUSE_BUTTON_PIN;
    PAUSE_BUTTON_PORT = 1; // Enable pull-up resistor
}
void LED_Init(void)
{
    LED_TRIS &= ~(1 << LED_PIN); // Set as output
    LED_PORT &= ~(1 << LED_PIN); // Initialize to OFF
}
void LED_Off(void)
{
    LED_PORT |= (1 << LED_PIN); // Set the LED pin high
}
void LED_On(void)
{
    LED_PORT &= ~(1 << LED_PIN); // Set the LED pin low
}

void checkPauseButton()
{
    unsigned char currentButtonState = PAUSE_BUTTON_PORT & (1 << PAUSE_BUTTON_PIN);

    if (currentButtonState != lastButtonState)
    {
        __delay_ms(DEBOUNCE_DELAY); // Chống dội nút nhấn
        currentButtonState = PAUSE_BUTTON_PORT & (1 << PAUSE_BUTTON_PIN);

        if (currentButtonState != lastButtonState)
        {
            lastButtonState = currentButtonState;

            if (currentButtonState == 0) // Button is pressed (active low)
            {
                isPaused = !isPaused; // Đổi trạng thái pause

                // Call distance measurement when button is pressed
                SR04_Distance();

                if (isPaused)
                {
                    // BUZZER_On();
                    LED_On();
                }
                else
                {
                    // BUZZER_Off();
                    LED_Off();
                }
            }
        }
    }
}

void main(void)
{
    // Initialize the HC-SR04 sensor
    SR04_init();
    // Initialize the pause button
    BUTTON_Init();
    // Initialize the buzzer
    BUZZER_Init();
    // Initialize the LED
    LED_Init();
    // Initialize the UART
    UART_TX_Init();

    // Send welcome message via UART
    UART_Write_Text("Welcome to the HC-SR04 Distance Measurement System\r\n");
    UART_Write_Text("Press the button to start/pause the measurement\r\n");

    // Initialize the LCD
    I2C_Master_Init();
    LCD_Init(0x4E); // Initialize LCD module with I2C address = 0x4E
    // Write strings to LCD
    LCD_Clear();
    LCD_Set_Cursor(1, 1);
    LCD_Write_String("Hoang Trung An");
    LCD_Set_Cursor(2, 0);
    LCD_Write_String("Nguyen Hung Duong");
    __delay_ms(2000);
    LCD_Clear();
    LCD_Set_Cursor(1, 1);
    LCD_Write_String("BTL VI DIEU KHIEN");


    while (1)
    {
        // Check pause button
        checkPauseButton();

        
    }

    __delay_ms(100);
    return;
}
