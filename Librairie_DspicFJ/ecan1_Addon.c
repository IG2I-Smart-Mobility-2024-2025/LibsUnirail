/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    ecan1_Addon.c

  @Summary:
    This is the ecan1_Addon.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

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


/**
  Section: Included Files
 */
#include "ecan1_Addon.h"

/*
#ifdef XTypeProc
    #warning __XTypeProc__ OK
#else
    #warning XTypeProc no declared 
#endif
*/

void CAN1_SetIO_PORT(void) {
    
//    /*Attention, si les IO du bus can peuvent etre des entrées analogiques
//     alors il FAUT IMPERATIVEMENT Desabled le module ADC    */
//    //    PMD1bits.AD1MD = 1; //Disabled module A/D !!!!!!!!!!!
//#if typeProc_MOT
//    //Pour Carte moteur loco
//    RPOR2bits.RP5R = 0x10; // Rp5 pour CANTX		 	
//    RPINR26bits.C1RXR = 4; // Rp4 pour CANRX	
//#elif typeProc_BAL
//   //Config IO CAN pour uC "Balise"
//    RPOR3bits.RP7R = 0x10; // Rp7 pour CANTX		 		
//    RPINR26bits.C1RXR = 6; // Rp6 pour CANRX
//#elif typeProc_LCD
//   //Carte LCD
//    RPOR1bits.RP3R = 0x10; // Rp3 pour CANTX		 	
//    RPINR26bits.C1RXR = 2; // Rp2 pour CANRX	
//#elif typeProc_GSM
//    //Carte XBee Wagon Eurocircuit
//    //Vieille carte XBee (meme config!!)
//    //RPOR2bits.RP5R = 0x10; // Rp5 pour CANTX		 	
//    //RPINR26bits.C1RXR = 4; // Rp4 pour CANRX	
//    RPOR2bits.RP5R = 0x10; // Rp5 pour CANTX		 	
//    RPINR26bits.C1RXR = 4; // Rp4 pour CANRX	
//#elif typeProc_BAL_Infra
//    //Carte balise de l'infrastructure
//    RPOR7bits.RP15R = 0x10; // Rp15 pour CANTX		 		
//    RPINR26bits.C1RXR = 14; // Rp14 pour CANRX	
//#elif typeProc_AIG_Infra
//           Nop(); 
//#elif typeProc_EnergieB
//           Nop();
//#else
//    #warning typeProc no declared 
//#endif

}


void CAN1_SetConfigBuffer(void) {
    /* put the module in configuration mode */
    C1CTRL1bits.REQOP = CAN1_CONFIGURATION_MODE;
    while (C1CTRL1bits.OPMODE != CAN1_CONFIGURATION_MODE);

    C1FCTRLbits.DMABS = 6; //32 buffers in DMA RAM
    
#if typeProc_LCD
    //Pour le LCD
    C1FCTRLbits.FSA = 12; //TRB12 est le premier buffer de la FIFO
#else
    C1FCTRLbits.FSA = 8; //TRB8 est le premier buffer de la FIFO
#endif
    /* enable window to access the filter configuration registers */
    /* use filter window*/
    C1CTRL1bits.WIN = 1;

    /* FIFO Mode 
 Les Filtres 0..12 sont dédiés à la FIFO CAN*/
    C1BUFPNT1bits.F0BP = 0xf; //Filter 0 uses FIFO
    C1BUFPNT1bits.F1BP = 0xf; //Filter 1 uses FIFO
    C1BUFPNT1bits.F2BP = 0xf; //Filter 2 uses FIFO
    C1BUFPNT1bits.F3BP = 0xf; //Filter 3 uses FIFO
    C1BUFPNT2bits.F4BP = 0xf; //Filter 4 uses FIFO
    C1BUFPNT2bits.F5BP = 0xf; //Filter 5 uses FIFO
    C1BUFPNT2bits.F6BP = 0xf; //Filter 6 uses FIFO
    C1BUFPNT2bits.F7BP = 0xf; //Filter 7 uses FIFO
    C1BUFPNT3bits.F8BP = 0xf; //Filter 8 uses FIFO
    C1BUFPNT3bits.F9BP = 0xf; //Filter 9 uses FIFO
    C1BUFPNT3bits.F10BP = 0xf; //Filter 10 uses FIFO
    C1BUFPNT3bits.F11BP = 0xf; //Filter 11 uses FIFO

    /* clear window bit to access ECAN control registers */
    C1CTRL1bits.WIN = 0;

    /* ECAN1, Buffer 0 to 3 are Transmit Buffer */
    C1TR01CONbits.TXEN0 = 0x1; // Buffer 0 is a Transmit Buffer 
    C1TR01CONbits.TXEN1 = 0x1; // Buffer 1 is a Transmit Buffer 
    C1TR23CONbits.TXEN2 = 0x1; // Buffer 2 is a Transmit Buffer 
    C1TR23CONbits.TXEN3 = 0x1; // Buffer 3 is a Transmit Buffer 

    //Buffer que j'ai mis en reserve pour matcher avec "Old Assign buffer filter"
    C1TR45CONbits.TXEN4 = 0x0; // Buffer 4 is a Receive Buffer 
    C1TR45CONbits.TXEN5 = 0x0; // Buffer 5 is a Receive Buffer 
    C1TR67CONbits.TXEN6 = 0x0; // Buffer 6 is a Receive Buffer 
    C1TR67CONbits.TXEN7 = 0x0; // Buffer 7 is a Receive Buffer 

    C1TR01CONbits.TX0PRI = 0x0; // Message Buffer 0 Priority Level
    C1TR01CONbits.TX1PRI = 0x0; // Message Buffer 1 Priority Level
    C1TR23CONbits.TX2PRI = 0x0; // Message Buffer 2 Priority Level
    C1TR23CONbits.TX3PRI = 0x0; // Message Buffer 3 Priority Level
    C1TR45CONbits.TX4PRI = 0x0; // Message Buffer 4 Priority Level
    C1TR45CONbits.TX5PRI = 0x0; // Message Buffer 5 Priority Level
    C1TR67CONbits.TX6PRI = 0x0; // Message Buffer 6 Priority Level
    C1TR67CONbits.TX7PRI = 0x0; // Message Buffer 7 Priority Level

    /* put the module in normal mode */
    C1CTRL1bits.REQOP = CAN1_NORMAL_OPERATION_MODE;
    while (C1CTRL1bits.OPMODE != CAN1_NORMAL_OPERATION_MODE);

    /* clear the buffer and overflow flags */
    C1RXFUL1 = 0x0000;
    C1RXFUL2 = 0x0000;
    C1RXOVF1 = 0x0000;
    C1RXOVF2 = 0x0000;
}

/*
 Cette routine est spécifique aux DsPIC33FJ128MC802 ou DsPIC33FJ128GP802
 * Seules deux vitesses de processeur sont prises en compte: Foc = 10MHz ou 80MHz
 * Si Foc=10MHz, deux choix possible de vitesse de bus : 125Kb et 250Kb
 * Si Foc=80MHz, quatre choix possible de vitesse de bus : 125Kb, 250Kb, 500Kb et 1Mb
 * 
 * return "false" si aucune de ces conditions réunies
 */
bool CAN1_InitSpeed(uint16_t freqOSC, uint16_t CANspeed) {
    bool succesInit = false;
    if (freqOSC == SPEED_CPU_NO_PLL) {
        switch (CANspeed) {
            case 125:
                /* put the module in configuration mode */
                C1CTRL1bits.REQOP = CAN1_CONFIGURATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_CONFIGURATION_MODE);
                C1CTRL1bits.CANCKS = 1; //FCAN = Fcy (FCAN can't exceed 40MHz)
                /*****************************************************************/
                //Cas ou Fosc = 10 MHz et PLL inactive
                /*****************************************************************/
                /* Determination du Baud rate prescaler

                    TFQ = N x 125Kbits = 20 x 125Kbits = 2,5MHz (NB: ici N=20 Tq pour un bit)
	
                    Fcy = 10MHz / 2
                    C1CFG1<BRP> = (Fcy/(2xFTQ))-1
                                            = (5 000 000 / ( 2 x 2 500 000)) - 1
                                            = 1 - 1 = 0
                 */
                C1CFG1bits.BRP = 0;

                /* Synchronization Jump Width set to 4 TQ */
                /*	
                    Règle pour la détermination 
                        RJW = mini ( 4 ou PHSEG1 ) soit 4
                 */
                C1CFG1bits.SJW = 0x3;

                /* Phase Segment 1 time is 8 TQ */
                C1CFG2bits.SEG1PH = 0x7;

                /* Phase Segment 2 time is set to be programmable */
                //On veut imposer nous même le temps de phase2
                C1CFG2bits.SEG2PHTS = 0x1;

                /* Phase Segment 2 time is 8 TQ */
                C1CFG2bits.SEG2PH = 0x7;

                /* Propagation Segment time is 3 TQ */
                C1CFG2bits.PRSEG = 0x2;

                /* Bus line is sampled three times at the sample point */
                C1CFG2bits.SAM = 0x1;

                /* Bus line is sampled one time at the sample point */
                //	C1CFG2bits.SAM = 0x0; //une fois

                /* put the module in normal mode */
                C1CTRL1bits.REQOP = CAN1_NORMAL_OPERATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_NORMAL_OPERATION_MODE);

                succesInit = true;
                break;

            case 250:
                /* put the module in configuration mode */
                C1CTRL1bits.REQOP = CAN1_CONFIGURATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_CONFIGURATION_MODE);
                C1CTRL1bits.CANCKS = 1; //FCAN = Fcy (FCAN can't exceed 40MHz)

                /*****************************************************************/
                //Cas ou Fosc = 10 MHz et PLL inactive
                /*****************************************************************/
                /* Determination du Baud rate prescaler
                 * On passe à 10Tq au lieu de 20!!!!!

                    TFQ = N x 250Kbits = 10 x 250Kbits = 5MHz (NB: ici N=20 Tq pour un bit)
	
                    Fcy = 10MHz / 2
                    C1CFG1<BRP> = (Fcy/(2xFTQ))-1
                                            = (5 000 000 / ( 2 x 2 500 000)) - 1
                                            = 1 - 1 = 0
                 */
                C1CFG1bits.BRP = 0;


                /* Synchronization Jump Width set to 4 TQ */
                /*	
                    Règle pour la détermination 
                        RJW = mini ( 4 ou PHSEG1 ) soit 4
                 */
                C1CFG1bits.SJW = 0x3;

                /* Phase Segment 1 time is 4 TQ */
                C1CFG2bits.SEG1PH = 0x3;

                /* Phase Segment 2 time is set to be programmable */
                //On veut imposer nous même le temps de phase2
                C1CFG2bits.SEG2PHTS = 0x1;

                /* Phase Segment 2 time is 3 TQ */
                C1CFG2bits.SEG2PH = 0x2;

                /* Propagation Segment time is 2 TQ */
                C1CFG2bits.PRSEG = 0x1;

                /* Bus line is sampled three times at the sample point */
                C1CFG2bits.SAM = 0x1;

                /* Bus line is sampled one time at the sample point */
                //	C1CFG2bits.SAM = 0x0; //une fois

                /* put the module in normal mode */
                C1CTRL1bits.REQOP = CAN1_NORMAL_OPERATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_NORMAL_OPERATION_MODE);

                succesInit = true;
                break;

            default:
                break;

        }
    } else if (freqOSC == MAX_SPEED_CPU_PLL) {
        switch (CANspeed) {
            case 125:
                /* put the module in configuration mode */
                C1CTRL1bits.REQOP = CAN1_CONFIGURATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_CONFIGURATION_MODE);
                C1CTRL1bits.CANCKS = 1; //FCAN = Fcy (FCAN can't exceed 40MHz)

                /*****************************************************************/
                //Cas ou Fosc = 10 MHz et PLL active
                /*****************************************************************/

                /* Determination du Baud rate prescaler

                    TFQ = N x 125Kbits = 20 x 125Kbits = 2,5MHz (NB: ici N=20 Tq pour un bit)
	
                    Comme le bit "C1CTRL1bits.CANCKS" est toujours equivalent à 1
                    Ce bit "C1CTRL1bits.CANCKS" n'existe plus !!!!!!!!!!!!!!
	
                    Fcy = 10MHz / 2
                    C1CFG1<BRP> = (Fcy/(2xFTQ))-1
                                            = (40 000 000 / ( 2 x 2 500 000)) - 1
                                            = 8 - 1 = 0
                 */
                C1CFG1bits.BRP = 7;

                /* Synchronization Jump Width set to 4 TQ */
                /*	
                    Règle pour la détermination 
                        RJW = mini ( 4 ou PHSEG1 ) soit 4
                 */
                C1CFG1bits.SJW = 0x3;

                /* Phase Segment 1 time is 8 TQ */
                C1CFG2bits.SEG1PH = 0x7;

                /* Phase Segment 2 time is set to be programmable */
                //On veut imposer nous même le temps de phase2
                C1CFG2bits.SEG2PHTS = 0x1;

                /* Phase Segment 2 time is 8 TQ */
                C1CFG2bits.SEG2PH = 0x7;

                /* Propagation Segment time is 3 TQ */
                C1CFG2bits.PRSEG = 0x2;

                /* Bus line is sampled three times at the sample point */
                C1CFG2bits.SAM = 0x1;

                /* Bus line is sampled one time at the sample point */
                //	C1CFG2bits.SAM = 0x0; //une fois

                /* put the module in normal mode */
                C1CTRL1bits.REQOP = CAN1_NORMAL_OPERATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_NORMAL_OPERATION_MODE);

                succesInit = true;
                break;

            case 250:
                /* put the module in configuration mode */
                C1CTRL1bits.REQOP = CAN1_CONFIGURATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_CONFIGURATION_MODE);
                C1CTRL1bits.CANCKS = 1; //FCAN = Fcy (FCAN can't exceed 40MHz)

                /*****************************************************************/
                //Cas ou Fosc = 10 MHz et PLL active
                /*****************************************************************/

                /* Determination du Baud rate prescaler

                    TFQ = N x 250Kbits = 20 x 250Kbits = 5MHz (NB: ici N=20 Tq pour un bit)
	
                    Fcy = 80MHz / 2
                    C1CFG1<BRP> = (Fcy/(2xFTQ))-1
                                            = (40 000 000 / ( 2 x 5 000 000)) - 1
                                            = 4 - 1 = 0
                 */
                C1CFG1bits.BRP = 3;

                /* Synchronization Jump Width set to 4 TQ */
                /*	
                    Règle pour la détermination 
                        RJW = mini ( 4 ou PHSEG1 ) soit 4
                 */
                C1CFG1bits.SJW = 0x3;

                /* Phase Segment 1 time is 8 TQ */
                C1CFG2bits.SEG1PH = 0x7;

                /* Phase Segment 2 time is set to be programmable */
                //On veut imposer nous même le temps de phase2
                C1CFG2bits.SEG2PHTS = 0x1;

                /* Phase Segment 2 time is 8 TQ */
                C1CFG2bits.SEG2PH = 0x7;

                /* Propagation Segment time is 3 TQ */
                C1CFG2bits.PRSEG = 0x2;

                /* Bus line is sampled three times at the sample point */
                C1CFG2bits.SAM = 0x1;

                /* Bus line is sampled one time at the sample point */
                //	C1CFG2bits.SAM = 0x0; //une fois

                /* put the module in normal mode */
                C1CTRL1bits.REQOP = CAN1_NORMAL_OPERATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_NORMAL_OPERATION_MODE);

                succesInit = true;
                break;

            case 500:
                /* put the module in configuration mode */
                C1CTRL1bits.REQOP = CAN1_CONFIGURATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_CONFIGURATION_MODE);
                C1CTRL1bits.CANCKS = 1; //FCAN = Fcy (FCAN can't exceed 40MHz)

                /*****************************************************************/
                //Cas ou Fosc = 10 MHz et PLL active
                /*****************************************************************/

                /* Determination du Baud rate prescaler

                    TFQ = N x 500Kbits = 20 x 500Kbits = 10MHz (NB: ici N=20 Tq pour un bit)
	
                    Fcy = 80MHz / 2
                    C1CFG1<BRP> = (Fcy/(2xFTQ))-1
                                            = (40 000 000 / ( 2 x 10 000 000)) - 1
                                            = 2 - 1 = 1
                 */
                C1CFG1bits.BRP = 1;

                /* Synchronization Jump Width set to 4 TQ */
                /*	
                    Règle pour la détermination 
                        RJW = mini ( 4 ou PHSEG1 ) soit 4
                 */
                C1CFG1bits.SJW = 0x3;

                /* Phase Segment 1 time is 8 TQ */
                C1CFG2bits.SEG1PH = 0x7;

                /* Phase Segment 2 time is set to be programmable */
                //On veut imposer nous même le temps de phase2
                C1CFG2bits.SEG2PHTS = 0x1;

                /* Phase Segment 2 time is 8 TQ */
                C1CFG2bits.SEG2PH = 0x7;

                /* Propagation Segment time is 3 TQ */
                C1CFG2bits.PRSEG = 0x2;

                /* Bus line is sampled three times at the sample point */
                C1CFG2bits.SAM = 0x1;

                /* Bus line is sampled one time at the sample point */
                //	C1CFG2bits.SAM = 0x0; //une fois

                /* put the module in normal mode */
                C1CTRL1bits.REQOP = CAN1_NORMAL_OPERATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_NORMAL_OPERATION_MODE);

                succesInit = true;
                break;

            case 1000:
                /* put the module in configuration mode */
                C1CTRL1bits.REQOP = CAN1_CONFIGURATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_CONFIGURATION_MODE);
                C1CTRL1bits.CANCKS = 1; //FCAN = Fcy (FCAN can't exceed 40MHz)

                /*****************************************************************/
                //Cas ou Fosc = 10 MHz et PLL active
                /*****************************************************************/

                /* Determination du Baud rate prescaler

                    TFQ = N x 1000Kbits = 20 x 1000Kbits = 20MHz (NB: ici N=20 Tq pour un bit)
	
                    Fcy = 80MHz / 2
                    C1CFG1<BRP> = (Fcy/(2xFTQ))-1
                                            = (40 000 000 / ( 2 x 20 000 000)) - 1
                                            = 1 - 1 = 0
                 */
                C1CFG1bits.BRP = 0;


                /* Synchronization Jump Width set to 4 TQ */
                /*	
                    Règle pour la détermination 
                        RJW = mini ( 4 ou PHSEG1 ) soit 4
                 */
                C1CFG1bits.SJW = 0x3;

                /* Phase Segment 1 time is 8 TQ */
                C1CFG2bits.SEG1PH = 0x7;

                /* Phase Segment 2 time is set to be programmable */
                //On veut imposer nous même le temps de phase2
                C1CFG2bits.SEG2PHTS = 0x1;

                /* Phase Segment 2 time is 8 TQ */
                C1CFG2bits.SEG2PH = 0x7;

                /* Propagation Segment time is 3 TQ */
                C1CFG2bits.PRSEG = 0x2;

                /* Bus line is sampled three times at the sample point */
                C1CFG2bits.SAM = 0x1;

                /* Bus line is sampled one time at the sample point */
                //	C1CFG2bits.SAM = 0x0; //une fois

                /* put the module in normal mode */
                C1CTRL1bits.REQOP = CAN1_NORMAL_OPERATION_MODE;
                while (C1CTRL1bits.OPMODE != CAN1_NORMAL_OPERATION_MODE);

                succesInit = true;
                break;

        }
    }
    //Nop();
    return succesInit;
}

/*   			
    "BitEXIDE" sera à EXIDE_LOW ou EXIDE_HIGH soit	
        EXIDE : Extended Identifier Enable bit
        if MIDE = 1 then
            1 = Match only message with extended identifier addresses
            0 = Match only message with standard identifier addresses
        if MIDE = 0 then
            Ignore EXIDE bit
	
    "MasqueSource" compris entre "ACCEPTANCE_MASK0" .. "ACCEPTANCE_MASK2"
                                                                        ou NO_MASK

Rappel:	
    Pour être compatible avec les conventions choisies
        (TX0 à TX3) --> Buffer émission classique
         TX4 à TX7) --> "Custon Buffer"
        (RX8 à RX31) --> FIFO Buffer de réception

    A la sortie de cette routine, le filtre sélectionné sera "Enable"
 */
void CAN1_AssignFiltreSID_ToBUF4a7(unsigned int StdId, unsigned int NumeroFiltre,
        unsigned int HitBuf, unsigned int MasqueSource, unsigned int BitEXIDE) {
    /* enable window to access the filter configuration registers */
    int aze;
    if ((HitBuf > 3) && (HitBuf < 8)) {
        C1CTRL1bits.WIN = 0b1;
        switch (NumeroFiltre) {

            case FILTRE12:
                aze = (StdId & 0x07FF) << 5;
                C1RXF12SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF12SID = C1RXF12SID | (1 << 3);

                C1BUFPNT4bits.F12BP = HitBuf & 0x000F; //Attention au buffer15!!
                C1FMSKSEL2bits.F12MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN12 = 1;
                break;

            case FILTRE13:
                C1RXF13SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF13SID = C1RXF13SID | (1 << 3);

                C1BUFPNT4bits.F13BP = HitBuf & 0x000F; //Attention au buffer15!!
                C1FMSKSEL2bits.F13MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN13 = 1;
                break;

            case FILTRE14:
                C1RXF14SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF14SID = C1RXF14SID | (1 << 3);

                C1BUFPNT4bits.F14BP = HitBuf & 0x000F; //Attention au buffer15!!
                C1FMSKSEL2bits.F14MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN14 = 1;
                break;

            case FILTRE15:
                C1RXF15SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF15SID = C1RXF15SID | (1 << 3);

                C1BUFPNT4bits.F15BP = HitBuf & 0x000F; //Attention au buffer15!!
                C1FMSKSEL2bits.F15MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN15 = 1;
                break;

            default:
                break;
        }
        /* enable window to access status registers */
        C1CTRL1bits.WIN = 0b0;
    }
}

/*  ATTENTION, seuls, les filtres 0 à 11 sont autorisés, "exit" pour les autres
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
                                                                        ou NO_MASK

Rappel:	
    Pour être compatible avec les conventions choisies
        (TX0 à TX3) --> Buffer émission classique
         TX4 à TX7) --> "Custon Buffer"
        (RX8 à RX31) --> FIFO Buffer de réception

    A la sortie de cette routine, le filtre sélectionné sera "Enable"
 */
void CAN1_AssignFiltreSID_ToFIFO31(unsigned int StdId, unsigned int NumeroFiltre,
        unsigned int MasqueSource, unsigned int BitEXIDE) {
    /* enable window to access the filter configuration registers */

    if (NumeroFiltre < 12) {
        C1CTRL1bits.WIN = 0b1;
        switch (NumeroFiltre) {
            case 0:
                C1RXF0SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF0SID = C1RXF0SID | (1 << 3);

                C1BUFPNT1bits.F0BP = 0x000F;
                /*  Attribué le message CAN au buffer15 signifie que l'on envoi
                ce message dans la FIFO CAN */
                C1FMSKSEL1bits.F0MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN0 = 1;
                break;

            case 1:
                C1RXF1SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF1SID = C1RXF1SID | (1 << 3);

                C1BUFPNT1bits.F1BP = 0x000F;
                C1FMSKSEL1bits.F1MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN1 = 1;
                break;

            case 2:
                C1RXF2SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF2SID = C1RXF2SID | (1 << 3);

                C1BUFPNT1bits.F2BP = 0x000F;
                C1FMSKSEL1bits.F2MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN2 = 1;
                break;

            case 3:
                C1RXF3SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF3SID = C1RXF3SID | (1 << 3);

                C1BUFPNT1bits.F3BP = 0x000F;
                C1FMSKSEL1bits.F3MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN3 = 1;
                break;

            case 4:
                C1RXF4SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF4SID = C1RXF4SID | (1 << 3);

                C1BUFPNT2bits.F4BP = 0x000F;
                C1FMSKSEL1bits.F4MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN4 = 1;
                break;

            case 5:
                C1RXF5SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF5SID = C1RXF5SID | (1 << 3);

                C1BUFPNT2bits.F5BP = 0x000F;
                C1FMSKSEL1bits.F5MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN5 = 1;
                break;

            case 6:
                C1RXF6SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF6SID = C1RXF6SID | (1 << 3);

                C1BUFPNT2bits.F6BP = 0x000F;
                C1FMSKSEL1bits.F6MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN6 = 1;
                break;

            case 7:
                C1RXF7SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF7SID = C1RXF7SID | (1 << 3);

                C1BUFPNT2bits.F7BP = 0x000F;
                C1FMSKSEL1bits.F7MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN7 = 1;
                break;

            case 8:
                C1RXF8SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF8SID = C1RXF8SID | (1 << 3);

                C1BUFPNT3bits.F8BP = 0x000F;
                C1FMSKSEL2bits.F8MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN8 = 1;
                break;

            case 9:
                C1RXF9SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF9SID = C1RXF9SID | (1 << 3);

                C1BUFPNT3bits.F9BP = 0x000F;
                C1FMSKSEL2bits.F9MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN9 = 1;
                break;

            case 10:
                C1RXF10SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF10SID = C1RXF10SID | (1 << 3);

                C1BUFPNT3bits.F10BP = 0x000F;
                C1FMSKSEL2bits.F10MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN10 = 1;
                break;

            case 11:
                C1RXF11SID = (StdId & 0x07FF) << 5;
                if (BitEXIDE & 0x0001)
                    C1RXF11SID = C1RXF11SID | (1 << 3);

                C1BUFPNT3bits.F11BP = 0x000F;
                C1FMSKSEL2bits.F11MSK = MasqueSource & 0x0003; //(acceptance Mask)
                C1FEN1bits.FLTEN11 = 1;
                break;


            default:
                break;
        }
        /* enable window to access status registers */
        C1CTRL1bits.WIN = 0b0;
    }
}

/******************************************************************************
 *                                                                             
 *    Function:		CAN1_AssignMaskSID
 *    Description:   Assign Mask for CAN identifier                                                                        
 *    Arguments:		StdId : identifier Standard
 *                   NumeroMask : Number of the Mask
 *                   BitMIDE : Bit of identifier      
 *    Return Value:  None
 *                                                                                                   
 * 
 *
 * 	
 *   "NumeroMask" doit imperativement être MASK0, MASK1 ou MASK2
 *   "StdId" est l'identificateur en mode standard uniquement
 *   "BitMIDE" sera à MIDE_LOW ou MIDE_HIGH, se référer au datasheet du DsPic
 *	
 *   Tout bit à "0" dans le masque indique que l'on acceptera ce bit
 *   quel que soit son niveau logique. (indépendant du filtre)
 *	
 *   Donc tout bit à "1" dans le masque indique un test à exécuter via 
 *   le filtre.
 *  
 * 
 ******************************************************************************/
void CAN1_AssignMaskSID(unsigned int StdId, unsigned int NumeroMask,
        unsigned int BitMIDE) {
    /* enable window to access the filter configuration registers */
    C1CTRL1bits.WIN = 0b1;
    switch (NumeroMask) {
        case 0:
            C1RXM0SID = (StdId & 0x07FF) << 5;
            if (BitMIDE & 0x0001)
                C1RXM0SID = C1RXM0SID | (1 << 3);
            break;

        case 1:
            C1RXM1SID = (StdId & 0x07FF) << 5;
            if (BitMIDE & 0x0001)
                C1RXM1SID = C1RXM1SID | (1 << 3);
            break;

        case 2:
            C1RXM2SID = (StdId & 0x07FF) << 5;
            if (BitMIDE & 0x0001)
                C1RXM2SID = C1RXM2SID | (1 << 3);
            break;

    }
    /* enable window to access status registers */
    C1CTRL1bits.WIN = 0b0;
}

void CAN1_ActiveAllInterrupt(void)
{
/* configure the device to interrupt on the receive buffer full flag */
    /* clear the buffer full flags */
    C1INTFbits.RBIF = 0;
    //    /* put the module in normal mode */
    //    C1CTRL1bits.REQOP = CAN1_NORMAL_OPERATION_MODE;
    //    while (C1CTRL1bits.OPMODE != CAN1_NORMAL_OPERATION_MODE);

    /* Enable ECAN1 Interrupt */
    IEC2bits.C1IE = 1;
    //    IEC2bits.C1IE = 0;

    /* Enable Receive interrupt */
    C1INTEbits.RBIE = 1;
    //    C1INTEbits.RBIE = 0;

    /* Enable Error interrupt*/
    //    C1INTEbits.ERRIE = 1;
    C1INTEbits.ERRIE = 0;

    /* Enable Receive buffer Overflow interrupt */
    //    C1INTEbits.RBOVIE = 1;
    C1INTEbits.RBOVIE = 0;
}


bool ECAN1_DMA_is_TrameDatas(int NumeroBuffer) {
    if (!(ecan1msgBuf[NumeroBuffer][0] & 0x0002))
        return true;
    else
        return false;
}

uint8_t ECAN1_DMA_GetDLC(int NumeroBuffer) {
    return ( (ecan1msgBuf[NumeroBuffer][2] & 0x000F));
}

void CAN1_AssignMask2forEID(uint32_t ExtId) {
    uint32_t temp32;
    //Pour Id etendu, BitMIDE doit etre High
    /* enable window to access the filter configuration registers */
    C1CTRL1bits.WIN = 0b1;

    //uint16_t temp, regC1RXM2SID, regC1RXM2EID;
    //    C1RXM2SID = (ExtId >> 18) << 5;
    //    C1RXM2SID = C1RXM2SID | ((ExtId >> 16) & 0x3);

    temp32 = (ExtId >> 18) << 5;
    temp32 = temp32 | ((ExtId >> 16) & 0x3);
    temp32 = temp32 | (1 << 3); //set bit MIDE
    C1RXM2SID = temp32;

    //C1RXM2SID = C1RXM2SID | (1 << 3); //set bit MIDE

    C1RXM2EID = ExtId;

    //DebugNop();
    C1CTRL1bits.WIN = 0b0;
}

void CAN1_AssignFiltre11andMASK2forEID_ToFIFO31(uint32_t ExtId) {
    uint32_t temp32;
    /* enable window to access the filter configuration registers */
    C1CTRL1bits.WIN = 0b1;
    //    C1RXF11SID = (ExtId >> 18) << 5;
    //    C1RXF11SID = C1RXF11SID | ((ExtId >> 16) & 0x3);
    //    C1RXF11SID = C1RXF11SID | (1 << 3); //set bit EXIDE
    //DebugNop();

    temp32 = (ExtId >> 18) << 5;
    temp32 = temp32 | ((ExtId >> 16) & 0x3);
    temp32 = temp32 | (1 << 3); //set bit EXIDE
    C1RXF11SID = temp32;

    C1RXF11EID = ExtId;
    //DebugNop();

    C1BUFPNT3bits.F11BP = 0x000F;
    C1FMSKSEL2bits.F11MSK = 0x02; //(acceptance Mask)
    C1FEN1bits.FLTEN11 = 1;
    //DebugNop();

    C1CTRL1bits.WIN = 0b0;
}


void CAN1_AssignFiltre10andMASK2forEID_ToFIFO31(uint32_t ExtId) {
    uint32_t temp32;
    /* enable window to access the filter configuration registers */
    C1CTRL1bits.WIN = 0b1;

    temp32 = (ExtId >> 18) << 5;
    temp32 = temp32 | ((ExtId >> 16) & 0x3);
    temp32 = temp32 | (1 << 3); //set bit EXIDE
    C1RXF10SID = temp32;

    C1RXF10EID = ExtId;
    //DebugNop();

    C1BUFPNT3bits.F10BP = 0x000F;
    C1FMSKSEL2bits.F10MSK = 0x02; //(acceptance Mask)
    C1FEN1bits.FLTEN10 = 1;
    //DebugNop();

    C1CTRL1bits.WIN = 0b0;
}



/**
 End of File
 */

