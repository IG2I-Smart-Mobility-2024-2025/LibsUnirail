#include "xbee.h"
	
#define TIMEOUT_RECEPTION 20 // en ms

/**Format de la trame (xbee documentation page 86+):<BR>
    Delimiteur ->0x7E<BR>
    Longueur de la \b trame (longueur du message +5) 2 octets<BR>
    Mode d'operation API sans echappements (0x01)<BR>
    ID de la trame pour suivi d'ACK<BR>
    Adresse de destination, 2 octets<BR>
    Options<BR>
    donnees<BR>
    checksum
    \todo faire une lib pour config, envoi de messages, monitoring, etc.
    \todo verifier si gi_FlagReceptionCompletePayload sert a qqch
    \todo elimine de la fonction: 
    -	short si_FlagReceptionCompleteSpecifsTrameCAN= 0 et son seul usage: 
    si_FlagReceptionCompleteSpecifsTrameCAN = 0
    - short si_FlagReceivePayloadXBeeEnCours = 0 et son usage: 
    si_FlagReceivePayloadXBeeEnCours = 0;
    si_FlagReceivePayloadXBeeEnCours = 1;
	
	
	
 */
short PortXbee_receptionOctet(xBeeReceivePacket* donnees, int serial) {
    unsigned char CharRecu;
    static short si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
    static short si_IndiceTabReceivePacket; //compteur d'indice du tableau de donnees
    static unsigned char suc_cks_calcule; //Accumulateur pour calculer le checksum
	
	
#if MC802
    CharRecu = U2RXREG;

    if (IFS1bits.T4IF) //Erreut TimeOUT donc Reset Diagramme etat
    {
        T4CONbits.TON = 0; //	Stop TimeOUT
        IFS1bits.T4IF = 0;
        TMR4 = 0;
        si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
    }
	
#else
	static unsigned int time = 0;
	CharRecu = serialGetchar(serial);
	
	if ( (millis()-time) > TIMEOUT_RECEPTION)
	{
		time = millis();
		si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
	}

#endif


    //Pour Debug
    //MESCAN_SetData8(&mc_GSM_statusRun, cdmc_GSM_var1Debug, si_Etat_ISR_UART);

    switch (si_Etat_ISR_UART) {
        case WAIT_START_DELIMITER_FRAME_XB:
            suc_cks_calcule = 0;
            if (CharRecu == START_DELIMITER_FRAME_XB) {
#if MC802
                TMR4 = 0;
                IFS1bits.T4IF = 0;
                Nop();
#else 
				time = millis();
#endif
                si_Etat_ISR_UART = RX_MSB_LEN_MESSAGE;
            }
            return 0;

        case RX_MSB_LEN_MESSAGE:
            donnees->LenPacket = (unsigned int) (CharRecu << 8);
            si_Etat_ISR_UART = RX_LSB_LEN_MESSAGE;
            return 0;

        case RX_LSB_LEN_MESSAGE:
            donnees->LenPacket = donnees->LenPacket + CharRecu;
            si_Etat_ISR_UART = RX_FRAME_TYPE;
            return 0;

        case RX_FRAME_TYPE:
            donnees->OptionFrameType = CharRecu;
            suc_cks_calcule += CharRecu;
            if (CharRecu == FRAME_TYPE_RX16_BITS_ADR) {
                si_Etat_ISR_UART = RX_MSB_SOURCE_ADR;
                return 0;
            } else if (CharRecu == TX_STATUS_FRAME_ACK_RF) {
                si_Etat_ISR_UART = RX_ACKXBEE_ID_ACK;
                return 0;
            } else if (CharRecu == AT_COMMAND_RESPONSE) {
                si_Etat_ISR_UART = RX_ATCOMMAND_ID_ATCOMMAND;
                return 0;
            } else {
                si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
                return -2;
            }

        case RX_MSB_SOURCE_ADR:
            donnees->AdrSource = (unsigned int) (CharRecu << 8);
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_LSB_SOURCE_ADR;
            return 0;

        case RX_LSB_SOURCE_ADR:
            donnees->AdrSource += CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_RSSI;
            return 0;

        case RX_RSSI:
            donnees->RSSI = CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_OPTIONS;
            return 0;

        case RX_OPTIONS:
            donnees->Options = CharRecu;
            suc_cks_calcule += CharRecu;
            si_IndiceTabReceivePacket = 0;
            si_Etat_ISR_UART = RX_DATA_TYPE_TRAME_RF;
            return 0;

        case RX_DATA_TYPE_TRAME_RF:
            //Dans le tableau de datas, La premiere data d'indice ZERO indique
            //Le type de trame datas RF que l'on a recu (TROIS types possibles)

            //  0x3E: Reception d'un codage de trame CAN qu'il faudra envoyer sur le bus
            //  0x3F: Reception d'un codage de trame CAN qu'il faudra interpreter
            //  Autres: Correspond a un numero de SUBSET GSM-R

            donnees->bReceivePacketData[si_IndiceTabReceivePacket] = CharRecu;
            si_IndiceTabReceivePacket++;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_DATAS_MESSAGE;

            return 0;


        case RX_DATAS_MESSAGE:
            //Reception des datas xbee (SUBMIT GSM_R ou FRAMEs CAN)
            donnees->bReceivePacketData[si_IndiceTabReceivePacket] = CharRecu;
            si_IndiceTabReceivePacket++;
            suc_cks_calcule += CharRecu;
            if (si_IndiceTabReceivePacket == (donnees->LenPacket - 5))
                si_Etat_ISR_UART = RX_CKS;
            return 0;

        case RX_CKS:
            // Reception du checksum et verification
            donnees->CKS = CharRecu;
            suc_cks_calcule = 0xFF - suc_cks_calcule;

            if (suc_cks_calcule == CharRecu) {
                donnees->StatusCom = RAS;


                si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
                return 1;
            } else {
                donnees->StatusCom = ERREUR;
                si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
                return -1;
            }
            break;
            //Traitement pour reception Frame Acknoledge RF Xbee
        case RX_ACKXBEE_ID_ACK:
            donnees->FrameId_IdentifiUARTdataFrameBeingReported = CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ACKXBEE_STATE;
            return 0;

        case RX_ACKXBEE_STATE:
            donnees->ReponseACK_EtatLowSiGoodACK = CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ACKXBEE_CKS;
            return 0;

        case RX_ACKXBEE_CKS:
            donnees->CKS = CharRecu;
            suc_cks_calcule = 0xFF - suc_cks_calcule;
            si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
            
            if (suc_cks_calcule == CharRecu) {
                donnees->StatusCom = RAS;
                 return 1;

            } else {


                donnees->StatusCom = ERREUR;
                return -1;
            }
            break;

        case RX_ATCOMMAND_ID_ATCOMMAND:
            donnees->FrameId_IdentifiUARTdataFrameBeingReported = CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ATCOMMAND_1;
            return 0;

        case RX_ATCOMMAND_1:
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ATCOMMAND_2;
            return 0;

        case RX_ATCOMMAND_2:
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ATCOMMAND_STATUS;
            return 0;

        case RX_ATCOMMAND_STATUS:
            donnees->ReponseACK_EtatLowSiGoodACK = CharRecu;
            donnees->CKS = CharRecu;
            if (donnees->LenPacket > 5)
                si_Etat_ISR_UART = RX_ATCOMMAND_DATAS;
            else
                si_Etat_ISR_UART = RX_CKS;

            return 0;

        case RX_ATCOMMAND_DATAS:
            //Reception des datas xbee
            donnees->bReceivePacketData[si_IndiceTabReceivePacket] = CharRecu;
            si_IndiceTabReceivePacket++;
            suc_cks_calcule += CharRecu;
            if (si_IndiceTabReceivePacket == (donnees->LenPacket - 4))
                si_Etat_ISR_UART = RX_CKS;
            return 0;


        default:
            donnees->StatusCom = 2;
            return -2;
    }
}

/**
// si ID_message > 1 ACK (on peux aussi l'utiliser pour avoir une numerotation des trames)

short xbee_send (int serial, char dest_addr[2], char *donnees, int long_donnees, short type_trame, unsigned char ID_message, short options)
{
	return PortXbee_envoyer(dest_addr, donnees, long_donnees, serial, type_trame, ID_message, options)
}

short xbee_send_TX_REQUEST_16BITS(int serial, char dest_addr[2], char *donnees, int long_donnees)
{
	return PortXbee_envoyer(dest, donnees, long_donnees, serial, TX_REQUEST_16BITS_ADR, 0x01, 0x00);
}

void xbee_insert_Ghost_in_data(char *donnees, int long_donnees)
{
	unsigned int i ;
	int nbr, val;
	nbr = long_donnees;
	val = GHOST_TRAME_CAN;
	
	for (i = nbr ;  i >0 ; i--)
      donnees[i] = donnees[i-1];
 
	donnees[i] = val;
}

void xbee_insert_Shadow_in_data(char *donnees, int long_donnees)
{
	unsigned int i ;
	int nbr, val;
	nbr = long_donnees;
	val = SHADOWS_TRAME_CAN;
	
	for (i = nbr ;  i >0 ; i--)
      donnees[i] = donnees[i-1];
 
	donnees[i] = val;
}

void xbee_insert_GSMR_in_data(char *donnees, int long_donnees)
{
	unsigned int i ;
	int nbr, val;
	nbr = long_donnees;
	val = '?';
	
	for (i = nbr ;  i >0 ; i--)
      donnees[i] = donnees[i-1];
 
	donnees[i] = val;
}

*/

/**Format de la trame (xbee documentation page 86+):<BR>
    Delimiteur ->0x7E<BR>
    Longueur de la \b trame (longueur du message +5) 2 octets<BR>
    Mode d'operation API sans echappements (0x01)<BR>
    ID de la trame pour suivi d'ACK<BR>
    Adresse de destination, 2 octets<BR>
    Options<BR>
    donnees<BR>
    checksum
    \todo faire une lib pour config, envoi de messages, monitoring, etc.
 */
short PortXbee_envoyer(char dest_addr[2], unsigned char *donnees, int nb, int serial, short type_trame, unsigned char ID_message, short options) {
    short retour = -1;
    unsigned char checksum = 0;
    int i, pos, nbTotal;
    unsigned char trame[128];

    //    memset(trame, 0, 128);

    // page 63
    trame[0] = 0x7E;
    trame[1] = ((nb + 5) >> 8) & 0xFF;
    trame[2] = ((nb + 5)) & 0xFF;
    trame[3] = type_trame & 0xFF;
    trame[4] = ID_message & 0xFF;
    trame[5] = dest_addr[0];
    trame[6] = dest_addr[1];
 
	if (type_trame == TX_REQUEST_16BITS_ADR) {
        trame[7] = options & 0xFF;
        nbTotal = 8 + nb;
    } else {
        nbTotal = 7 + nb;
        trame[1] = ((nb + 4) >> 8) & 0xFF;
        trame[2] = ((nb + 4)) & 0xFF;
    }

    if (type_trame == TX_REQUEST_16BITS_ADR) {
        for (i = 0; i < nb; i++) {
            trame[8 + i] = donnees[i];
        }
    } else {
        for (i = 0; i < nb; i++) {
            trame[7 + i] = donnees[i];
        }
    }
	
    // page 59
    checksum = 0;
    for (pos = 3; pos < nbTotal; pos++) {
        checksum += trame[pos];
    }
    trame[nbTotal++] = 0xFF - checksum;

    // cf. man 2 write
    //serialPuts(fd, trame);

    //debug : affichage
    //fprintf(stderr, "-> envoyer (%d/%d) : ", n, retour);
    //fprintf(stderr, "trame : ");

    for (i = 0; i < nbTotal; i++) {

        //    printf("%X ",trame[i] );
        //fprintf(stderr, "0x%02X ", *(trame+i));
        ///\todo A verifier le bon fonctionnement
        //       printf("%X ", *(trame+i));
#if MC802
        uart2_write(*(trame + i));
#else
        serialPutchar(serial, *(trame + i));
#endif
    }
    //fprintf(stderr, "\n");
    //fprintf(stderr, "%s\n", trame);
    //    printf("Trame envoyee\n");

    return retour;
} 

/*
void xbee_insert_data_for_Ghost(char *donnees, int long_donnees)
{
	unsigned int i ;
	int nbr, val;
	nbr = long_donnees;
	val = '?';

	for (i = nbr ;  i >0 ; i--)
		donnees[i] = donnees[i-1];

	donnees[i] = val;
}*/