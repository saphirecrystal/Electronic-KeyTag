/*
 * I2C.c
 *
 *  Created on: May 6, 2019
 *      Author: Raymond
 */

/*
 * i2c.c
 *
 *  Created on: Apr 26, 2019
 *      Author: Raymond
 */
#include <msp430.h>
#include <LIS3DH.h>


volatile unsigned char RXData;
volatile unsigned char Data;

void I2C_init()
{
    UCB0CTLW0 |= UCSWRST;                   // Software reset enabled
    UCB0CTLW0 |= UCMODE_3 | UCMST | UCSYNC; // I2C mode, Master mode, sync
    UCB0BRW = 0x000A;                       // baudrate = SMCLK / 8
    UCB0I2CSA |= LIS3DH_SLAVE_ADDRESS;      //0011000;// Slave Address
    UCB0CTL1 &= ~UCSWRST;                   // Clear SW reset, resume operation
}

unsigned char I2C_ReadRegister(unsigned char Address)
{
    unsigned char Result;
    //UCB0IFG &= ~(UCTXIFG0|UCRXIFG0);
    // Read data from I2C slave device at the DeviceAddress specified.
    UCB0CTL1 |= UCTR;
    UCB0CTL1 |= UCTXSTT;                    // I2C TX, start condition

    while (!(UCB0IFG & UCTXIFG0));          // Wait for slave address transmit to complete
    UCB0TXBUF = Address;                    // Load TX buffer with register address
    while (!(UCB0IFG & UCTXIFG0));          // Wait for transmit to complete
    UCB0IFG &= ~UCTXIFG0;                   // Clear USCI_B0 TX int flag
    // Send restart with transmit/receive bit NOT set
    UCB0CTL1 &= ~UCTR;                      // Toggle transmitter bit
    UCB0CTL1 |= UCTXSTT;                    // I2C start condition
    while(UCB0CTL1 & UCTXSTT);              // Wait for start to complete
    UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
    while (!(UCB0IFG & UCRXIFG0));          // Wait for receive buffer to fill
    Result = UCB0RXBUF;                     // Fill receive data buffer with received byte
    while (UCB0CTL1 & UCTXSTP);             // Wait for stop condition to complete
    UCB0IFG &= ~UCRXIFG0;                   // Clear USCI_B0 RX int flag
    // Return new data from RX buffer
    return Result;
}

unsigned char I2C_WriteRegister(unsigned char Address, unsigned char Data)
{
    // Write data to I2C slave device at the DeviceAddress specified.
    UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
    while (!(UCB0IFG & UCTXIFG0));          // Wait for slave address transmit to complete
    UCB0TXBUF = Address;                    // Load TX buffer with register address
    while (!(UCB0IFG & UCTXIFG0));          // Wait for transmit to complete
    UCB0TXBUF = Data;                       // Load TX buffer with data byte
    while (!(UCB0IFG & UCTXIFG0));          // Wait for transmit to complete
    UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
    while (UCB0CTL1 & UCTXSTP);             // Wait for stop condition to complete
    UCB0IFG &= ~UCTXIFG0;                   // Clear USCI_B0 TX int flag
    return 0;
}

//Configure the Accelerometer
void I2C_config_Accelerometer()
{
    while (UCB0CTL1 & UCTXSTP);
    //RXData = I2C_ReadRegister(LIS3DH_WHO_AM_I);

    Data = I2C_WriteRegister(LIS3DH_CTRL_REG1, LIS3Dh_XYZ_EN | LIS3DH_ODR_400Hz); //ODR data rate set to 400Hz.

    while (UCB0CTL1 & UCTXSTP);
    Data = I2C_WriteRegister(LIS3DH_CTRL_REG3, LIS3DH_I1_IA1);         //CTRL_REG3 - IA1 interrupt on IA1
    Data = I2C_WriteRegister(LIS3DH_CTRL_REG4, LIS3DH_FS_4g);          //Setting to +/- 4g - full scale selection && self test mode
                                                                       //CTRL_REG4
    //Data = I2C_WriteRegister(LIS3DH_CTRL_REG5, 0x08);                    //Latch interrupt on INT1_SRC - CTRL_REG5
    Data = I2C_WriteRegister(LIS3DH_INT1_CFG, LIS3DH_XYZ_LH );          //INT1_CFG - enable interrupt on XYZ - L/H
    Data = I2C_WriteRegister(LIS3DH_INT1_THS, LIS3DH_THS5);            //INT1_THS Threshold: one LSB @ +/- 4g is 32mg
    Data = I2C_WriteRegister(LIS3DH_INT1_DURATION, LIS3DH_DUR_15);     //INT1_DUR Duration: N/ODR*/
}














