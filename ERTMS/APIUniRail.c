#include "APIUniRail.h"

int checkPortNature(int fd)
{
	struct stat portStat;
	int portState;
	portState = fstat(fd, &portStat);
	if (!portState)
	{
		int isSock = S_ISSOCK(portStat.st_mode), isChar = S_ISCHR(portStat.st_mode);
		if (portStat.st_dev && portStat.st_ino && portStat.st_rdev && portStat.st_nlink && !isSock && isChar)
			return 1;	///Serial
		if (portStat.st_dev && portStat.st_ino && !portStat.st_rdev && portStat.st_nlink && isSock && !isChar)
		{
			int ret, val;
			unsigned int len;
			struct can_filter rfilter;
			ret = getsockopt(fd, SOL_CAN_RAW, CAN_RAW_FILTER , &rfilter, &len);
			if (!ret)
				return 2;	///CAN
			ret = getsockopt(fd, SOL_SOCKET, SO_TYPE , &val, &len);
			if (!ret)
				return 3;	///NETWORK
			return 0;	///UNKNOWN TYPE OF SOCKET
		}
		return 0;	///UNKNOWN PORT
	}
	else
		return -1;	///ERROR
}

void SendThroughCAN(uCAN1_MSG* headCanMsg, uint8_t* buffer)
{
	bool flowCtl;
	uCAN1_MSG sendCAN;
	sendCAN.frame.idType = headCanMsg->frame.idType;
	uint8_t length = headCanMsg->frame.data0+1;
	flowCtl = canLinux_transmit(CANLINUX_PRIORITY_HIGH, headCanMsg);
	while (!flowCtl)
	{
		usleep(1000);
		flowCtl = canLinux_transmit(CANLINUX_PRIORITY_HIGH, headCanMsg);
	}
	bool exitCondition = false;
	do
	{
		if (sendCAN.frame.idType == CAN1_FRAME_EXT)
			exitCondition = MESCAN_sliceArray(&sendCAN, buffer, headCanMsg->frame.id, length, CAN1_FRAME_EXT);
		else
			exitCondition = MESCAN_sliceArray(&sendCAN, buffer, headCanMsg->frame.id, length, CAN1_MSG_DATA);
		flowCtl = canLinux_transmit(CANLINUX_PRIORITY_MEDIUM, &sendCAN);
		while (!flowCtl)
		{
			usleep(1000);
			flowCtl = canLinux_transmit(CANLINUX_PRIORITY_MEDIUM, &sendCAN);
		}
	}
	while(exitCondition == false);
}

void SendThroughTCP(uint8_t* buffer, uint16_t length, int socket)
{
	send(socket, buffer, length, 0);
}

void APISendCommunicationInitiationMessage(GSMR_CommunicationInitiationMessage* initCom, unsigned long long int timeStamp, TrainInfo* train1, uint8_t messTag, int fd)
{
	uint8_t tableau[30], cks;
	char destAddr[2];
	uCAN1_MSG envCanMsg;
	int portType;
	initGSMR_CommunicationInitiationMessage(initCom, timeStamp, train1->parametres[IdTrain]);
	serializeMessage (initCom, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, initCom->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, initCom->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, initCom->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, initCom->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendNoCompatibleVersionSupported(GSMR_NoCompatibleVersionSupported* noComp,  unsigned long long int timeStamp, TrainInfo* train1, uint8_t messTag, int fd)
{
	uint8_t tableau[30], cks;
	char destAddr[2];
	uCAN1_MSG envCanMsg;
	int portType;
	initGSMR_NoCompatibleVersionSupported(noComp, timeStamp, train1->parametres[IdTrain]);
	serializeMessage (noComp, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, noComp->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, noComp->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, noComp->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, noComp->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendSessionEstablishedMessage(GSMR_SessionEstablishedMessage* SessionEstablished, unsigned long long int timeStamp, TrainInfo* train1, uint8_t messTag, int fd)
{
	uint8_t tableau[30], cks;
	char destAddr[2];
	uCAN1_MSG envCanMsg;
	int portType;
	initGSMR_SessionEstablishedMessage(SessionEstablished, timeStamp, train1->parametres[IdTrain]);
	serializeMessage (SessionEstablished, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, SessionEstablished->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, SessionEstablished->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, SessionEstablished->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, SessionEstablished->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}	

void APISendSoM_PositionReport(GSMR_SoM_PositionReport* SoMposReport, unsigned long long int timeStamp, TrainInfo* train1, uint8_t q_status, GSMR_PositionReportPacket* posReport, GSMR_TrainRunningNumber* trainNumber, GSMR_DataOutsideErtmsPacket* itinerary, uint8_t messTag, int fd)
{
	uint8_t tableau[30], cks;
	char destAddr[2];
	uCAN1_MSG envCanMsg;
	int portType;
	initGSMR_SoM_PositionReport(SoMposReport, timeStamp, train1->parametres[IdTrain], q_status, posReport, trainNumber, itinerary );
	serializeMessage (SoMposReport, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, SoMposReport->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, SoMposReport->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, SoMposReport->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, SoMposReport->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}	

void APISendValidatedTrainDataMessage(GSMR_ValidatedTrainDataMessage* valData, GSMR_PositionReportPacket* posReport, GSMR_ValidatedTrainDataPacket* dataPacket, BaliseInfo* baliseActuelle, TrainInfo* train1, GSMR_RBCSystemVersionMessage* RBCInfo, unsigned long long int timeStamp, uint8_t messTag, int fd)
{
	uint8_t tableau[100], cks;
	char destAddr[2];
	uCAN1_MSG envCanMsg;
	GSMR_nid_lrbg firstBalise;
	GSMR_engine_identifier identMotor[32];
	uint8_t systNat[32];
	identMotor[0].m_voltage = 1;
	identMotor[0].nid_ctraction = 7;
	
	firstBalise.nid_c = RBCInfo->nid_lrbg.nid_c;
	firstBalise.nid_bg = RBCInfo->nid_lrbg.nid_bg;
	
	int portType;
	initGSMR_PositionReportPacket(posReport, 0, firstBalise, train1->distance_parcourue, 0, 0, 2, 2, 1, (int)train1->parametres[LTrain], train1->vit_mesuree, 0, train1->modeTrain, (int)train1->parametres[NiveauERTMS], 0);
	initGSMR_ValidatedTrainDataPacket(dataPacket, 0, 2, (int)train1->parametres[LTrain], (int)train1->parametres[VitesseMaxTrain], 1, 0, 0, 8, 1, identMotor, 0, systNat);
	initGSMR_ValidatedTrainDataMessage(valData, timeStamp, train1->parametres[IdTrain], posReport, *dataPacket);
	serializeMessage (valData, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, valData->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, valData->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, valData->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, valData->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendMARequestMessage(GSMR_MARequestMessage* MARequest, GSMR_PositionReportPacket* posReport, BaliseInfo* baliseActuelle, TrainInfo* train1, GSMR_RBCSystemVersionMessage* RBCInfo, uint8_t qReason, unsigned long long int timeStamp, uint8_t messTag, int fd)
{
	char destAddr[2];
	uint8_t tableau[100], cks;
	uCAN1_MSG envCanMsg;
	GSMR_nid_lrbg firstBalise;
	firstBalise.nid_c = RBCInfo->nid_lrbg.nid_c;
	firstBalise.nid_bg = RBCInfo->nid_lrbg.nid_bg;
	
	int portType;
	initGSMR_PositionReportPacket(posReport, 0, firstBalise, train1->distance_parcourue, 0, 0, 2, 2, 1, (int)train1->parametres[LTrain], train1->vit_mesuree, 0, train1->modeTrain, (int)train1->parametres[NiveauERTMS], 0);
	initGSMR_MARequestMessage(MARequest, timeStamp, train1->parametres[IdTrain], qReason, posReport);
	serializeMessage (MARequest, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, MARequest->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, MARequest->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, MARequest->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, MARequest->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendRBCSystemVersionMessage(GSMR_RBCSystemVersionMessage* RBCInfo, unsigned int timeStamp, GSMR_nid_lrbg baliseTag, uint8_t systemVersion, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[30], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	initGSMR_RBCSystemVersionMessage(RBCInfo, timeStamp , 1, baliseTag, systemVersion);
	serializeMessage (RBCInfo, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, RBCInfo->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageReceived, RBCInfo->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_sourceAdressMessageReceived, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_RSSI_FromAntenne, messTag);
		cks =  (MESCAN_generateChecksum(tableau, RBCInfo->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageReceived, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, RBCInfo->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendSoMPositionConfirmed(GSMR_SoMPositionConfirmed* SoMConfirm, unsigned int timeStamp, uint8_t m_ack, GSMR_nid_lrbg baliseTag, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[30], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	initGSMR_SoMPositionConfirmed(SoMConfirm, timeStamp, m_ack, baliseTag);
	serializeMessage (SoMConfirm, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, SoMConfirm->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageReceived, SoMConfirm->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_sourceAdressMessageReceived, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_RSSI_FromAntenne, messTag);
		cks =  (MESCAN_generateChecksum(tableau, SoMConfirm->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageReceived, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, SoMConfirm->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendACKTrainDataMessage(GSMR_ACKTrainDataMessage* trainACK, unsigned int timeStamp, uint8_t M_ack, GSMR_nid_lrbg baliseTag, unsigned int timeStampTrain, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[30], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	initGSMR_ACKTrainDataMessage(trainACK, timeStamp, M_ack, baliseTag, timeStampTrain);
	serializeMessage (trainACK, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, trainACK->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, trainACK->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, trainACK->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, trainACK->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendLevel2_3MA_Message(GSMR_MovementAuthorityMessage* MA, unsigned int timeStamp, uint8_t M_ack, GSMR_nid_lrbg baliseTag, GSMR_Level2_3MovementAuthorityPacket packetnb15,
	uint8_t v_ema, uint16_t t_ema, GSMR_SectionDescription endsectiondescription, ERTMS_SectionTimer end, uint8_t q_dangerpoint, uint16_t d_dp, uint8_t v_releasedp,
	ERTMS_SectionTimer overlap, uint16_t d_startol, uint8_t v_releaseol, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[270], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	GSMR_SectionDescription sectiondescription[32];
	initGSMR_Level2_3MovementAuthorityPacket(&packetnb15, 0, 0, v_ema, t_ema, 0, sectiondescription, endsectiondescription,  end, q_dangerpoint, d_dp, v_releasedp, overlap, d_startol,	v_releaseol);
	initGSMR_MovementAuthorityMessage(MA, timeStamp, M_ack, baliseTag, packetnb15);
	serializeMessage (MA, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, MA->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageReceived, MA->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_sourceAdressMessageReceived, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_RSSI_FromAntenne, messTag);
		cks =  (MESCAN_generateChecksum(tableau, MA->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageReceived, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, MA->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}
void APISendGSMR_SRAuthorisationMessage(GSMR_SRAuthorisationMessage* SRAuth, uint32_t timeStamp, uint8_t M_ack, GSMR_nid_lrbg baliseTag, uint16_t d_sr, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[270], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	initGSMR_SRAuthorisationMessage(SRAuth, timeStamp, M_ack, baliseTag, 0, d_sr);
	serializeMessage (SRAuth, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, SRAuth->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageReceived, SRAuth->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_sourceAdressMessageReceived, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_RSSI_FromAntenne, messTag);
		cks =  (MESCAN_generateChecksum(tableau, SRAuth->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageReceived, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, SRAuth->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendAcknowledgmentMessage(GSMR_Acknowledgment* ack, uint32_t timeStamp, uint8_t nidEngine, uint32_t timeStampTrain, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[30], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	initGSMR_Acknowledgment(ack, timeStamp, nidEngine, timeStampTrain);
	serializeMessage (ack, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, ack->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageReceived, ack->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_sourceAdressMessageReceived, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_RSSI_FromAntenne, messTag);
		cks =  (MESCAN_generateChecksum(tableau, ack->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageReceived, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, ack->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendGSMR_EndOfMissionMessage(GSMR_EndOfMission* EOM, uint32_t timeStamp, uint8_t nidEngine, GSMR_PositionReportPacket* posReport, TrainInfo* train1, GSMR_RBCSystemVersionMessage* RBCInfo, uint8_t messTag, int fd)
{
	char destAddr[2];
	uint8_t tableau[100], cks;
	uCAN1_MSG envCanMsg;
	GSMR_nid_lrbg firstBalise;
	firstBalise.nid_c = RBCInfo->nid_lrbg.nid_c;
	firstBalise.nid_bg = RBCInfo->nid_lrbg.nid_bg;
	
	int portType;
	initGSMR_PositionReportPacket(posReport, 0, firstBalise, train1->distance_parcourue, 0, 0, 2, 2, 1, (int)train1->parametres[LTrain], train1->vit_mesuree, 0, train1->modeTrain, (int)train1->parametres[NiveauERTMS], 0);
	initGSMR_EndOfMission(EOM, timeStamp, train1->parametres[IdTrain], posReport);
	serializeMessage (EOM, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, EOM->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, EOM->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, EOM->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, EOM->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendGSMR_AckTerminationCommunicationSession(GSMR_AckTerminationCommunicationSession* termination, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[30], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	initGSMR_AckTerminationCommunicationSession(termination, timeStamp, m_ack, nid_lrbg);
	serializeMessage (termination, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, termination->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_RECEIVED;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageReceived, termination->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_sourceAdressMessageReceived, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_RSSI_FromAntenne, messTag);
		cks =  (MESCAN_generateChecksum(tableau, termination->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageReceived, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, termination->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendEBT_RBCTransitionOrder(EBT_Message* contactRBC, uint8_t m_version, uint8_t n_pig, uint8_t n_total, uint8_t m_dup, uint8_t m_mcount, GSMR_nid_lrbg nid_lrbg, uint8_t q_link, EBT_RBCTransitionOrder* RBC_ContactPacket, uint8_t q_scale, uint16_t d_rbctr, uint16_t nid_c,
	uint16_t nid_rbc, uint64_t nid_radio, uint8_t q_sleepsession, int CANidBase, int fd)
{
	uint8_t tableau[120], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	initEBT_RBCTransitionOrder(RBC_ContactPacket, q_scale, d_rbctr, nid_c,	nid_rbc, nid_radio, q_sleepsession);
	initEBT(contactRBC, m_version, n_pig, n_total, m_dup, m_mcount, nid_lrbg, q_link, RBC_ContactPacket);
	serializeEBT (contactRBC, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 2:
		envCanMsg.frame.id = CANidBase;
		envCanMsg.frame.idType = CAN1_FRAME_EXT;
		envCanMsg.frame.dlc = 8;
		envCanMsg.frame.data0 =  13 + RBC_ContactPacket->l_packet;
		envCanMsg.frame.data2 = envCanMsg.frame.data3 = envCanMsg.frame.data4 = 0;
		envCanMsg.frame.data5 = envCanMsg.frame.data6 = envCanMsg.frame.data7 = 0;
		envCanMsg.frame.data1 =  MESCAN_generateChecksum(tableau, envCanMsg.frame.data0+1) &0xFF;
		SendThroughCAN(&envCanMsg, tableau);
		break;
	default:
		printf("Error port type for EBT: %d\n", portType);
	}
}
