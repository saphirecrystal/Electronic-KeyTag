/*
 * RTC.c
 *
 *  Created on: May 6, 2019
 *      Author: Raymond
 */

#include <msp430.h>
#include <LIS3DH.h>
#include <inttypes.h>

void RTC_init(uint16_t clockPredivider)
{
    RTCCTL &= ~(RTCSS_3 | RTCPS_7); //XT1 and clock predivider 1024

    RTCMOD &= ~CLEAR_ALL;
    RTCCTL |= clockPredivider;
}

void RTC_start(uint16_t clockSource)
{
    RTCCTL &= ~RTCSS_3;
    RTCCTL |= clockSource;
    RTCCTL |= RTCSR;

}

void RTC_stop()
{
    RTCCTL &= ~ RTCSS_3;
}

void RTC_setModulo(uint16_t modulo)
{
    RTCMOD = modulo;
}

void RTC_enableInterrupt(uint8_t interruptMask)
{
    if (interruptMask & RTCIE)
    {
        RTCCTL |= RTCIE;
    }
}

void RTC_disableInterrupt(uint8_t interruptMask)
{
    if (interruptMask & RTCIE)
    {
        RTCCTL &= ~RTCIE;
    }
}

uint8_t RTC_getInterruptStatus(uint8_t interruptFlagMask)
{
    uint8_t intStatus = 0;

    if (interruptFlagMask & RTCIF)
    {
        intStatus = (uint8_t)(RTCCTL & RTCIF);
    }

    return intStatus;
}

void RTC_clearInterrupt(int8_t interruptFlagMask)
{
    RTCCTL &= ~RTCIF;
}

void Init_RTC( uint16_t Time )
{
    /** Stop the RTC (pseudo) real time clock prior to changing these registers. */
    RTC_stop();

    /** Initialize the RTC to increment the OFS_RTCCNT register once every clock tick.  The
    * Modulo register (RTCMOD) is set to roll over every 4096 clock ticks.
    *   ( The value RTC_CLOCKPREDIVIDER_16 would increment the OFS_RTCNT register once 16
    *     clock ticks. )
    */
    RTC_init( RTCPS__1024 );

    /** Module register (OFS_RTCMOD) is set to roll over every 4096 clock ticks. */
    RTC_setModulo( Time ); //5 min

    /** Enable the RTC interrupt isr to be called when the RTC counter register (OFS_RTCCNT) would
     * exceed the value set into the modulo register.  The RTC counter register is reset to zero
     * prior to the isr being called.
     */
    RTC_enableInterrupt( RTCIE );

    /** Start the RTC clock using the XT1CLK as the timing source. */
    RTC_start( RTCSS__VLOCLK );
}

