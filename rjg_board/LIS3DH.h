/*
 * LIS3DH.h
 *
 *  Created on: Apr 26, 2019
 *      Author: Raymond
 */

#define CLEAR_ALL (0xFF)

//Slave Address
#define LIS3DH_SLAVE_ADDRESS (0x18) //18


//Register Address Map
#define LIS3DH_TEMP_CFG_REG                 (0x1F) // Enable temp/ADC
#define LIS3DH_CTRL_REG1                    (0x20) // Data rate, normal/low power mode, enable xyz axis
#define LIS3DH_CTRL_REG2                    (0x21) // HPF config
#define LIS3DH_CTRL_REG3                    (0x22) // Int1 interrupt type enable/disable
#define LIS3DH_CTRL_REG4                    (0x23) // BDU, endian data sel, range, high res mode, self test, SPI 3 or 4 wire
#define LIS3DH_CTRL_REG5                    (0x24) // boot, FIFO enable, latch int1 & int2, 4D enable int1 & int2 with 6D bit set
#define LIS3DH_CTRL_REG6                    (0x25) // int2 interrupt settings, set polarity of int1 and int2 pins
#define LIS3DH_OUT_X_L_INCR                 (0xA8) //
#define LIS3DH_OUT_X_L                      (0x28)
#define LIS3DH_OUT_X_H                      (0x29)
#define LIS3DH_OUT_Y_L                      (0x2A)
#define LIS3DH_OUT_Y_H                      (0x2B)
#define LIS3DH_OUT_Z_L                      (0x2C)
#define LIS3DH_OUT_Z_H                      (0x2D)
#define LIS3DH_FIFO_CTRL_REG                (0x2E)
#define LIS3DH_FIFO_SRC_REG                 (0x2F)
#define LIS3DH_INT1_CFG                     (0x30)
#define LIS3DH_INT1_SRC                     (0x31)
#define LIS3DH_INT1_THS                     (0x32)
#define LIS3DH_INT1_DURATION                (0x33)
#define LIS3DH_CLICK_CFG                    (0x38)
#define LIS3DH_CLICK_SRC                    (0x39)
#define LIS3DH_CLICK_THS                    (0x3A)
#define LIS3DH_TIME_LIMIT                   (0x3B)
#define LIS3DH_TIME_LATENCY                 (0x3C)
#define LIS3DH_TIME_WINDOW                  (0x3D)
#define LIS3DH_WHO_AM_I                     (0x0F)

//CTRL_REG1 (0x20)
#define LIS3DH_ODR_0Hz                      (0x00) //Power Down Mode
#define LIS3DH_ODR_1Hz                      (0x10) //1Hz
#define LIS3DH_ODR_10Hz                     (0x20) //10Hz
#define LIS3DH_ODR_25Hz                     (0x30) //25Hz
#define LIS3DH_ODR_50Hz                     (0x40) //50Hz
#define LIS3DH_ODR_100Hz                    (0x50) //100Hz
#define LIS3DH_ODR_200Hz                    (0x60) //200Hz
#define LIS3DH_ODR_400Hz                    (0x70) //400Hz
#define LIS3DH_ODR_LPM                      (0x80) //1.6KHz LPM
#define LIS3DH_ODR_HR                       (0x90) //1.344KHz High Resolution

#define LIS3DH_X_EN                         (0x01) //X axis enabled
#define LIS3DH_Y_EN                         (0x02) //Y axis enabled
#define LIS3DH_Z_EN                         (0x04) //Z axis enabled
#define LIS3DH_LP_EN                        (0x08) //LP mode enabled
#define LIS3Dh_XYZ_EN                       (0x07) //Default Value


// CTRL_REG2 (0x21) - High Pass Filter values
#define LIS3DH_HPF_DISABLED                 (0x00)
#define LIS3DH_HPF_AOI_INT1                 (0x01)
#define LIS3DH_HPF_AOI_INT2                 (0x02)
#define LIS3DH_HPF_CLICK                    (0x04)
#define LIS3DH_HPF_FDS                      (0x08)

#define LIS3DH_HPF_CUTOFF1                  (0x00)
#define LIS3DH_HPF_CUTOFF2                  (0x10)
#define LIS3DH_HPF_CUTOFF3                  (0x20)
#define LIS3DH_HPF_CUTOFF4                  (0x30)

#define LIS3DH_HPF_DEFAULT_MODE             (0x00)
#define LIS3DH_HPF_REFERENCE_SIGNAL         (0x40)
#define LIS3DH_HPF_NORMAL_MODE              (0x80)
#define LIS3DH_HPF_AUTORESET_ON_INTERRUPT   (0xC0)

//CTRL_REG3 (0x22h) - Interrupt Enable
#define LIS3DH_I1_CLICK                     (0x80) //Click interrupt on INT1
#define LIS3DH_I1_IA1                       (0x40) //IA1 interrupt on INT1
#define LIS3DH_I1_IA2                       (0x20) //IA2 interrupt on INT1
#define LIS3DH_I1_ZYXDA                     (0x10) //ZYXDA interrupt on INT1
#define LIS3DH_I1_32IDA                     (0x08) //321DA interrupt on INT1. Default value: 0
#define LIS3DH_I1_WTM                       (0x04) //FIFO watermark interrupt on INT1. Default value: 0
#define LIS3DH_I1_OVERRUN                   (0x02) //FIFO overrun interrupt on INT1

//CTRL_REG4 (0x23h) - Interrupt Enable
#define LIS3DH_BDU                          (0x80) //Block data update
#define LIS3DH_BLE                          (0x40) //Big/little endian data selection
                                                   //Full-scale selection
#define LIS3DH_FS_2g                        (0x00) //+/- 2g
#define LIS3DH_FS_4g                        (0x10) //+/- 4g
#define LIS3DH_FS_8g                        (0x20) //+/- 8g
#define LIS3DH_FS_16g                       (0x30) //+/- 16g
#define LIS3DH_HR                           (0x08) //High-resolution output mode
                                                   //Self-test enable
#define LIS3DH_ST_NM                        (0x00) //Normal mode
#define LIS3DH_ST0                          (0x02) //Self-test 0
#define LIS3DH_ST1                          (0x04) //Self-test 1
#define LIS3DH_SIM                          (0x01) //SPI serial interface mode selection

//INT1_THS (0x32)
#define LIS3DH_THS0                         (0x01)
#define LIS3DH_THS1                         (0x02)
#define LIS3DH_THS2                         (0x04)
#define LIS3DH_THS3                         (0x08)
#define LIS3DH_THS4                         (0x10)
#define LIS3DH_THS5                         (0x20)
#define LIS3DH_THS6                         (0x40)

//INT1_DURATION (0x33)
#define LIS3DH_DUR_0                        (0x00)
#define LIS3DH_DUR_1                        (0x01)
#define LIS3DH_DUR_2                        (0x02)
#define LIS3DH_DUR_3                        (0x03)
#define LIS3DH_DUR_4                        (0x04)
#define LIS3DH_DUR_5                        (0x05)
#define LIS3DH_DUR_6                        (0x06)
#define LIS3DH_DUR_7                        (0x07)
#define LIS3DH_DUR_8                        (0x08)
#define LIS3DH_DUR_9                        (0x09)
#define LIS3DH_DUR_10                       (0x0A)
#define LIS3DH_DUR_11                       (0x0B)
#define LIS3DH_DUR_12                       (0x0C)
#define LIS3DH_DUR_13                       (0x0D)
#define LIS3DH_DUR_14                       (0x0E)
#define LIS3DH_DUR_15                       (0x0F)

//INT1_CFG & INT2_CFG (0x34) Enable Interrupt Generation
#define LIS3DH_X_LOW                        (0x01)
#define LIS3DH_X_HIGH                       (0x02)
#define LIS3DH_Y_LOW                        (0x04)
#define LIS3DH_Y_HIGH                       (0x08)
#define LIS3DH_Z_LOW                        (0x10)
#define LIS3DH_Z_HIGH                       (0x20)
#define LIS3DH_SIX_D                        (0x40)
#define LIS3DH_AOI                          (0x80)
#define LIS3DH_XYZ_LH                       (0x7F)

//FIFO_CTRL_REG - (0x2E)
#define LIS3DH_FIFO_BYPASS_MODE             (0x00)
#define LIS3DH_FIFO_FIFO_MODE               (0x40)
#define LIS3DH_FIFO_STREAM_MODE             (0x80)
#define LIS3DH_FIFO_STREAM_TO_FIFO_MODE     (0xC0)

// CLICK_SRC (0x39) - Click Detection values
#define LIS3DH_SINGLE_CLICK                 (0x15)
#define LIS3DH_DOUBLE_CLICK                 (0x2A)

#define LIS3DH_MODE_NORMAL                  (0x00)
#define LIS3DH_MODE_LOW_POWER               (0x01)
#define LIS3DH_MODE_HIGH_RESOLUTION         (0x02)

#define LIS3DH_ADC1                         (0x01)
#define LIS3DH_ADC2                         (0x02)
#define LIS3DH_ADC3                         (0x03)

//INT1_SRC & INT2_SRC (0x35) - Interrupt mask
#define AXIS_Z_H                            (0x20)
#define AXIS_Z_L                            (0x10)
#define AXIS_Y_H                            (0x08)
#define AXIS_Y_L                            (0x04)
#define AXIS_X_H                            (0x02)
#define AXIS_X_L                            (0x01)

#define AXIS_Z_H_O                          (0x60)
#define AXIS_Z_L_O                          (0x50)
#define AXIS_Y_H_O                          (0x48)
#define AXIS_Y_L_O                          (0x44)
#define AXIS_X_H_O                          (0x42)
#define AXIS_X_L_O                          (0x41)

#define INTERRUPT_BIT                       (0x40)

/*
//CTRL_REG1 (0x20)
#define ODR_400HZ (0x77)
#define IA1_EN (0x40)
#define FS_4G (0x10) //10 w/o self test mode
#define XYZ_INT_EN (0x7F)
#define THS_32MG (0x20)
#define DURATION (0x0F)*/
