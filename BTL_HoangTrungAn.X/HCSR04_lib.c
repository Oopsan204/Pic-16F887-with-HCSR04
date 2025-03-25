/*
 * File:   HCSR04_lib.c
 * Author: Lenovo
 *
 * Created on February 13, 2025, 12:13 AM
 */

#include "HCSR04_lib.h"

#define LOW_PASS_FILTER_ALPHA 0.025
#define LOW_PASS_FILTER(x, y) ((x) * LOW_PASS_FILTER_ALPHA + (y) * (1 - LOW_PASS_FILTER_ALPHA))

// Global variables for interrupt handler
volatile unsigned int echo_start = 0;
volatile unsigned int last_distance = 0;
volatile unsigned char echo_complete = 0;
volatile unsigned char echo_state = 0; // 0: waiting, 1: measuring
float crystal_freq_mhz = 12.0;             // 12 MHz crystal
float sound_speed_cms = 34300.0;           // 343 m/s = 34300 cm/s
unsigned char timer_prescaler = 1;
float division_factor = 0;

void SR04_init()
{
    ANSELH = 0x00; // Port B as Digital I/O
    TRIG_dir = 0;  // TRIG output
    ECHO_dir = 1;  // ECHO as Input
    ECHO_ioc = 1;  // Interrupt-On-Change enabled for ECHO pin

    GIE = 1;  // Global Interrupt Enable
    RBIF = 0; // Clear PORTB On-Change Interrupt Flag
    RBIE = 1; // Enable PORTB On-Change Interrupt

    T1CON = 0x00; // Initialize Timer Module (Prescaler 1:1)
    // PIC uses 4 clock cycles per instruction
    float instruction_freq = crystal_freq_mhz * 1000000 / 4;

    // Calculate time per timer tick in microseconds
    float time_per_tick_us = (timer_prescaler * 1000000.0) / instruction_freq;

    // Division factor calculation:
    // For distance in cm: timer_value / division_factor
    // Where timer_value is proportional to echo time (round trip)
    // We divide by 2 because sound travels to object and back
    division_factor = 2000000.0 / (time_per_tick_us * sound_speed_cms)-1;
}
//------------------------------------------------------------------------------
void SR04_trigger()
{
    TMR1H = 0; // Sets the Initial Value of Timer
    TMR1L = 0; // Sets the Initial Value of Timer

    // Send trigger pulse
    TRIG = 0;
    __delay_us(2);
    TRIG = 1;
    __delay_us(10);
    TRIG = 0;
}

void SR04_Distance()
{
    unsigned int measurements[20] = {0}; // Store measurements
    unsigned int sum = 0;
    unsigned int valid_readings = 0;
    
    // Take multiple measurements
    for (int i = 0; i < 20; i++)
    {
        // Reset state
        echo_state = 0;
        echo_complete = 0;
        
        // Send trigger pulse
        SR04_trigger();
        
        // Wait for measurement to complete with timeout
        unsigned int timeout = 0;
        while (!echo_complete && timeout < 100)
        {
            __delay_ms(1);
            timeout++;
        }
        
        if (echo_complete && last_distance > 0 && last_distance < 450)
        {
            // Store valid measurement
            measurements[i] = last_distance;
            sum += last_distance;
            valid_readings++;
        }
        
        // Short delay between measurements
        __delay_ms(20);
    }
    
    // Calculate the average if we have valid readings
    if (valid_readings > 0)
    {
        distn = sum / valid_readings;
    }
    else
    {
        // No valid readings, use the last known distance
        distn = 0;
    }
    
    // Apply simple filtering to reject outliers
    if (distn > 350)
    {
        distn = 350; // Cap maximum reading
    }
        
    // Display distance on LCD
    LCD_Set_Cursor(2, 1);
    LCD_Write_String("                   ");
    
    if (distn == 0)
    {
        LCD_Set_Cursor(2, 1);
        LCD_Write_String("No reading");
        UART_Write_Text("Error: No reading\r\n");
        BUZZER_Beep(500); // Error beep
    }
    else
    {
        sprintf(out, "Distance = %d cm", distn);
        LCD_Set_Cursor(2, 1);
        LCD_Write_String(out);
        UART_Write_Text(out);
        UART_Write_Text("\r\n");
        
        // Sound feedback based on distance
        if (distn > 380)
        {
            LCD_Set_Cursor(2, 1);
            LCD_Write_String("Distance: Max range");
            BUZZER_Beep(300);
        }
        else if (distn < 10)
        {
            BUZZER_MultipleBeeps(3, 100, 100); // Triple beep for very close
        }
        else if (distn < 30)
        {
            BUZZER_MultipleBeeps(2, 200, 100); // Double beep for close
        }
        else
        {
            BUZZER_Beep(150); // Single beep for normal range
        }
    }
}

//------------------------------------------------------------------------------
void __interrupt() echoTime()
{
    if (RBIF == 1) // Makes sure that it is PORTB On-Change Interrupt
    {
        // Determine if rising or falling edge on ECHO pin
        if (ECHO == 1 && echo_state == 0)
        {
            // Rising edge - start timing
            TMR1H = 0;
            TMR1L = 0;
            TMR1ON = 1;
            echo_state = 1; // Now in measuring state
        }
        else if (ECHO == 0 && echo_state == 1)
        {
            // Falling edge - stop timing and calculate distance
            TMR1ON = 0;

            // Get timer value and calculate distance
            unsigned int TMR = (TMR1H << 8) | TMR1L;
            last_distance = TMR / division_factor; // For 12MHz crystal

            echo_state = 0;    // Reset state
            echo_complete = 1; // Signal measurement complete
        }
        RBIF = 0; // Clear interrupt flag
    }
}