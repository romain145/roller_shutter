/*
 * File:   main.c
 * Author: Romain
 *
 * Created on 07 August 2019, 16:56
 */

#define _XTAL_FREQ     4000000

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include "main.h"

// inputs
#define PROG_BUTTON     RA7
#define START_BUTTON    RB4

// outputs
#define PROG_LED        RB1
#define RELAY_CONTROL   RA0
#define RELAY1          RB5
#define RELAY2          RB2


void main(void) {
    static int status=0;
    static int up=0;
    
    //CMCON = 0b00000111;                 // Disable comparators to enable RA0-RA3 input
    TRISB1=0; // set LED as output
    TRISA0=0; // set RELAY_CONTROL
    TRISB5=0; // set RELAY1 as output
    TRISB2=0; // set RELAY2 as output
    
    PROG_LED = 0; // turn ON prog LED at startup
    __delay_ms(500);
    
    while(START_BUTTON == 0) // if button pressed, stay locked
    {
        PROG_LED = 0;
        __delay_ms(100);
        PROG_LED = 1;
        __delay_ms(100);
    }
    
    RELAY_CONTROL=1; // enable relays
    
    while(1)
    {
        if(START_BUTTON == 1) // button released, stop all
        {
            RELAY1 = 0;
            RELAY2 = 0;
            PROG_LED = 1; // turn OFF prog LED
            status = 0; // reset state machine
        }
        
        switch(status)
        {
        
            case 0:
                if(START_BUTTON == 0)
                {
                    __delay_ms(100); // debounce for 100ms
                    if(START_BUTTON == 0)
                    {
                        status = 1;
                    }
                }
                
                break;
            
            case 1:
                if(up == 0)
                {
                    RELAY1 = 1;
                    PROG_LED = 0;
                }
                else
                {
                    RELAY2 = 1;
                    PROG_LED = 0;
                }
                while(START_BUTTON == 0);
                RELAY1 = 0;
                RELAY2 = 0;
                up ^= 1; // inverse direction
                status = 0; // reset state machine
                break;
        }

    }
}
