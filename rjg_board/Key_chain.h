/*
 * Key_chain.h
 *
 *  Created on: May 6, 2019
 *      Author: Raymond
 */

#include <msp430.h>
#include <LIS3DH.h>
#include <inttypes.h>

#define ST_SP  (1)

#define BUZZER_FREQUENCY   (45)   //2700 Hz Period
#define BUZZER_DUTYCYCLE   (3)    //6% Duty Cycle

//Timer A0
#define HALF_SECOND        (2053)
#define ONE_SECOND         (4105)
#define TWO_SECOND         (8212)
#define THREE_SECOND       (12288)
#define FIVE_SECOND        (20480)
#define TEN_SECOND         (40960)
#define EIGHT_HUNDRED_MS   (3277)
#define SIX_HUNDRED_MS     (2458)
#define FIFTEEN_HUNDRED_MS (6144)

//RTC
#define HALF_MINUTE        (300)
#define ONE_MINUTE         (585)
#define HALF_HOUR          (17578)
#define ONE_HOUR           (35156)
#define TWO_HOUR           (65536) //MAX time

//GPIO
#define RED_LED                    (0x0001) //BIT0 P1.0
#define GREEN_LED                  (0x0002) //BIT1 P1.1
#define BOOST_REGULATOR            (0x0004) //BIT2 P1.2
#define SWITCH                     (0x0008) //BIT3 P1.3
#define SENSOR_INTERRUPT           (0x0010) //BIT4 P1.4
#define BLUE_LED                   (0x0004) //BIT2 P2.2
#define BUZZER                     (0x0008) //BIT3 P2.3

//===================================================
//-----------------------GPIO.c----------------------
//===================================================
void GPIO_init();
void Sensor_enableInterrupt();
void Sensor_disableInterrupt();
void Sensor_clearInterrupt();
void Switch_enableInterrupt();
void Switch_disableInterrupt();
void Switch_clearInterrupt();

//===================================================
//-----------------------CLOCK.c---------------------
//===================================================
void initClockTo1MHz();
void initClockTo16MHz();
//===================================================

//===================================================
//-----------------------I2C.c-----------------------
//===================================================
void I2C_init();
unsigned char I2C_ReadRegister(unsigned char Address);
unsigned char I2C_WriteRegister(unsigned char Address, unsigned char Data);
void I2C_config_Accelerometer();
//===================================================

//===================================================
//-----------------------RTC.c-----------------------
//===================================================
//Timer for Real Time Clock Counter
void RTC_init(uint16_t clockPredivider);
void RTC_start(uint16_t clockSource);
void RTC_stop();
void RTC_setModulo(uint16_t modulo);
void RTC_enableInterrupt(uint8_t interruptMask);
void RTC_disableInterrupt(uint8_t interruptMask);
uint8_t RTC_getInterruptStatus(uint8_t interruptFlagMask);
void RTC_clearInterrupt(int8_t interruptFlagMask);
void Init_RTC( uint16_t Time );
//===================================================

//===================================================
//-------------------FUNCTIONS.c---------------------
//===================================================
void RED_LED_ON();
void GREEN_LED_ON();
void BLUE_LED_ON();
void RED_LED_OFF();
void GREEN_LED_OFF();
void BLUE_LED_OFF();
void Boost_enable();
void Boost_disable();
//===================================================

//===================================================
//---------------------TIMER.c-----------------------
//===================================================
//Timer A1.2
void Buzzer_init(uint16_t Period, uint16_t DutyCycle);
void Buzzer_start();
void Buzzer_stop();
void Init_Buzzer(uint16_t Period, uint16_t DutyCycle);
void Buzzer(uint8_t ONOFF);

//Timer A0.1
void TIMA0_init(uint16_t Period, uint16_t DutyCycle);
void TIMA0_has_time();
void TIMA0_stop();
void TIMA0_start();
void Init_timer(uint16_t Time);
void Init_TIMA0(uint16_t Period, uint16_t DutyCycle);
//===================================================
