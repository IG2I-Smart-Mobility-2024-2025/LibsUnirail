/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    ecan1_Addon.h

  @Summary:
    This is the ecan1_Addon.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

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
#ifndef ECAN1_ADDON_H
#define	ECAN1_ADDON_H


/**
  Section: Included Files
 */

#include <xc.h>
#include <stdbool.h>
#include "ecan1_DsPICFJ.h"

//#if typeProc_MOT
//    //Pour Carte moteur loco
//    #include "../../SD60/SD60_Uc_Regul/system.h"
//#elif typeProc_BAL
//   //Config IO CAN pour uC "Balise"
//    #include "../../SD60/SD60_Balise/system.h"
//#elif typeProc_LCD
//   //Carte LCD
//   #include "../../SD60/SD60_LCD/system.h"
//#elif typeProc_GSM
//    //Carte XBee Wagon Eurocircuit
//    #include "../../SD60/SD60_GSMR/system.h"
//#elif typeProc_BAL_Infra
//    //Carte balise de l'infrastructure
//    #include"../../Infrastructure/BAL_Infra/system.h"
//#elif typeProc_AIG_Infra
//    //Carte balise de l'infrastructure
//    #include"../../Infrastructure/AIG_Infra/system.h"
//#elif typeProc_EnergieB
//    //Carte EnergieB (ON/OFF 24V des rails +XBee oFF locos)
//#include"../../Infrastructure/AIG_Infra/system.h"
//
//#else
//    #warning typeProc no declared for system.h
//#endif

#define MAX_SPEED_CPU_PLL   80
#define SPEED_CPU_NO_PLL    10


/* Operation modes */
typedef enum {
    CAN1_NORMAL_OPERATION_MODE = 0,
    CAN1_DISABLE_MODE = 1,
    CAN1_LOOPBACK_MODE = 2,
    CAN1_LISTEN_ONLY_MODE = 3,
    CAN1_CONFIGURATION_MODE = 4,
    CAN1_LISTEN_ALL_MESSAGES_MODE = 7
} ECAN1_OP_MODES;

// Mes "#define" supplémentaires
#define ACCEPTANCE_MASK0		0x0
#define ACCEPTANCE_MASK1		0x1
#define ACCEPTANCE_MASK2		0x2
#define NO_MASK					0x3

#define MASK0					0x0
#define MASK1					0x1
#define MASK2					0x2

//Les filtre 0 à 11 sont dédiés à la FIFO CAN
//Soit pour l'utilisation de "CAN1_AssignFiltreSID_ToFIFO31"
#define FILTRE0					0x0
#define FILTRE1					0x1
#define FILTRE2					0x2
#define FILTRE3					0x3
#define FILTRE4					0x4
#define FILTRE5					0x5
#define FILTRE6					0x6
#define FILTRE7					0x7
#define FILTRE8					0x8
#define FILTRE9					0x9
#define FILTRE10				0xA
#define FILTRE11				0xB

//Ces filtres sont pour utilisation de "CAN1_AssignFiltreSID_ToBUF4a7"
#define FILTRE12				0xC
#define FILTRE13				0xD
#define FILTRE14				0xE
#define FILTRE15				0xF

//#define BUF2					0x2
//#define BUF3					0x3
#define BUF4					0x4
#define BUF5					0x5
#define BUF6					0x6
#define BUF7					0x7
//#define BUF8					0x8
//#define BUF9					0x9
//#define BUF10					0xA
//#define BUF11					0xB
//#define BUF12					0xC
//#define BUF13					0xD
//#define BUF14					0xE

#define MIDE_HIGH				0x1
#define MIDE_LOW				0x0

#define EXIDE_HIGH          	0x1
#define EXIDE_LOW				0x0

extern ECAN_MSG_BUF ecan1msgBuf __attribute__((space(dma), aligned(CAN1_MESSAGE_BUFFERS * 16)));

bool ECAN1_DMA_is_TrameDatas(int NumeroBuffer);
uint8_t ECAN1_DMA_GetDLC(int NumeroBuffer);

/******************************************************************************
 *                                                                             
 *    Function:		CAN1_ActiveAllInterrupt
 *    Description:  
 *    Arguments:	
 *                   
 *                         
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void CAN1_ActiveAllInterrupt(void);

/******************************************************************************
 *                                                                             
 *    Function:		CAN1_AssignMaskSID
 *    Description:   Assign Mask for CAN identifier                                                                        
 *    Arguments:		StdId : identifier Standard
 *                   NumeroMask : Number of the Mask
 *                   BitMIDE : Bit of identifier      
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void CAN1_AssignMaskSID(unsigned int StdId, unsigned int NumeroMask, unsigned int BitMIDE);


/******************************************************************************
 *                                                                             
 *    Function:		CAN1_AssignFiltreSID_ToBUF4a7
 *    Description:   
 * ATTENTION, seuls, les filtres 12 à 15 sont autorisés, "exit" pour les autres
 * Ces filtres ne peuvent être associés qu'aux buffers FIFO
 
    "StdId" est l'identificateur en mode standard uniquement
    "NumeroFiltre" doit être compris entre "FILTRE0" et "FILTRE11 
   			
    "BitEXIDE" sera à EXIDE_LOW ou EXIDE_HIGH soit	
        EXIDE : Extended Identifier Enable bit
        if MIDE = 1 then
            1 = Match only message with extended identifier addresses
            0 = Match only message with standard identifier addresses
        if MIDE = 0 then
            Ignore EXIDE bit
	
    "MasqueSource" compris entre "ACCEPTANCE_MASK0" .. "ACCEPTANCE_MASK2"  *    Arguments:		
 *                   
 *                         
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void CAN1_AssignFiltreSID_ToBUF4a7(unsigned int StdId, unsigned int NumeroFiltre,
        unsigned int HitBuf, unsigned int MasqueSource, unsigned int BitEXIDE);


/******************************************************************************
 *                                                                             
 *    Function:		CAN1_AssignFiltreSID_ToFIFO31
 *    Description: 
 * ATTENTION, seuls, les filtres 0 à 11 sont autorisés, "exit" pour les autres
 * Ces filtres ne peuvent être associés qu'aux buffers FIFO
 
    "StdId" est l'identificateur en mode standard uniquement
    "NumeroFiltre" doit être compris entre "FILTRE0" et "FILTRE11 
   			
    "BitEXIDE" sera à EXIDE_LOW ou EXIDE_HIGH soit	
        EXIDE : Extended Identifier Enable bit
        if MIDE = 1 then
            1 = Match only message with extended identifier addresses
            0 = Match only message with standard identifier addresses
        if MIDE = 0 then
            Ignore EXIDE bit
	
    "MasqueSource" compris entre "ACCEPTANCE_MASK0" .. "ACCEPTANCE_MASK2"  
 *    Arguments:		
 *                   
 *                         
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void CAN1_AssignFiltreSID_ToFIFO31(unsigned int StdId, unsigned int NumeroFiltre,
        unsigned int MasqueSource, unsigned int BitEXIDE);


/******************************************************************************
 *                                                                             
 *    Function:		bool CAN1_InitSpeed(uint16_t speed);
 *    Description:
 *  Cette routine est spécifique aux DsPIC33FJ128MC802 ou DsPIC33FJ128GP802
 * Seules deux vitesses de processeur sont prises en compte: Foc = 10MHz ou 80MHz
 * Si Foc=10MHz, deux choix possible de vitesse de bus : 125Kb et 250Kb
 * Si Foc=80MHz, quatre choix possible de vitesse de bus : 125Kb, 250Kb, 500Kb et 1Mb
 *   
 *    Arguments: Vitesse Bus CAN		                  
 *                         
 * return "false" si aucune de ces conditions réunies 
 *                                                                                                   
 ******************************************************************************/
bool CAN1_InitSpeed(uint16_t freqOSC, uint16_t CANspeed);


/******************************************************************************
 *                                                                             
 *    Function:		void CAN1_SetIO_PORT(void);
 *    Description:   
 *      L'utilisateur doit écrire cette routine, cad attribuer manuellement les
 * pins émetteur CAN et récepteur CAN.
 *  En clair, mettre à jour les registres RPINRxx et RPORxx
 *    Arguments:None		           
 *                         
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void CAN1_SetIO_PORT(void);


/******************************************************************************
 *                                                                             
 *    Function:		void CAN1_SetConfigBuffer(void);
 *    Description:   
 *      Cette routine configure les buffers DMA RAM du bus CAN
 * - On utilisera les 32 buffers disponibles. Attention, cela représente 512 octets,
 * soit la moitié de la DMA RAM disponiple. Il ne restera donc que 512 octets pour
 * les autres périphériques qui voudraient utiliser le controleur DMA
 * 
 * On indique aussi que:
 * - la FIFO de réception des messages CAN débute à partir du buffer numéro 8.
 * - les filtres 0 à 11 sont attribués à la reception des messages CANS dans la FIFO
 * - les buffers 0 à 3 sont des buffers d'émission. On a donc une profondeur 
 * de 4 dans la pile d'émission des messages CAN.
 * - Les buffers 4 à 7 qui sont paramétrables sont configurés en buffers de 
 * réception. On pourra les attribuer à des messages prioritaires qui pourront 
 * être traités dans la routine d'interruption CAN
 *    Arguments: None		
 *                         
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void CAN1_SetConfigBuffer(void);



void CAN1_AssignMask2forEID(uint32_t ExtId);
void CAN1_AssignFiltre11andMASK2forEID_ToFIFO31(uint32_t ExtId);
void CAN1_AssignFiltre10andMASK2forEID_ToFIFO31(uint32_t ExtId);

#endif	/* ECAN1_ADDON_H */

/**
 End of File
 */


