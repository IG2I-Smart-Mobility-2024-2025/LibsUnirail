/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    ecan1_DsPICFJ.h

  @Summary:
    This is the ecan1_DsPICFJ.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

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

#ifndef __Ecan1_DSPIC33FJ__H
#define __Ecan1_DSPIC33FJ__H

//ATTENTION, la DMA0 et la DMA1 sont utilisées pour le bus CAN


/**
  Section: Included Files
 */
#include <xc.h>
#include <stdbool.h>
#include "ecan1_DefinitionVariable.h"

//Reprise des memes noms que MCC

#define CAN1_MESSAGE_BUFFERS    32      //Nb buffers in DMA RAM
/* ATTENTION, correlation avec le registre :
 * C1FCTRLbits.DMABS = 0 soit 4 buffers in DMA RAM --> OK compilateur
 * C1FCTRLbits.DMABS = 1 soit 6 buffers in DMA RAM  --> Erreur compil
 * C1FCTRLbits.DMABS = 2 soit 8 buffers in DMA RAM --> OK compilateur
 * C1FCTRLbits.DMABS = 3 soit 12 buffers in DMA RAM --> Erreur compil
 * C1FCTRLbits.DMABS = 4 soit 16 buffers in DMA RAM --> OK compilateur
 * C1FCTRLbits.DMABS = 5 soit 24 buffers in DMA RAM --> Erreur compil
 * 
 * PS: la valeur choisie pour notre librairie est impérativement celle ci dessous
 * C1FCTRLbits.DMABS = 6 soit 32 buffers in DMA RAM --> OK compilateur
 * 
 * C1FCTRLbits.DMABS = 7 RESERVED 
 Pour que cela compile, il faut une puissance de 2 soit 4,8,16 ou 32*/ 

/*TX0, TX1, TX2, TX3 sont des buffers d'emission
 TX4/RX4, TX5/RX5, TX6/RX6, TX7/RX7 sont en reserve pour "custom application"   */

#define CAN1_FIFO_STARTING_BUFFER   8
// ATTENTION, correlation avec le registre :
//C1FCTRLbits.FSA = 8;    //TRB8 est le premier buffer de la FIFO
// 0 <= FSA <=0b 11111 soit RB31

/* Define ECAN Message Buffers */
typedef unsigned int ECAN_MSG_BUF [CAN1_MESSAGE_BUFFERS][8];

extern ECAN_MSG_BUF ecan1msgBuf __attribute__((space(dma), aligned(CAN1_MESSAGE_BUFFERS * 16)));

/*		ATTENTION: Rappel norme CAN
LES 7 BITS LES PLUS SIGNIFICATIFS DE L'IDENTIFICATEUR (ID10 à ID4) NE PEUVENT
ETRE TOUS RECESSIFS!!!					*/


/* Operation modes */
//typedef enum {
//    CAN1_NORMAL_OPERATION_MODE = 0,
//    CAN1_DISABLE_MODE = 1,
//    CAN1_LOOPBACK_MODE = 2,
//    CAN1_LISTEN_ONLY_MODE = 3,
//    CAN1_CONFIGURATION_MODE = 4,
//    CAN1_LISTEN_ALL_MESSAGES_MODE = 7
//} ECAN1_OP_MODES;


//Niveau de priorité pour l'envoi des trames CAN
typedef enum {
    ECAN1_PRIORITY_HIGH =   0b11,
    ECAN1_PRIORITY_MEDIUM = 0b10,
    ECAN1_PRIORITY_LOW =    0b01,
    ECAN1_PRIORITY_NONE =   0b00
} ECAN1_TX_PRIOIRTY;

/***************************************************************************
Function Prototypes  
 ***************************************************************************/
/* Null weak implementations of callback functions. */
void __attribute__((weak)) ECAN1_CallbackBusOff(void){}
void __attribute__((weak)) ECAN1_CallbackTxErrorPassive(void){}
void __attribute__((weak)) ECAN1_CallbackRxErrorPassive(void){}
void __attribute__((weak)) ECAN1_CallbackMessageReceived(void) {}
void __attribute__((weak)) ECAN1_CallbackRxBufferOverflow() {}


/*  "ECAN1_DMACopy" est un sous-programme utile aux routines 
 * "ECAN1_receive" et "ECAN1_transmit"          
 
 * Cette routine sert à recopier le contenu d'un buffer DMA CAN vers une variable
 * message CAN defini en RAM
 * Exemple:
 * ECAN1_DMACopy(BUF4, &mc_maVariable);
 * 
 * PS: Il est à noter qu'il peut être dangereux d'utiliser cette routine avec 
 * tous les buffers DMA RAM.
 * En effet, les buffers 0 à 3 sont dédiés à l'émission de trames CAN, donc 
 * utilisation non appropriée!
 * Les buffers 8 à 31 sont dédiés à la FIFO, donc utilisation aussi non appropriée!
 * Ne reste qu'une possibilité pour les buffers  4 à 7, à condition que ceux ci
 * aient bien été configurés en buffers de réception message CAN
 */
void ECAN1_DMACopy(uint8_t buffer_number, uCAN1_MSG *message);

/*  Cette routine recopie un message CAN qui a été reçu dans la FIFO Hardware
 * du périphérique CAN vers une variable CAN en mémoire RAM
 * Avant d'appeler cette routine, il faut vérifier qu'un message CAN a bien été reçu.
 * Exemple d'utilisation:
 *             ECAN1_receive(&msgReceiveFIFO);
 */
bool ECAN1_receive(uCAN1_MSG *recCanMsg);


/* Cette routine envoi sur le bus CAN, un message de type CAN.
 * Pour ce faire, elle vérifie qu'au moins un des buffers DMA RAM (0 à 3) est libre.
 * Si c'est le cas, le message sera transmis sur le Bus.
 * Dans le cas contraire, un "false" sera renvoyé!!
 * 
 * Donc deux utilisations possibles:
 *  - Blocante:   while (!ECAN1_transmit(ECAN1_PRIORITY_MEDIUM, &myMesCAN));
 * 
 *  - Non bloquante : ECAN1_transmit(ECAN1_PRIORITY_MEDIUM, &myMesCAN);
 */
bool ECAN1_transmit(ECAN1_TX_PRIOIRTY priority, uCAN1_MSG *sendCanMsg);


/* Cette routine retourne le nombre de messages CAN qui ont été reçu dans la
 * FIFO Hardware CAN. Les messages CAN qui pourraient être dans les buffers
 * 4 à 7 ne sont pas pris en compte.
 */
uint8_t ECAN1_messagesInBuffer();

bool ECAN1_isBusOff();
bool ECAN1_isRXErrorPassive();
bool ECAN1_isTXErrorPassive();


/*
Initialises the DMA to be used with ECAN module                                                        
 *                       Channel 0 of the DMA is configured to Tx ECAN messages
 * 						of ECAN module 1. 
 *						Channel 1 is configured to Rx ECAN messages of module 1.
*/
void CAN1_InitDMAECAN(void);


#endif  //fin "__Ecan1_DSPIC33FJ__H"

/**
 End of File
*/