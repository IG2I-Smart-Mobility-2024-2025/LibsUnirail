/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    clock.h

  @Summary:
    This is the clock.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.145.0
        Device            :  
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36b
        MPLAB             :  MPLAB X v5.25
*/


#ifndef CLOCK_H
#define	CLOCK_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ  80000000UL
#endif

#define CLOCK_SystemFrequencyGet()        (80000000UL)

#define CLOCK_PeripheralFrequencyGet()    (CLOCK_SystemFrequencyGet() / 2)

#define CLOCK_InstructionFrequencyGet()   (CLOCK_SystemFrequencyGet() / 2)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the oscillator to the default states configured in the
 *                  MCC GUI
 * @Example
    CLOCK_Initialize(void);
 */
void CLOCK_Initialize(void);
#endif	/* CLOCK_H */
/**
 End of File
*/