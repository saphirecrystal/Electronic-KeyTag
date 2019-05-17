/*
 * TIMER.c
 *
 *  Created on: May 6, 2019
 *      Author: Raymond
 */


#include <msp430.h>
#include <LIS3DH.h>
#include <inttypes.h>


//===========================================================
//-----------------2700Hz PWM Buzzer Frequency---------------
//===========================================================
void Buzzer_init(uint16_t Period, uint16_t DutyCycle)
{
    //2700 Hz PWM for Buzzer
    TA1CCR0  = Period - 1;                        // PWM Period
    TA1CCTL2 = OUTMOD_7;                      // CCR2 reset/set
    TA1CCR2  = DutyCycle -1;                     // CCR2 PWM duty cycle
    TA1CTL   |= TASSEL__SMCLK | ID_3;         // SMCLK, up mode, clear TAR
}

void Buzzer_start()
{
    //Start timer
    TA1CTL |= MC__UP | TACLR;
}

void Buzzer_stop()
{
    //Halt the timer
    TA1CTL &= ~MC__UPDOWN;
}

//Buzzer
void Init_Buzzer(uint16_t Period, uint16_t DutyCycle)
{
    Buzzer_stop();
    Buzzer_init(Period, DutyCycle);
}

void Buzzer(uint8_t ONOFF)
{
    if(ONOFF == 1)
    {
        Buzzer_start();
    }
    else
    {
        Buzzer_stop();
    }
}
//===========================================================

//===========================================================
//Timer to control the Buzzer/LED/Single/Double switch clicks.
//===========================================================
void TIMA0_init(uint16_t Period, uint16_t DutyCycle)
{
    //One Second timer to control LED's
    TA0CCR0  = Period -1;                         // PWM Period
    TA0CCTL1 = OUTMOD_7;                       // CCR2 reset/set
    TA0CCR1  = DutyCycle;                           // CCR2 PWM duty cycle
    TA0CTL   = TASSEL__ACLK| ID_3;
}

void TIMA0_stop()
{
    TA0CTL &= ~MC__UPDOWN;
}

void TIMA0_start()
{
    //TA0CCTL2 = OUTMOD_7;                       // CCR2 reset/set
    TA0CTL |= MC__UP | TACLR;
}

uint16_t TIMA0_get_time()
{
    uint16_t Timer_value;
    //Get the value in TAxR
    Timer_value = TA0R;

    return Timer_value;
}

//Other
void Init_TIMA0(uint16_t Period, uint16_t DutyCycle)
{
    TIMA0_stop();
    TIMA0_init(Period, DutyCycle);
    TA0CTL |= TAIE;
    //TA0CCTL1 |= CCIE;
    TA0CTL |= MC__UP | TACLR; //Start timer
}

void Init_timer(uint16_t Time)
{
    TA0CTL   = 0;                                //Halt and clear timer
    TA0CCR0  = Time;                            // PWM Period Five Seconds
    TA0CTL   = TASSEL__ACLK| ID_3;               // Clock Select and divider
}
//===========================================================


