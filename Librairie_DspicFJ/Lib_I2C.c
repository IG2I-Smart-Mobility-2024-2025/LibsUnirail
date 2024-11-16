/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    Lib_I2C.c

  @Summary:
    This is the Lib_I2C.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.75.1
        Device            :  dsPIC33FJ128MC802
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05

 * Created on 21 novembre 2018
 */

#include <XC.h>
#include "Lib_I2C.h"





/*********************************************************************
 * Function:        InitPerifI2C
 *
 * Input:		None.
 *
 * Output:		None.
 *
 * Overview:		Generates an I2C Start Condition
 *
 * Note:			None
 ********************************************************************/
void InitMasterI2C(unsigned int frequence) {
    /*Calcul du registre I2CBRG (Vitesse de transfert du bus I2C)
    Version corrigée, coquille dans Doc Mcp
	
    NB: Uniquement en mode MASTER I2C

                            Fcy					Fcy
    I2CBRG = ( ------		-	-----------) - 1
                            Fscl			10,000,000
							
							
    Relation inverse
    On pose K = 10,000,000
	
                            K * Fcy
    Fscl = ------------------
                    K(I2CBRG + 1) +Fcy
					
                            5MHz					5MHz
    I2CBRG = ( ------		-	-------------) - 1 = 48.5d
                            100KHz			10,000,000
	
    Rappel Fcy = Fosc/2
    Tableau récapitulatif avec Vitesse = 100Kbits/s
    |		Fcy = Fosc/2	|	I2C_BRG 								|
    |		Fcy = 40MHz		|	I2C_BRG = 395 ou 0x18B	|
    |		Fcy = 5MHz		|	I2C_BRG = 49  ou 0x31			|	
	
     */

    I2C1CONbits.A10M = 0; //7 bits adress slave (Only Slave mode)

    I2C1MSK = 0; //Match complet

    //	I2C1BRG = 49;		//Vitesse du bus 100KHz à Fosc = 10MHz
    //	I2C1BRG = 25;		//Vitesse du bus 200KHz à Focs = 10MHz
    I2C1BRG = frequence; //Vitesse du bus 100KHz à Fosc = 80MHz

    I2C1CONbits.IPMIEN = 0; //IPMI support mode disabled
    I2C1CONbits.DISSLW = 1; //Slew rate control mode disable
    I2C1CONbits.SMEN = 0; //Disable SMBus input thresholds
    I2C1CONbits.GCEN = 0; //General call adress disabled

    I2C1CONbits.I2CEN = 1; //Enable I2C module	
}

/*********************************************************************
 * Function:        MyStartI2C()
 *
 * Input:		None.
 *
 * Output:		None.
 *
 * Overview:		Generates an I2C Start Condition
 *
 * Note:			None
 ********************************************************************/
void MyStartI2C(void) {
    //This function generates an I2C start condition and returns status 
    //of the Start.

    I2C1CONbits.SEN = 1; //Generate Start COndition
    while (I2C1CONbits.SEN); //Wait for Start COndition
    //	return(I2C1STATbits.S);	//Optionally return status
}

/*********************************************************************
 * Function:        MyRestartI2C()
 *
 * Input:		None.
 *
 * Output:		None.
 *
 * Overview:		Generates a restart condition and optionally returns status
 *
 * Note:			None
 ********************************************************************/
void MyRestartI2C(void) {
    //This function generates an I2C Restart condition and returns status 
    //of the Restart.

    I2C1CONbits.RSEN = 1; //Generate Restart		
    while (I2C1CONbits.RSEN); //Wait for restart	
    //	return(I2C1STATbits.S);	//Optional - return status
}

/*********************************************************************
 * Function:        MyStopI2C()
 *
 * Input:		None.
 *
 * Output:		None.
 *
 * Overview:		Generates a bus stop condition
 *
 * Note:			None
 ********************************************************************/
void MyStopI2C(void) {
    //This function generates an I2C stop condition and returns status 
    //of the Stop.

    I2C1CONbits.PEN = 1; //Generate Stop Condition
    while (I2C1CONbits.PEN); //Wait for Stop
    //	return(I2C1STATbits.P);	//Optional - return status
}

/*********************************************************************
 * Function:        MyWriteI2C()
 *
 * Input:		Byte to write.
 *
 * Output:		return (-1);	//NACK received from slave
 *						return (0);		//ACK received from slave
 *
 * Overview:		Writes a byte out to the bus
 *
 * Note:			None
 ********************************************************************/
int MyWriteI2C(unsigned char byte) {
    while (I2C1STATbits.TBF); //wait for data transmission

    I2C1TRN = byte; //Load byte to I2C1 Transmit buffer

    while (I2C1STATbits.TRSTAT); //wait for slave ack

    if (I2C1STATbits.ACKSTAT)
        return (0); //NACK received from slave
    else
        return (-1); //ACK received from slave
}

/*********************************************************************
 * Function:        MyAckI2C()
 *
 * Input:		None.
 *
 * Output:		Acknowledge Status.
 *
 * Overview:		Return the Acknowledge status on the bus
 *
 * Note:			None
 ********************************************************************/
unsigned int MyAckI2C(void) {
    return (!I2C1STATbits.ACKSTAT); //Return Ack Status
}

/*********************************************************************
 * Function:        NotAckI2C()
 *
 * Input:		None.
 *
 * Output:		None.
 *
 * Overview:		Generates a NO Acknowledge on the Bus
 *
 * Note:			None
 ********************************************************************/
void MyNotAckI2C(void) {
    I2C1CONbits.ACKDT = 1; //Set for NotACk
    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN); //wait for ACK to complete
    I2C1CONbits.ACKDT = 0; //Set for NotACk
}

/*********************************************************************
 * Function:        AckI2C()
 *
 * Input:		None.
 *
 * Output:		None.
 *
 * Overview:		Generates an Acknowledge.
 *
 * Note:			None
 ********************************************************************/
void AckI2C(void) {
    I2C1CONbits.ACKDT = 0; //Set for ACk
    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN); //wait for ACK to complete
}

/*********************************************************************
 * Function:        MyReadI2C()
 *
 * Input:		None.
 *
 * Output:		contents of I2C1 receive buffer.
 *
 * Overview:		Read a single byte from Bus
 *
 * Note:			None
 ********************************************************************/
unsigned char MyReadI2C(void) {
    I2C1CONbits.RCEN = 1; //Enable Master receive
    Nop();
    while (!I2C1STATbits.RBF); //Wait for receive bufer to be full
    return (I2C1RCV); //Return data in buffer
}

/*********************************************************************
 * Function:       MyGetsI2C()
 *
 * Input:		array pointer, Length.
 *
 * Output:		None.
 *
 * Overview:		read Length number of Bytes into array
 *
 * Note:			None
 ********************************************************************/
void MyGetsI2C(unsigned char *rdptr, unsigned char Length) {
    while (Length--) {
        *rdptr++ = MyReadI2C(); //get a single byte

        if (Length) {
            //ATTENTION, Surtout pas	MyAckI2C() qui indique si ACK reçu		
            AckI2C(); //GENERE UN Acknowledge sur le bus
        }
    }
}

/*********************************************************************
 * Function:        EEPROM_ByteWriteI2C()
 *
 * Input:		Addr, data to write
 *
 * Output:		None.
 *
 * Overview:		perform a high density byte write of data byte, Data.
 *				starting at the address formed from HighAdd and LowAdd
 *
 * Note:			None
 ********************************************************************/
void EEPROM_ByteWriteI2C(unsigned int Add, unsigned char data) {
    MyStartI2C(); //Generate Start COndition
    MyWriteI2C(ADDR_EEPROM_W); //Write Control byte

    while (!(MyAckI2C())) //Wait for EEPROM not busy
    {
        MyRestartI2C(); //generate restart
        MyWriteI2C(ADDR_EEPROM_W);
    }

    MyWriteI2C(Add >> 8); //Write High Address
    MyWriteI2C(Add); //Write Low Address

    MyWriteI2C(data); //Write Data
    MyStopI2C(); //Initiate Stop Condition
}

/*********************************************************************
 * Function:        EEPROM_ByteReadI2C()
 *
 * Input:		Add sur 16 bits.
 *
 * Output:		byte lu à l'adresse de l'EEPROM.
 *
 * Note:			None
 ********************************************************************/
unsigned char EEPROM_ByteReadI2C(unsigned int Add) {
    unsigned char ByteLu;

    MyStartI2C(); //Generate Start condition
    MyWriteI2C(ADDR_EEPROM_W); //send control byte for write (Adresse hard EEPROM)

    while (!(MyAckI2C())) //Wait for EEPROM not busy
    {
        MyRestartI2C(); //generate restart
        MyWriteI2C(ADDR_EEPROM_W);
    }

    MyWriteI2C(Add >> 8); //Send High Address
    MyWriteI2C(Add); //Send Low Address

    MyRestartI2C(); //Generate Restart
    MyWriteI2C(ADDR_EEPROM_W | 0x01); //send control byte for Read

    ByteLu = MyReadI2C();

    MyNotAckI2C(); //send Not Ack
    MyStopI2C(); //Send Stop Condition
    return (ByteLu);
}

/*********************************************************************
 * Function:        MyPutStringI2C()
 *
 * Input:		pointer to array.
 *
 * Output:		None.
 *
 * Overview:		writes a string of data upto PAGESIZE from array
 *
 * Note:			None
 ********************************************************************/
void MyPutStringI2C(unsigned char *wrptr, unsigned char length) {
    unsigned char x;

    for (x = 0; x < length; x++) //Transmit Data Until Pagesize
    {
        MyWriteI2C(*wrptr); //Write 1 byte
        wrptr++;
    }
}

/*********************************************************************
 * Function:        EEPROMPageWriteI2C()
 *
 * Input:		Add, *wrptr, length.
 *
 * Output:		None.
 *
 * Overview:		Write a page of data from array pointed to be wrptr
 *				starting at address from Add
 *
 * Note:			Address must start on a page boundary
 ********************************************************************/
void EEPROMPageWriteI2C(unsigned int Add, unsigned char *wrptr, unsigned char length) {
    MyStartI2C(); //Generate Start condition
    MyWriteI2C(ADDR_EEPROM_W); //send control byte for write (Adresse hard EEPROM)

    while (!(MyAckI2C())) //Wait for EEPROM not busy
    {
        MyRestartI2C(); //generate restart
        MyWriteI2C(ADDR_EEPROM_W);
    }

    MyWriteI2C(Add >> 8); //Send High Address
    MyWriteI2C(Add); //Send Low Address


    MyPutStringI2C(wrptr, length); //Send data
    MyStopI2C(); //Send Stop Condition
}



/*********************************************************************
Add 	:	Offset sur 16 bits, les adresses sup à 0x1FF seront ignorées

0x0000 <= Adr EEPROM <= 000F, on ne recopiera au maximun que les 16 
premiers octets dans TabMemBaliA
Si Add > 000F , la routine ne recopiera rien

0x0100 <= Adr EEPROM <= 010F, on ne recopiera au maximun que les 16 
premiers octets dans TabMemBaliB
Si Add > 010F , la routine ne recopiera rien, de même que si


 *ptr1 : TabToEEPROM
length: Nb de datas à ecrire
 *********************************************************************/

//void RAM_Write(unsigned int Add, unsigned char *ptr1, unsigned char length)
//{
//	unsigned int PageMem, i;
//	unsigned char offset;
//	PageMem = Add >> 8;
//	
//	offset = Add;
//	if ( offset < SIZEOF_TAB_RAM_BALIAB )
//	{
//		switch ( PageMem )
//		{
//			case 0:
//				//Concerne la baliseA
//				for (i=0; i< length; i++)
//				{
//				 	if ( i+offset < SIZEOF_TAB_RAM_BALIAB )
//					 	TabMemBaliA[i+offset] = *ptr1++;
//				}
//			break;
//			
//			case 1:
//				//Concerne la baliseB
//				for (i=0; i< length; i++)
//				{
//				 	if ( i+offset < SIZEOF_TAB_RAM_BALIAB )
//					 	TabMemBaliB[i+offset] = *ptr1++;
//				}			
//			break;
//			
//			default:
//			break;
//			
//		}
//	}		
//}
//

/*********************************************************************
 * Function:        HDSequentialReadI2C()
 *
 * Input:		Add, *rdptr, length.
 *
 * Output:		None.
 *
 * Overview:		Performs a sequential read of length bytes starting at address
 *				and places data in array pointed to by *rdptr
 *
 * Note:			None
 ********************************************************************/
void EEPROM_SequentialReadI2C(unsigned int Add, unsigned char *rdptr, unsigned char length) {
    MyStartI2C(); //Generate Start condition
    MyWriteI2C(ADDR_EEPROM_W); //send control byte for write (Adresse hard EEPROM)

    while (!(MyAckI2C())) //Wait for EEPROM not busy
    {
        MyRestartI2C(); //generate restart
        MyWriteI2C(ADDR_EEPROM_W);
    }

    MyWriteI2C(Add >> 8); //Send High Address
    MyWriteI2C(Add); //Send Low Address

    MyRestartI2C(); //Generate Restart
    MyWriteI2C(ADDR_EEPROM_W | 0x01); //send control byte for Read

    MyGetsI2C(rdptr, length); //Read in multiple bytes
    MyNotAckI2C(); //Send Not Ack
    MyStopI2C(); //Send Stop Condition
}









