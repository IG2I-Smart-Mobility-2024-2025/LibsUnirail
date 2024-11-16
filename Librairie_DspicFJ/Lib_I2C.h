/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    Lib_I2C.h

  @Summary:
    This is the Lib_I2C.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.75.1
        Device            :  dsPIC33FJ128MC802
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.10

 * Created on 21 novembre 2018
 */

#ifndef H_LIB_I2C
#define H_LIB_I2C

/*	Adresses des registres du MCP23008										*/
#define	MCP23008_IODIR          	0x00
#define	MCP23008_IPOL				0x01
#define	MCP23008_GPINTEN        	0x02
#define	MCP23008_DEFVAL         	0x03
#define	MCP23008_INTCON         	0x04
#define	MCP23008_IOCON          	0x05
#define	MCP23008_GPPU				0x06
#define	MCP23008_INTF				0x07
#define	MCP23008_INTCAP         	0x08
#define MCP23008_GPIO				0x09
#define MCP23008_OLAT				0x0A


/*	Adresses des registres du PCA9551										*/
#define	PCA9551_INPUT           	0x00
#define	PCA9551_PSC0            	0x01
#define	PCA9551_PWM0            	0x02
#define	PCA9551_PSC1            	0x03
#define	PCA9551_PWM1            	0x04
#define	PCA9551_LS0             	0x05
#define	PCA9551_LS1             	0x06

#define AdressMCP23008OutLed		0x4E
#define AdressMCP23008Switch		0x4C

#define MCP23008_ROUECODEUSE_W      0x4C
#define MCP23008_BARGRAPH_W			0x4A
#define MCP23008_DIP_SWITCH_W		0x4E
#define	ADDR_PCA9551_W				0xCE


//EEPROM
#define	ADDR_EEPROM_W				0xA0
#define PAGE_SYZE					64


#define FreqI2C_100K_Fosc_80MHz 395
#define FreqI2C_200K_Fosc_80MHz 197

#define FreqI2C_100K_Fosc_10MHz 49
#define FreqI2C_200K_Fosc_10MHz 25

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void InitMasterI2C(unsigned int frequence);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void MyStartI2C(void);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
unsigned int MyAckI2C(void);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void MyNotAckI2C(void);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void AckI2C(void);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void MyRestartI2C(void);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void MyStopI2C(void);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
int MyWriteI2C(unsigned char byte);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
unsigned char MyReadI2C(void);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void EEPROM_ByteWriteI2C(unsigned int Add, unsigned char data);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
unsigned char EEPROM_ByteReadI2C(unsigned int Add);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void EEPROM_SequentialReadI2C(unsigned int Add, unsigned char *rdptr, unsigned char length);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void EEPROMPageWriteI2C(unsigned int Add, unsigned char *wrptr, unsigned char length);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:       
 *                                                                             
 *    Arguments:		
 * 
 *                                             
 *    Return Value:                                                                                
 ******************************************************************************/
void RAM_Write(unsigned int Add, unsigned char *ptr1, unsigned char length);

#endif

