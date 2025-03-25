/*
 * File:   software_PWM.c
 * Author: Lenovo
 *
 * Created on February 23, 2025, 9:32 PM
 */

#include "software_PWM.h"


void SoftPWM_Init(uint8_t prescaler, uint8_t postscaler, uint8_t period);
uint8_t SoftPWM_AddChannel(volatile unsigned char *port, volatile unsigned char *tris, uint8_t pin_number, uint8_t initial_duty);
void SoftPWM_SetDuty(uint8_t channel, uint8_t duty);
void SoftPWM_SetDutyPercent(uint8_t channel, uint8_t percent);
void SoftPWM_Enable(uint8_t channel, uint8_t state);
void SoftPWM_StopAll(void);



// Initialize Timer2 for PWM
void SoftPWM_Init(uint8_t prescaler, uint8_t postscaler, uint8_t period)
{
    // Disable Timer2 before configuration
    T2CON = 0x00;

    // Configure Timer2
    T2CON = (postscaler << 3) | (prescaler);
    PR2 = period;

    // Enable Timer2 and related interrupts
    PIE1bits.TMR2IE = 1; // Timer2 interrupt enable
    INTCONbits.PEIE = 1; // Peripheral interrupt enable
    INTCONbits.GIE = 1;  // Global interrupt enable

    T2CONbits.TMR2ON = 1; // Enable Timer2
}

// Helper function to configure pin
Pin_Config SoftPWM_ConfigurePin(volatile unsigned char *port,
                                volatile unsigned char *tris,
                                uint8_t pin_number)
{
    Pin_Config config;
    config.port = port;
    config.tris = tris;
    config.pin_mask = (1 << pin_number);
    return config;
}

// Add a new PWM channel
uint8_t SoftPWM_AddChannel(volatile unsigned char *port,
                           volatile unsigned char *tris,
                           uint8_t pin_number,
                           uint8_t initial_duty)
{
    if (num_channels >= MAX_PWM_CHANNELS)
        return 0xFF;

    uint8_t channel = num_channels++;

    // Configure pin
    pwm_channels[channel].pin = SoftPWM_ConfigurePin(port, tris, pin_number);
    pwm_channels[channel].duty = initial_duty;
    pwm_channels[channel].counter = 0;
    pwm_channels[channel].enabled = 1;

    // Set pin as output and initialize to low
    *(pwm_channels[channel].pin.tris) &= ~pwm_channels[channel].pin.pin_mask;
    *(pwm_channels[channel].pin.port) &= ~pwm_channels[channel].pin.pin_mask;

    return channel;
}

// Set duty cycle for a channel
void SoftPWM_SetDuty(uint8_t channel, uint8_t duty)
{
    if (channel < num_channels)
    {
        pwm_channels[channel].duty = duty;
    }
}

// Set duty cycle as percentage (0-100)
void SoftPWM_SetDutyPercent(uint8_t channel, uint8_t percent)
{
    if (channel < num_channels && percent <= 100)
    {
        pwm_channels[channel].duty = (uint8_t)((uint16_t)percent * 255 / 100);
    }
}

// Enable/disable a channel
void SoftPWM_Enable(uint8_t channel, uint8_t state)
{
    if (channel < num_channels)
    {
        pwm_channels[channel].enabled = state;
        if (!state)
        {
            *(pwm_channels[channel].pin.port) &= ~pwm_channels[channel].pin.pin_mask;
        }
    }
}

// Stop all channels
void SoftPWM_StopAll(void)
{
    for (uint8_t i = 0; i < num_channels; i++)
    {
        pwm_channels[i].enabled = 0;
        *(pwm_channels[i].pin.port) &= ~pwm_channels[i].pin.pin_mask;
    }
}

// Timer2 interrupt service routine
void __interrupt() PWM_ISR(void)
{
    if (PIR1bits.TMR2IF)
    {
        // Process each PWM channel
        for (uint8_t i = 0; i < num_channels; i++)
        {
            if (pwm_channels[i].enabled)
            {
                if (pwm_channels[i].counter < pwm_channels[i].duty)
                {
                    *(pwm_channels[i].pin.port) |= pwm_channels[i].pin.pin_mask; // Set HIGH
                }
                else
                {
                    *(pwm_channels[i].pin.port) &= ~pwm_channels[i].pin.pin_mask; // Set LOW
                }
                pwm_channels[i].counter++;
            }
        }

        PIR1bits.TMR2IF = 0; // Clear Timer2 interrupt flag
    }
}