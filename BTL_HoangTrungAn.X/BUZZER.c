/*
 * File:   BUZZER.c
 * Author: Lenovo
 *
 * Created on March 11, 2025, 10:15 PM
 */


#include "BUZZER.h"

// Add this function before your BUZZER functions
void custom_delay_ms(unsigned int ms)
{
    unsigned int i;
    for (i = 0; i < ms; i++)
    {
        __delay_ms(1); // Delay 1ms at a time
    }
}
// Buzzer control functions
void BUZZER_Init(void)
{
    BUZZER_TRIS &= ~(1 << BUZZER_PIN); // Set as output
    BUZZER_PORT |= (1 << BUZZER_PIN);  // Set the buzzer pin high
}

void BUZZER_Off(void)
{
    BUZZER_PORT |= (1 << BUZZER_PIN); // Set the buzzer pin high
}

void BUZZER_On(void)
{
    BUZZER_PORT &= ~(1 << BUZZER_PIN); // Set the buzzer pin low
}

void BUZZER_Beep(uint16_t duration)
{
    BUZZER_On();
    custom_delay_ms(duration);
    BUZZER_Off();
}

void BUZZER_MultipleBeeps(uint8_t count, uint16_t beep_duration, uint16_t pause_duration)
{
    for (uint8_t i = 0; i < count; i++)
    {
        BUZZER_On();
        custom_delay_ms(beep_duration);
        BUZZER_Off();
        if (i < count - 1)
        {
            custom_delay_ms(pause_duration);
        }
    }
}