/*
 * FUNCTIONS.c
 *
 *  Created on: May 6, 2019
 *      Author: Raymond
 */

#include <msp430.h>
#include <LIS3DH.h>


void RED_LED_ON()
{
    if((P1OUT &= BIT1) || (P2OUT &= BIT2))
    {
        P1OUT &= ~BIT1;
        P2OUT &= ~BIT2;
        P1OUT |= BIT0;
    }
    else
    {
        P1OUT |= BIT0;
    }
}

void GREEN_LED_ON()
{
    if((P1OUT &= BIT0) || (P2OUT &= BIT2))
    {
        P1OUT &= ~BIT0;
        P2OUT &= ~BIT2;
        P1OUT |= BIT1;
    }
    else
    {
        P1OUT |= BIT1;
    }
}

void BLUE_LED_ON()
{
    if((P1OUT &= BIT0) || (P1OUT &= BIT1))
    {
        P1OUT &= ~BIT0;
        P1OUT &= ~BIT1;
        P2OUT |= BIT2;
    }
    else
    {
        P2OUT |= BIT2;
    }
}

void RED_LED_OFF()
{
    P1OUT &= ~BIT0;
}

void GREEN_LED_OFF()
{
    P1OUT &= ~BIT1;
}

void BLUE_LED_OFF()
{
    P2OUT &= ~BIT2;
}

void Boost_enable()
{
	P1OUT |= BIT2;
}

void Boost_disable()
{
	P1OUT &= ~BIT2;
}










