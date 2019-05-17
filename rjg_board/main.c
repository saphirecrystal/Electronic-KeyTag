#include <msp430.h>
#include <LIS3DH.h>
#include <Key_chain.h>
#include <inttypes.h>

uint8_t ST_SP_FLAG = 0;             //Start/Stop Timer -STSP flag
uint8_t PERIOD_COUNT = 0;           //Number of times the timer counts to a
                                    //set period.
uint8_t CLICK_COUNT = 0;            //Number of times the switch is clicked
uint8_t TIME_UP = 0;                //Flag to check if timer has reached
                                    //total number of cycles.

uint16_t count = 0;
uint8_t single_click = 0;
uint8_t single_count = 0;
uint8_t long_press = 0;
uint8_t long_count = 0;
uint8_t i_count = 0;
uint8_t shut_down = 0;
uint8_t very_long_count = 0;
uint8_t very_long_press = 0;
uint8_t data_flag = 0;
uint16_t RXData;
uint16_t Data;
//==================================================================//
//--------------------------Main Function---------------------------//
//==================================================================//
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    GPIO_init();                            //Initializing GPIO
    initClockTo1MHz();                      //Initializing clock to 1MHz
    I2C_init();                             //Initializing I2C clock
    I2C_config_Accelerometer();             //Initializing the Accelerometer

    Boost_disable();
    Init_RTC(ONE_HOUR);                     //Initializing RTC clock
    while(!(RTCCNT & 25));                  //Enable Interrupts after 5 seconds of start up.
    Switch_enableInterrupt();
    Sensor_enableInterrupt();
    //__bis_SR_register(LPM3_bits | GIE);     //Enter LPM /w Interrupts
    __bis_SR_register(GIE);                   //Enter LPM /w Interrupts

    while(1)
    {
        //If System is not shut down
        if(!shut_down)
        {
            //============================================================
            //-------------check if timer overflowed 15 times-------------
            //============================================================
            if((PERIOD_COUNT < 16) && TIME_UP == 1)
            {
                //Start the timer every time it
                //counts up to preset period.
                Init_TIMA0(TWO_SECOND, ONE_SECOND);
                //Clear the TIME_UP Flag.
                TIME_UP = 0;
            }
            else if(PERIOD_COUNT == 16)
            {
                //-------------------------------
                //Reset system when the timer has
                //counted required number of times.
                //--------------------------------
                Boost_disable();            //Disable the boost voltage
                Buzzer_stop();              //Stop the Buzzer
                P1OUT &= ~BIT1;             //Turn off GREEN LED
                P2OUT &= ~BIT2;             //Turn off BLUE LED
                P1OUT &= ~BIT0;             //Turn off RED LED
                ST_SP_FLAG = 0;             //Clear flags.
                TIME_UP = 0;
                Init_RTC(ONE_HOUR);         //Restart RTC for one hour.
                PERIOD_COUNT = 0;           //Clear the Period count
            }
            //============================================================

            //============================================================
            //----------------------Single Click--------------------------
            //============================================================
            if(single_click)
            {
                if(single_count == 1)
                {
                    if(PERIOD_COUNT != 0)
                    {
                        Buzzer_stop();
                        TIMA0_stop();
                        P1OUT &= ~(BIT0 + BIT1);
                        P2OUT &= ~BIT2;
                        PERIOD_COUNT = 0;
                     }

                     Boost_enable();
                     P1OUT |= BIT1;
                     //P2OUT |= BIT2;
                     //Sensor interrupt is disabled in ISR.
                }
                else if(long_count == 1 && single_count == 1)
                {
                    //Enter this section if the Long press mode
                    //was On and interrupted by single click
                    P1OUT &= ~(BIT0 + BIT1);
                    P2OUT &= ~BIT2;
                    if(PERIOD_COUNT != 0)
                    {
                       Buzzer_stop();
                       TIMA0_stop();
                       P1OUT &= ~(BIT0 + BIT1);
                       P2OUT &= ~BIT2;
                       PERIOD_COUNT = 0;
                    }
                    P1OUT |= BIT0 + BIT1;
                    P2OUT |= BIT2;
                    long_count = 0;
                    //Sensor interrupt is disabled in ISR.
                }
                else if(single_count == 2)
                {
                    P1OUT &= ~(BIT0 + BIT1);
                    P2OUT &= ~BIT2;
                    Boost_disable();
                    CLICK_COUNT = 0;
                    Init_RTC(ONE_HOUR);
                    Sensor_enableInterrupt();
                    single_count = 0;
                }
                single_click = 0;
            }
            //============================================================
            //-----------------------LONG PRESS---------------------------
            //============================================================
            else if(long_press)
            {
                if(long_count == 1)
                {
                    //Sensor interrupt is disabled in ISR.
                    if(PERIOD_COUNT != 0)
                    {
                        Buzzer_stop();
                        TIMA0_stop();
                        P1OUT &= ~(BIT0 + BIT1);
                        P2OUT &= ~BIT2;
                        PERIOD_COUNT = 0;
                    }
                    Boost_enable();
                    for(i_count = 3; i_count > 0; i_count--)
                    {
                        P1OUT |= BIT1;
                        __delay_cycles(30000);
                        P1OUT &= ~BIT1;
                        //__delay_cycles(30000);
                    }
                    Sensor_enableInterrupt();
                    //Switch interrupt is enabled when sensor IFG is cleared.
                }
                //Enter this section if the Single Click mode
                //was On and interrupted by Long press
                else if(single_count == 1 && long_count == 1)
                {
                    P1OUT &= ~(BIT0 + BIT1);
                    P2OUT &= ~BIT2;
                    if(PERIOD_COUNT != 0)
                    {
                        Buzzer_stop();
                        TIMA0_stop();
                        P1OUT &= ~(BIT0 + BIT1);
                        P2OUT &= ~BIT2;
                        PERIOD_COUNT = 0;
                    }
                    Boost_enable();
                    for(i_count = 3; i_count > 0; i_count--)
                    {
                        P1OUT |= BIT1;
                        __delay_cycles(30000);
                        P1OUT &= ~BIT1;
                        //__delay_cycles(30000);
                    }
                    Sensor_enableInterrupt();
                    //Switch interrupt is enabled when sensor IFG is cleared.
                    single_count = 0;
                }
                else if(long_count == 2)
                {
                    for(i_count = 3; i_count > 0; i_count--)
                    {
                        P1OUT |= BIT0;
                        __delay_cycles(30000);
                        P1OUT &= ~BIT0;
                        //__delay_cycles(30000);
                    }
                    P1OUT &= ~(BIT0 + BIT1);
                    P2OUT &= ~BIT2;
                    Boost_disable();
                    CLICK_COUNT = 0;
                    Init_RTC(ONE_HOUR);
                    Sensor_enableInterrupt();
                    long_count = 0;
                }
                long_press = 0;
            }
            //============================================================
            //---------------------VERY LONG PRESS------------------------
            //============================================================
            else if(very_long_press)
            {
               if(very_long_count == 1)
               {
                   RTC_stop();
                   Boost_disable();
                   Sensor_disableInterrupt();
                   Switch_enableInterrupt();
                   shut_down = 1;
               }
               else if(very_long_count == 2)
               {
                   Boost_disable();
                   Init_RTC(ONE_HOUR);                     //Initializing RTC clock
                   while(!(RTCCNT & 25));         //Enable Interrupts after 5 seconds of start up.
                   Switch_enableInterrupt();
                   Sensor_enableInterrupt();
                   CLICK_COUNT = 0;
                   very_long_count = 0;
               }
               very_long_press = 0;
            }
            //============================================================
        }
    }
}

//==================================================================
//----------------------PORT 1 - ISR--------------------------------
//==================================================================
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

    //============================================================
    //------------------SWITCH INTERRUPT--------------------------
    //============================================================
   if((P1IFG & BIT3) == BIT3)
   {
       CLICK_COUNT = CLICK_COUNT +1;
       P1IE  &= ~SENSOR_INTERRUPT;       //Sensor_disableInterrupt();
       RTCCTL &= ~ RTCSS_3;              //Stop RTC
       Init_timer(TEN_SECOND);                     //clear all settings. set timer for 2 seconds.
       TA0CTL   |= MC__UP | TACLR;       //Start Timer
       while(!(P1IN & BIT3));            //Wait for switch release.

       TA0CTL &= ~MC__UPDOWN;            //Stop the timer after the Switch is released.
       count = TA0R;                     //Read the time that the switch was held for.
       TA0R = 0;                         //Clear the count.
       //Check for the range of Counter value.
       //Long Press if switch is held longer than a second.
       if(count > FIFTEEN_HUNDRED_MS && count <= FIVE_SECOND && !shut_down)
       {
          long_press = 1;
          long_count = long_count + 1;
          count = 0;
       }
       //Single click if Switch is held less that a 800ms.
       else if(count > 0 && count <= FIFTEEN_HUNDRED_MS && !shut_down)
       {
          single_click = 1;
          single_count = single_count +1;
          count = 0;
       }
       //Shut down if the switch is held for 5 seconds
       else if(count > FIVE_SECOND && count <= TEN_SECOND)
       {
           very_long_press = 1;
           very_long_count = very_long_count +1;
           TA0CTL &= ~TAIFG;
           Init_timer(ONE_SECOND);
           TA0CTL   |= MC__UP | TACLR;        //Start Timer
           P1OUT |= BIT2;                     //Enable Boost
           P1OUT |= BIT0;                     //Red LED On
           while(!(TA0CTL & TAIFG));
           TA0CTL &= ~MC__UPDOWN;             //Stop the Timer.
           TA0CTL &= ~TAIFG;
           P1OUT &= ~BIT0;                    //Red LED Off
           P1OUT &= ~BIT2;                    //Disable Boost
           if(very_long_count == 2 && shut_down == 1)
           {
               shut_down = 0;
           }
           count = 0;
           //RESET;
       }

       //Clear interrupt
       P1IFG &= ~BIT3;
   }
   //============================================================

   //============================================================
   //--------------------SENSOR INTERRUPT------------------------
   //============================================================
   else if((P1IFG & BIT4) == BIT4)
   {
       P1IE  &= ~BIT3;                       //Switch_disableInterrupt();
       if(CLICK_COUNT == 0)
       {
           RTCCTL &= ~ RTCSS_3;              //Stop RTC
           if(PERIOD_COUNT != 0)
           {
               Boost_disable();
               Buzzer_stop();
               TIMA0_stop();
               P1OUT &= ~(BIT0 + BIT1);
               P2OUT &= ~BIT2;
               PERIOD_COUNT = 0;
           }
           Init_RTC(ONE_HOUR);
       }
       if(long_count == 1)
       {
           RXData = I2C_ReadRegister(LIS3DH_INT1_SRC);

           switch(RXData)
           {
               case AXIS_Z_H:
                   P2OUT |= BIT2;
                   P1OUT &= ~BIT0;
                   P1OUT &= ~BIT1;
                   break;
               case AXIS_Z_L:
                   P2OUT |= BIT2;
                   P1OUT &= ~BIT0;
                   P1OUT &= ~BIT1;
                   break;
               case AXIS_Y_H:
                   P1OUT |= BIT1;
                   P1OUT &= ~BIT0;
                   P2OUT &= ~BIT2;
                   break;
               case AXIS_Y_L:
                   P1OUT |= BIT1;
                   P1OUT &= ~BIT0;
                   P2OUT &= ~BIT2;
                   break;
               case AXIS_X_H:
                   P1OUT |= BIT0;
                   P1OUT &= ~BIT1;
                   P2OUT &= ~BIT2;
                   break;
               case AXIS_X_L:
                   P1OUT |= BIT0;
                   P1OUT &= ~BIT1;
                   P2OUT &= ~BIT2;
                   break;
               case AXIS_Z_H_O :
                   P2OUT |= BIT2;
                   P1OUT &= ~BIT0;
                   P1OUT &= ~BIT1;
                   break;
               case AXIS_Z_L_O:
                   P2OUT |= BIT2;
                   P1OUT &= ~BIT0;
                   P1OUT &= ~BIT1;
                   break;
               case AXIS_Y_H_O:
                   P1OUT |= BIT1;
                   P1OUT &= ~BIT0;
                   P2OUT &= ~BIT2;
                   break;
               case AXIS_Y_L_O :
                   P1OUT |= BIT1;
                   P1OUT &= ~BIT0;
                   P2OUT &= ~BIT2;
                   break;
               case AXIS_X_H_O:
                   P1OUT |= BIT0;
                   P1OUT &= ~BIT1;
                   P2OUT &= ~BIT2;
                   break;
               case AXIS_X_L_O:
                   P1OUT |= BIT0;
                   P1OUT &= ~BIT1;
                   P2OUT &= ~BIT2;
                   break;
               default:
                   break;
           }

       }

       P1IE  |= BIT3;                 //Switch_enableInterrupt();
       P1IFG &= ~BIT4;                // Clear P1.4 IFG
   }
}

//===============================================================
//----------------------------RTC ISR----------------------------
//===============================================================
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = RTC_VECTOR
__interrupt void RTC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(RTC_VECTOR))) RTC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(RTCIV, RTCIV_RTCIF))
    {
        case RTCIV_NONE : break;                         // No interrupt pending
        case RTCIV_RTCIF:                                // RTC Overflow
             RTCCTL &= ~ RTCSS_3;                        //Stop RTC
             //Initializes timer with interrupts enabled.
             Init_TIMA0(TWO_SECOND, ONE_SECOND);         //Timer to control LED and Buzzer
             Init_Buzzer(BUZZER_FREQUENCY, BUZZER_DUTYCYCLE);
             RTCCTL &= ~RTCIF;
            break;

        default:          break;
    }
}
//===============================================================


//===============================================================
//-----------------------TIMER0 A ISR----------------------------
//===============================================================
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A1_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    //When the RTC overflows
    //Flash LED's with DIfferent Colors and Beep
    if(TA0CTL &= TAIFG)
    {
        //uint8_t red = 0, blue = 0, green  = 0;
            Boost_enable();

            PERIOD_COUNT = PERIOD_COUNT + 1;

            if(PERIOD_COUNT == 1 || PERIOD_COUNT <= 15)
            {
                if((PERIOD_COUNT == 1 || PERIOD_COUNT == 4 || PERIOD_COUNT == 7 || PERIOD_COUNT == 10 || PERIOD_COUNT == 13) && TIME_UP == 0)
                {
                    P1OUT &= ~BIT1;
                    P2OUT &= ~BIT2;
                    P1OUT |= BIT0;
                    TIME_UP = 1;
                }
                else if((PERIOD_COUNT == 2 || PERIOD_COUNT == 5 || PERIOD_COUNT == 8 || PERIOD_COUNT == 11 || PERIOD_COUNT == 14) && TIME_UP == 0)
                {
                    P1OUT ^= BIT1;
                    P2OUT &= ~BIT2;
                    P1OUT &= ~BIT0;
                    TIME_UP = 1;
                }
                else if((PERIOD_COUNT == 3 || PERIOD_COUNT == 6 || PERIOD_COUNT == 9 || PERIOD_COUNT == 12 || PERIOD_COUNT == 15) && TIME_UP == 0)
                {
                    P1OUT &= ~BIT1;
                    P2OUT |= BIT2;
                    P1OUT &= ~BIT0;
                    TIME_UP = 1;
                }

                ST_SP_FLAG ^= ST_SP;
                Buzzer(ST_SP_FLAG);
            }
        TA0CTL &= ~TAIFG;
    }
}
//===============================================================

