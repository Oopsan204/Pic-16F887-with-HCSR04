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
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef SOFTWARE_PWM_H
#define SOFTWARE_PWM_H

#include <xc.h>

// Maximum number of PWM channels
#define MAX_PWM_CHANNELS 8

// Timer2 configuration constants
#define TMR2_PRESCALER_1 0x00
#define TMR2_PRESCALER_4 0x01
#define TMR2_PRESCALER_16 0x02
#define TMR2_POSTSCALER_1 0x00
#define TMR2_POSTSCALER_16 0x0F

// Pin configuration structure
typedef struct
{
    volatile unsigned char *port; // Pointer to PORT register
    volatile unsigned char *tris; // Pointer to TRIS register
    unsigned char pin_mask;       // Pin bit mask
} Pin_Config;

// PWM channel structure
typedef struct
{
    Pin_Config pin;  // Pin configuration
    uint8_t duty;    // Duty cycle (0-255)
    uint8_t counter; // Internal counter
    uint8_t enabled; // Channel state
} PWM_Channel;

// Global variables
volatile PWM_Channel pwm_channels[MAX_PWM_CHANNELS];
volatile uint8_t num_channels = 0;

void SoftPWM_Init(uint8_t prescaler, uint8_t postscaler, uint8_t period);
uint8_t SoftPWM_AddChannel(volatile unsigned char *port, volatile unsigned char *tris, uint8_t pin_number, uint8_t initial_duty);
void SoftPWM_SetDuty(uint8_t channel, uint8_t duty);
void SoftPWM_SetDutyPercent(uint8_t channel, uint8_t percent);
void SoftPWM_Enable(uint8_t channel, uint8_t state);
void SoftPWM_StopAll(void);

#endif /* SOFTWARE_PWM_H */
