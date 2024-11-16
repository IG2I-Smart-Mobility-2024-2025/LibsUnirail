/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    ecan1_DsPICFJ.c

  @Summary:
    This is the ecan1_DsPICFJ.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

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

#include "ecan1_DsPICFJ.h"

/******************************************************************************/
/* Private variable definitions                                               */
/******************************************************************************/
/* This alignment is required because of the DMA's peripheral indirect 
 * addressing mode. */
//static unsigned int ecan1msgBuf [CAN1_MESSAGE_BUFFERS][8] __attribute__((aligned(32 * 8 * 2)));
ECAN_MSG_BUF ecan1msgBuf __attribute__((space(dma), aligned(CAN1_MESSAGE_BUFFERS * 16)));

/******************************************************************************/
/* Private function prototypes                                                */
/******************************************************************************/
static void ECAN1_MessageToBuffer(uint8_t buffer_number, uCAN1_MSG* message);

/* Null weak implementations of callback functions. */
//void __attribute__((weak)) ECAN1_CallbackBusOff(void){}
//void __attribute__((weak)) ECAN1_CallbackTxErrorPassive(void){}
//void __attribute__((weak)) ECAN1_CallbackRxErrorPassive(void){}

//void __attribute__((weak)) ECAN1_CallbackMessageReceived(void) {}

//void __attribute__((weak)) ECAN1_CallbackRxBufferOverflow() {}

/*  Est utilisé dans la routine de reception des trames CAN
 * Attention, j'ai ajouté une ligne de code pour recuperer le DLC d'une RTR
 */
void ECAN1_DMACopy(uint8_t buffer_number, uCAN1_MSG *message) {
    uint16_t ide = 0;
    uint16_t rtr = 0;
    uint32_t id = 0;

    /* read word 0 to see the message type */
    ide = ecan1msgBuf[buffer_number][0] & 0x0001U;

    /* check to see what type of message it is */
    /* message is standard identifier */
    if (ide == 0U) {
        message->frame.id = (ecan1msgBuf[buffer_number][0] & 0x1FFCU) >> 2U;
        message->frame.idType = CAN1_FRAME_STD;
        rtr = ecan1msgBuf[buffer_number][0] & 0x0002U;
    }/* message is extended identifier */
    else {
        id = ecan1msgBuf[buffer_number][0] & 0x1FFCU;
        message->frame.id = id << 16U;
        message->frame.id += (((uint32_t) ecan1msgBuf[buffer_number][1] & (uint32_t) 0x0FFF) << 6U);
        message->frame.id += (((uint32_t) ecan1msgBuf[buffer_number][2] & (uint32_t) 0xFC00U) >> 10U);
        message->frame.idType = CAN1_FRAME_EXT;
        rtr = ecan1msgBuf[buffer_number][2] & 0x0200;
    }
    /* check to see what type of message it is */
    /* RTR message */
    if (rtr != 0U) {
        /* to be defined ?*/
        message->frame.msgtype = CAN1_MSG_RTR;

        //Mon ajout pour recuperer le DLC
        message->frame.dlc = (unsigned char) ecan1msgBuf[buffer_number][2] & 0xF;
        //Fin de mon ajout

    }/* normal message */
    else {
        message->frame.msgtype = CAN1_MSG_DATA;
        message->frame.data0 = (unsigned char) ecan1msgBuf[buffer_number][3];
        message->array[7] = (unsigned char) ecan1msgBuf[buffer_number][3];        
       
        message->frame.data1 = (unsigned char) ((ecan1msgBuf[buffer_number][3] & 0xFF00U) >> 8U);
        message->frame.data2 = (unsigned char) ecan1msgBuf[buffer_number][4];
        message->frame.data3 = (unsigned char) ((ecan1msgBuf[buffer_number][4] & 0xFF00U) >> 8U);
        message->frame.data4 = (unsigned char) ecan1msgBuf[buffer_number][5];
        message->frame.data5 = (unsigned char) ((ecan1msgBuf[buffer_number][5] & 0xFF00U) >> 8U);
        message->frame.data6 = (unsigned char) ecan1msgBuf[buffer_number][6];
        message->frame.data7 = (unsigned char) ((ecan1msgBuf[buffer_number][6] & 0xFF00U) >> 8U);
        message->frame.dlc = (unsigned char) (ecan1msgBuf[buffer_number][2] & 0x000FU);
    }
}

bool ECAN1_receive(uCAN1_MSG *recCanMsg) {
    uint_fast8_t currentBuffer;
    uint_fast8_t shiftAmount;
    bool messageReceived = false;
    uint16_t receptionFlags;


    if (C1INTFbits.RBOVIF == 1) {
        C1INTFbits.RBOVIF = 0;
        /* Receive buffer overflow occured, call the notification function */


        ECAN1_CallbackRxBufferOverflow();
        return messageReceived;
    }

    currentBuffer = C1FIFObits.FNRB;
    if (currentBuffer < 16) {
        receptionFlags = C1RXFUL1;
        shiftAmount = currentBuffer;
    } else {
        receptionFlags = C1RXFUL2;
        shiftAmount = currentBuffer - 16;
    }

    if (((receptionFlags >> shiftAmount) & 0x1) == 0x1) {
        ECAN1_DMACopy(currentBuffer, recCanMsg);

        if (currentBuffer < 16) {
            C1RXFUL1 &= ~(1 << shiftAmount);
        } else {
            C1RXFUL2 &= ~(1 << shiftAmount);
        }

        messageReceived = true;
    }

    return (messageReceived);
}


/******************************************************************************
 *                                                                             
 *    Function:		ECAN1_MessageToBuffer
 *    Description:       This function takes the input message, reformats it, 
 *                       and copies it to the specified CAN module buffer
 * 
 * Est utilisé dans la routine d'envoi trames CAN "ECAN1_transmit"	                                                                 
 *                                                                              
 ******************************************************************************/
static void ECAN1_MessageToBuffer(uint8_t buffer_number, uCAN1_MSG* message) {
    if (message->frame.idType == CAN1_FRAME_STD) {
        ecan1msgBuf[buffer_number][0] = (message->frame.id & 0x000007FF) << 2;
        ecan1msgBuf[buffer_number][1] = 0;
        ecan1msgBuf[buffer_number][2] = message->frame.dlc & 0x0F;
    } else {
        ecan1msgBuf[buffer_number][0] = (((uint16_t) (message->frame.id >> 16) & 0x1FFC)) | 0b1;
        ecan1msgBuf[buffer_number][1] = (uint16_t) (message->frame.id >> 6) & 0x0FFF;
        ecan1msgBuf[buffer_number][2] = (message->frame.dlc & 0x0F) + ((uint16_t) (message->frame.id << 10) & 0xFC00);
    }

    ecan1msgBuf[buffer_number][3] = ((message->frame.data1) << 8) + message->frame.data0;
    ecan1msgBuf[buffer_number][4] = ((message->frame.data3) << 8) + message->frame.data2;
    ecan1msgBuf[buffer_number][5] = ((message->frame.data5) << 8) + message->frame.data4;
    ecan1msgBuf[buffer_number][6] = ((message->frame.data7) << 8) + message->frame.data6;
}



/******************************************************************************
 *                                                                             
 *    Function:		ECAN1_transmit
 *    Description:       Transmits the message from user buffer to CAN buffer
 *                       as per the buffer number allocated.
 *                       Allocation of the buffer number is done by user 
 *                                                                             
 *    Arguments:		priority : priority of the message to be transmitted
 *                       sendCanMsg: pointer to the message object
 *                                             
 *    Return Value:      true - Transmit successful
 *                       false - Transmit failure                                                                              
 ******************************************************************************/

/******************************************************************
Seuls, les quatre premiers buffers sont utilisée en transmission 
TX0, TX1, TX2 et TX3
 * Les RTR trames sont transformées en trame data !!!! Like MCC de MCP!!!
 ******************************************************************/
bool ECAN1_transmit(ECAN1_TX_PRIOIRTY priority, uCAN1_MSG *sendCanMsg) {
    //    CAN1_TX_CONTROLS * pTxControls = (CAN1_TX_CONTROLS*)&C1TR01CON;

    uint_fast8_t numero_buffer_free;
    bool messageSent = false;

    numero_buffer_free = 0xF; //Numéro buffer non alloué
    if (C1TR01CONbits.TXREQ0 == 0)
        // TxBuffer0 is empty.
        numero_buffer_free = 0;
    else if (C1TR01CONbits.TXREQ1 == 0)
        // TxBuffer1 is empty. 
        numero_buffer_free = 1;

    else if (C1TR23CONbits.TXREQ2 == 0)
        // TxBuffer2 is empty.
        numero_buffer_free = 2;

    else if (C1TR23CONbits.TXREQ3 == 0)
        // TxBuffer3 is empty. 
        numero_buffer_free = 3;

    if (numero_buffer_free != 0xF) {
        ECAN1_MessageToBuffer(numero_buffer_free, sendCanMsg);
        messageSent = true;
        switch (numero_buffer_free) {
            case 0:
                C1TR01CONbits.TX0PRI = priority;
                C1TR01CONbits.TXREQ0 = 1;
                break;
            case 1:
                C1TR01CONbits.TX1PRI = priority;
                C1TR01CONbits.TXREQ1 = 1;
                break;
            case 2:
                C1TR23CONbits.TX2PRI = priority;
                C1TR23CONbits.TXREQ2 = 1;
                break;
            case 3:
                C1TR23CONbits.TX3PRI = priority;
                C1TR23CONbits.TXREQ3 = 1;
                break;
        }
    }

    return messageSent;
}

/******************************************************************************
 *                                                                             
 *    Function:		ECAN1_messagesInBuffer
 *    Description:       returns the number of messages that are received                                                                           
 *                                             
 *    Return Value:      Number of message received
 ******************************************************************************/
uint8_t ECAN1_messagesInBuffer() {
    uint_fast8_t messageCount;
    uint_fast8_t currentBuffer;
    uint16_t receptionFlags;

    messageCount = 0;

#if (CAN1_FIFO_STARTING_BUFFER<16)
    /* Check any message in buffer 0 to buffer 15*/
    receptionFlags = C1RXFUL1;
    if (receptionFlags != 0) {
        /* check whether a message is received */
        //        for (currentBuffer=0 ; currentBuffer < 16; currentBuffer++)

        //J'ai remplace 0 par "CAN1_FIFO_STARTING_BUFFER" 
        //Les buffers "custom" de reception ne seront pas pris en compte
        for (currentBuffer = CAN1_FIFO_STARTING_BUFFER; currentBuffer < 16; currentBuffer++) {
            if (((receptionFlags >> currentBuffer) & 0x1) == 0x1) {
                messageCount++;
            }
        }
    }
#endif

    /* Check any message in buffer 16 to buffer 32*/
    receptionFlags = C1RXFUL2;
    if (receptionFlags != 0) {
        /* check whether a message is received */
        for (currentBuffer = 0; currentBuffer < 16; currentBuffer++) {
            if (((receptionFlags >> currentBuffer) & 0x1) == 0x1) {
                messageCount++;
            }
        }
    }

    return (messageCount);
}

/******************************************************************************
 *                                                                             
 *    Function:		ECAN1_isBusOff
 *    Description:       Checks whether the transmitter in Bus off state
 *                                                                             
                                             
 *    Return Value:      true - Transmitter in Bus Off state
 *                       false - Transmitter not in Bus Off state                                                                              
 ******************************************************************************/
bool ECAN1_isBusOff() {
    return C1INTFbits.TXBO;
}

/******************************************************************************
 *                                                                             
 *    Function:		ECAN1_isRXErrorPassive
 *    Description:       Checks whether the receive in error passive state
 *                                             
 *    Return Value:      true - Receiver in Error Passive state
 *                       false - Receiver not in Error Passive state                                                                              
 ******************************************************************************/
bool ECAN1_isRXErrorPassive() {
    return C1INTFbits.RXBP;
}

/******************************************************************************
 *                                                                             
 *    Function:		ECAN1_isTXErrorPassive
 *    Description:       Checks whether the transmitter in error passive state                                                                          
 *                                             
 *    Return Value:      true - Transmitter in Error Passive state
 *                       false - Transmitter not in Error Passive state                                                                              
 ******************************************************************************/
bool ECAN1_isTXErrorPassive() {
    return (C1INTFbits.TXBP);
}



/******************************************************************************
 *                                                                             
 *    Function:			initDMAECAN
 *    Description:       Initialises the DMA to be used with ECAN module                                                        
 *                       Channel 0 of the DMA is configured to Tx ECAN messages
 * 						of ECAN module 1. 
 *						Channel 1 is configured to Rx ECAN messages of module 1.                                                      
 *    Arguments:			
 *	 Author:                                                                  
 *	                                                                 
 *                                                                              
 ******************************************************************************/
//ATTENTION chgt DMA0 en transmit par rapport aux premieres libCAN

void CAN1_InitDMAECAN(void) {
    DMACS0 = 0; //Clear the collission flags	

    /* setup channel 0 for peripheral indirect addressing mode 
    normal operation, word operation and select as Tx to peripheral */
    DMA0CON = 0x2020; //OK avant
    //    DMA1CONbits.MODE = 0x0; 	//Mode Continuous, ping pong disabled
    //    DMA1CONbits.AMODE = 0x2;	//Peripheral indirect adressing mode
    //    DMA1CONbits.SIZE = 0x0;		//Word mode
    //    DMA1CONbits.DIR = 0x1;		//Read from DPSRAM to peripheral

    /* setup the address of the peripheral ECAN1 (C1TXD) */
    //	DMA0PAD=0x0442;
    //NB: Le code ci dessous est equivalent
    DMA0PAD = (volatile unsigned int) &C1TXD;
    //Page 22.15 de section 22 (DMA)

    /* Set the data block transfer size of 8 */
    DMA0CNT = 7;

    /* automatic DMA Tx initiation by DMA request */
    DMA0REQ = 0x0046; //Cf page 6 section 22 
    //IRQSEL<6:0> = 1000110 ->ECAN1 - TX DATA REQUEST

    /* DPSRAM start adddress offset value */
    DMA0STA = __builtin_dmaoffset(ecan1msgBuf);
    /* enable the channel */

    DMA0CONbits.CHEN = 1;



    /* initialise the DMA channel 1 for ECAN Rx */
    //ATTENTION Chgt en DMA1 en Rx

    /* setup channel 1 for peripheral indirect addressing mode 
    normal operation, word operation and select as Rx to peripheral */
    DMA1CON = 0x0020; //Peripheral
    //    DMA2CONbits.MODE = 0x0; 	//Mode Continuous, ping pong disabled
    //    DMA2CONbits.AMODE = 0x2;	//Peripheral indirect adressing mode
    //    DMA2CONbits.SIZE = 0x0;		//Word mode
    //    DMA2CONbits.DIR = 0x0;		//Read from peripheral to DPSRAM

    /* setup the address of the peripheral ECAN1 (C1RXD) */
    //	DMA1PAD=0x0440;	
    //NB: Le code ci dessous est equivalent
    DMA1PAD = (volatile unsigned int) &C1RXD;
    //Table 22-1 de section 22 (DMA)

    /* Set the data block transfer size of 8 */
    DMA1CNT = 7;

    /* automatic DMA Rx initiation by DMA request */
    DMA1REQ = 0x0022; //Cf page 6 section 22 
    //IRQSEL<6:0> = 0100010 ->ECAN1 - RX DATA READY

    /* DPSRAM atart adddress offset value */
    DMA1STA = __builtin_dmaoffset(ecan1msgBuf);

    /* enable the channel */
    DMA1CONbits.CHEN = 1;

}

/**
 End of File
*/