/*
 * File:   UART.c
 * Author: Lenovo
 *
 * Created on February 21, 2025, 9:40 PM
 */


#include <xc.h>
#include "UART.h"

void UART_TX_Init(void)
{
    // Set baud rate to 9600 bps
    BRGH = 1;   // High-speed baud rate
    SPBRG = 77; // Set SPBRG for 9600 bps with 12 MHz clock

    // Enable Asynchronous Serial Port
    SYNC = 0;
    SPEN = 1;

    // Set RX-TX Pins to be in UART mode
    TRISC6 = 0; // TX pin (output)
    TRISC7 = 1; // RX pin (input)

    // Enable UART Transmission
    TXEN = 1;
    // Enable UART Reception
    CREN = 1;
}

uint8_t UART_TX_Empty()
{
    // Check if the output (transmitter) buffer is empty
    return TRMT;
}

// Function to transmit a single character over UART
void UART_Write(uint8_t data)
{
    // Wait until the transmitter buffer is empty
    while (!UART_TX_Empty())
        ;

    // Write data to the transmitter buffer
    TXREG = data;
}

// Function to transmit a string over UART
void UART_Write_Text(const char *text)
{
    while (*text != '\0')
    {
        UART_Write(*text++);
    }
}

// Function to receive a single character over UART
uint8_t UART_Read(void)
{
    // Wait until data is received
    while (!RCIF)
        ;

    // Read and return the received data
    return RCREG;
}

// Function to receive a string over UART until Enter key is pressed
void UART_Read_Text(char *buffer, uint8_t max_length)
{
    uint8_t i = 0;
    char received_char;

    // Receive characters until Enter key is pressed or buffer is full
    do
    {
        received_char = UART_Read();
        if (received_char != '\r' && received_char != '\n')
        {
            buffer[i++] = received_char;
        }
    } while (received_char != '\r' && received_char != '\n' && i < max_length - 1);

    // Null-terminate the string
    buffer[i] = '\0';
}