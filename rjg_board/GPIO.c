/*
 * GPIO.c
 *
 *  Created on: May 6, 2019
 *      Author: Raymond
 */

#include <msp430.h>
#include <LIS3DH.h>

void GPIO_init()
{
    P1DIR &= ~CLEAR_ALL;
    P2DIR &= ~CLEAR_ALL;

    P1OUT &= ~CLEAR_ALL;
    P2OUT &= ~CLEAR_ALL;

    //O/P Pins
    P1DIR |= BIT0 + BIT1 + BIT2;      //P1.0 -> RED LED
                                      //P1.1 -> GREEN LED
                                      //P1.2 -> Boost Enable Control
    P2DIR |= BIT2 + BIT3;             //P2.2 -> BLUE LED
                                      //P2.3 -> BUZZER
                                      //I/P Pins
    //P1DIR &= ~(BIT3 + BIT4 + BIT5); //P1.3 -> Switch
                                      //P1.4 -> INT_1 accelerometer
                                      //P1.5 -> INT_2 accelerometer
                                      //Clear all
                                      //Function select set to GPIO Default
    P1SEL0 &= ~CLEAR_ALL;
    P1SEL1 &= ~CLEAR_ALL;
    P2SEL0 &= ~CLEAR_ALL;
    P2SEL1 &= ~CLEAR_ALL;
                                    //Switch Configuration.
    P1OUT |= BIT3;                  // --
    //P1REN |= BIT3;                  // --
    P1IES |= BIT3;
    

    SYSCFG2 |= USCIBRMP;            // remapping configuration
    P2SEL1 |= BIT5 | BIT6;          //I2C pins
    P2SEL0 |= BIT3;                 //P2.3 -> TA1.2 Buzzer

    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
                                    // to activate previously configured port settings
}


void Sensor_enableInterrupt()
{
    P1IE  |= BIT4;
}

void Sensor_disableInterrupt()
{
    P1IE  &= ~BIT4;
}

void Sensor_clearInterrupt()
{
    P1IFG &= ~BIT4;
}

void Switch_enableInterrupt()
{
    P1IE  |= BIT3;
}

void Switch_disableInterrupt()
{
    P1IE  &= ~BIT3;
}

void Switch_clearInterrupt()
{
    P1IFG &= ~BIT3;
}

