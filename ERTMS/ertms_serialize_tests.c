	#include <stdlib.h>
	#include <check.h>
#include "ertms.h"

 START_TEST(serialize_EBT_MA)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t i;
	EBT_Message EBT;
	EBT_Level1MovementAuthority MAl1;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	GSMR_SectionDescription sectionsList[32];
	GSMR_SectionDescription endSection;
	endSection.l_section = 270;
	ERTMS_SectionTimer end;
	ERTMS_SectionTimer overlap;
	initEBT_Level1MovementAuthority(&MAl1, 0, 32, 25, 260, 1, sectionsList, endSection,
	end, 0, 0, 0, overlap, 0, 0);
	initEBT(&EBT, 1, 1, 1, 0, 1, balise, 1, &MAl1);
	serializeEBT(&EBT, buffer);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq((12+EBT.packetNb12.l_packet), i);
 }
 END_TEST

 START_TEST(serialize_EBT_RBC)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t i;
	EBT_Message EBT;
	EBT_RBCTransitionOrder RbcTrans;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initEBT_RBCTransitionOrder(&RbcTrans, 0, 475, 0xF00F, 0x0FF0, 0x60016001, 0);
	initEBT(&EBT, 1, 1, 1, 0, 1, balise, 1, &RbcTrans);
	serializeEBT(&EBT, buffer);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq((12+EBT.packetNb131.l_packet), i);
 }
 END_TEST

 START_TEST(serialize_EBT_TR)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t i;
	EBT_Message EBT;
	EBT_LevelTransitionOrder LvlTrans;
	uint8_t m_leveltr_nextList[8];
	uint8_t nid_ntc_nextList[8];
	uint16_t l_ackleveltr_nextList[8];
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initEBT_LevelTransitionOrder(&LvlTrans, 0, 2500, 2, 115, 1250, 1, m_leveltr_nextList, nid_ntc_nextList, l_ackleveltr_nextList);
	initEBT(&EBT, 1, 1, 1, 0, 1, balise, 1, &LvlTrans);
	serializeEBT(&EBT, buffer);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq((12+EBT.packetNb41.l_packet), i);
 }
 END_TEST

START_TEST(serialize_CommunicationInitiationMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_CommunicationInitiationMessage startUp;
	initGSMR_CommunicationInitiationMessage(&startUp, 1234, 56);
	serializeMessage(&startUp, buffer);
	ck_assert_int_eq(startUp.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(startUp.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(startUp.l_message, i);
 }
 END_TEST

START_TEST(serialize_SystemVersionMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
 	GSMR_RBCSystemVersionMessage revision;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_RBCSystemVersionMessage(&revision, 1234, 0, balise, 22);
	serializeMessage(&revision, buffer);
	ck_assert_int_eq(revision.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(revision.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(revision.l_message, i);
}
 END_TEST

START_TEST(serialize_SessionEstablishedMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_SessionEstablishedMessage session;
	initGSMR_SessionEstablishedMessage(&session, 1234, 56);
	serializeMessage(&session, buffer);
	ck_assert_int_eq(session.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(session.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(session.l_message, i);
}
 END_TEST

START_TEST(serialize_ValidatedTrainDataMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_ValidatedTrainDataMessage posReport;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	GSMR_ValidatedTrainDataPacket trainPacket;
	GSMR_PositionReportPacket packet0;
	GSMR_engine_identifier engDescript[32];
	engDescript[0].m_voltage = 3;
	engDescript[0].nid_ctraction = 314;
	uint8_t idNat[32];
	initGSMR_PositionReportPacket(&packet0, 1, balise, 987, 1, 1, 7, 5, 1, 300,	85, 1, 2, 2, 0);
	initGSMR_ValidatedTrainDataPacket(&trainPacket, 1, 1, 150, 130, 1, 2, 1, 10, 1, engDescript, 0, idNat);
	initGSMR_ValidatedTrainDataMessage(&posReport, 1234, 56, &packet0, trainPacket);
	serializeMessage(&posReport, buffer);
	ck_assert_int_eq(posReport.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(posReport.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(posReport.l_message, i);
}
 END_TEST

START_TEST(serialize_ACKTrainDataMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_ACKTrainDataMessage ackRBC;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_ACKTrainDataMessage(&ackRBC, 1234, 0, balise, 345);
	serializeMessage(&ackRBC, buffer);
	ck_assert_int_eq(ackRBC.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(ackRBC.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(ackRBC.l_message, i);
}
 END_TEST

START_TEST(serialize_MARequestMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_MARequestMessage MAreq;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	GSMR_PositionReportPacket packet0;
	initGSMR_PositionReportPacket(&packet0, 1, balise, 987, 1, 1, 7, 5, 1, 300,	85, 1, 2, 2, 0);
	initGSMR_MARequestMessage(&MAreq, 1234, 56, 1, &packet0);
	serializeMessage(&MAreq, buffer);
	ck_assert_int_eq(MAreq.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(MAreq.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(MAreq.l_message, i);
}
 END_TEST

START_TEST(serialize_MovementAuthorityMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_MovementAuthorityMessage MAmess;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	GSMR_Level2_3MovementAuthorityPacket MApack;
	GSMR_SectionDescription fakeSection[32];
	GSMR_SectionDescription finalSection;
	ERTMS_SectionTimer endTimer, ovrlap;
	initGSMR_Level2_3MovementAuthorityPacket(&MApack, 1, 1,	20, 50, 0, fakeSection, finalSection, endTimer, 0, 200, 20, ovrlap, 0, 15);
	initGSMR_MovementAuthorityMessage(&MAmess, 1234, 0, balise, MApack);
	serializeMessage(&MAmess, buffer);
	ck_assert_int_eq(MAmess.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(MAmess.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(MAmess.l_message, i);
}
 END_TEST

START_TEST(serialize_SRAuthorisationMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_SRAuthorisationMessage SRAmess;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_SRAuthorisationMessage(&SRAmess, 1234, 0, balise, 1, 345);
	serializeMessage(&SRAmess, buffer);
	ck_assert_int_eq(SRAmess.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(SRAmess.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(SRAmess.l_message, i);
}
 END_TEST

START_TEST(serialize_Acknowledgment)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_Acknowledgment ackTrain;
	initGSMR_Acknowledgment(&ackTrain, 1234, 56, 345);
	serializeMessage(&ackTrain, buffer);
	ck_assert_int_eq(ackTrain.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(ackTrain.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(ackTrain.l_message, i);
}
 END_TEST

START_TEST(serialize_EndOfMission)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_EndOfMission EOM;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	GSMR_PositionReportPacket packet0;
	initGSMR_PositionReportPacket(&packet0, 1, balise, 987, 1, 1, 7, 5, 1, 300,	85, 1, 2, 2, 0);
	initGSMR_EndOfMission(&EOM, 1234, 56, &packet0);
	serializeMessage(&EOM, buffer);
	ck_assert_int_eq(EOM.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(EOM.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(EOM.l_message, i);
}
 END_TEST

START_TEST(serialize_AckTerminationCommunicationSession)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b, i;
	GSMR_AckTerminationCommunicationSession termACK;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_AckTerminationCommunicationSession(&termACK, 1234, 0, balise);
	serializeMessage(&termACK, buffer);
	ck_assert_int_eq(termACK.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	ck_assert_int_eq(termACK.l_message, result16b);
	for (i = 0; i<300; i++)
	{
		if (buffer[i] == 0xFF)
			break;
	}
	ck_assert_int_eq(termACK.l_message, i);
}
 END_TEST
