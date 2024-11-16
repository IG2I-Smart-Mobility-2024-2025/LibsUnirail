	#include <stdlib.h>
	#include <check.h>
#include "ertms.h"

 
 START_TEST(init_EBT_Level1MovementAuthorityPacket)
 {
	printf("\tInitializing EBT_Level1MovementAuthority\n");
	EBT_Level1MovementAuthority MAl1;
	GSMR_SectionDescription sectionsList[32];
	GSMR_SectionDescription endSection;
	endSection.l_section = 270;
	ERTMS_SectionTimer end;
	ERTMS_SectionTimer overlap;
	initEBT_Level1MovementAuthority(&MAl1, 0, 32, 25, 260, 1, sectionsList, endSection,
	end, 0, 0, 0, overlap, 0, 0);
	ck_assert_int_eq(MAl1.nid_packet, 12);
	ck_assert_int_eq(MAl1.l_packet, 41);
	ck_assert_int_eq(MAl1.endsection.l_section, 270);
 }
 END_TEST
 
START_TEST(init_EBT_LevelTransitionOrder)
 {
	printf("\tInitializing EBT_LevelTransitionOrder\n");
	EBT_LevelTransitionOrder LvlTrans;
	uint8_t m_leveltr_nextList[8];
	uint8_t nid_ntc_nextList[8];
	uint16_t l_ackleveltr_nextList[8];
	initEBT_LevelTransitionOrder(&LvlTrans, 0, 2500, 2, 115, 1250, 1, m_leveltr_nextList, nid_ntc_nextList, l_ackleveltr_nextList);
	ck_assert_int_eq(LvlTrans.nid_packet, 41);
	ck_assert_int_eq(LvlTrans.l_packet, 16);
	ck_assert_int_eq(LvlTrans.m_leveltr, 2);
 }
 END_TEST
 
START_TEST(init_EBT_RBCTransitionOrder)
 {
	printf("\tInitializing EBT_RBCTransitionOrder\n");
	EBT_RBCTransitionOrder RbcTrans;
	initEBT_RBCTransitionOrder(&RbcTrans, 0, 475, 0xF00F, 0x0FF0, 0x60016001, 0);
	ck_assert_int_eq(RbcTrans.nid_packet, 131);
	ck_assert_int_eq(RbcTrans.l_packet, 20);
	ck_assert_int_eq(RbcTrans.nid_c, 0xF00F);
	ck_assert_int_eq(RbcTrans.nid_rbc, 0x0FF0);
	ck_assert_int_eq(RbcTrans.nid_radio, 0x60016001);
 }
 END_TEST
 
 START_TEST(init_EBT)
 {
	printf("\tInitializing EBT\n");
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
	ck_assert_int_eq(EBT.nid_lrbg.nid_c, 25);
	ck_assert_int_eq(EBT.nid_lrbg.nid_bg, 45);
 }
 END_TEST
 
 START_TEST(init_CommunicationInitiationMessage)
 {
	printf("\tInitializing GSMR_CommunicationInitiationMessage\n");
	GSMR_CommunicationInitiationMessage startUp;
	initGSMR_CommunicationInitiationMessage(&startUp, 1234, 56);
	ck_assert_int_eq(startUp.nid_message, 155);
	ck_assert_int_eq(startUp.l_message, 11);
	ck_assert_int_eq(startUp.t_train, 1234);
	ck_assert_int_eq(startUp.nid_engine, 56);
 }
 END_TEST
 
 START_TEST(init_RBCSystemVersionMessage)
 {
	printf("\tInitializing GSMR_RBCSystemVersionMessage\n");
	GSMR_RBCSystemVersionMessage revision;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_RBCSystemVersionMessage(&revision, 1234, 0, balise, 22);
	ck_assert_int_eq(revision.nid_message, 32);
	ck_assert_int_eq(revision.l_message, 13);
	ck_assert_int_eq(revision.t_train, 1234);
	ck_assert_int_eq(revision.nid_lrbg.nid_c, 25);
	ck_assert_int_eq(revision.nid_lrbg.nid_bg, 45);
	ck_assert_int_eq(revision.m_version, 22);
 }
 END_TEST
 
 START_TEST(init_SessionEstablishedMessage)
 {
	printf("\tInitializing GSMR_SessionEstablishedMessage\n");
	GSMR_SessionEstablishedMessage session;
	initGSMR_SessionEstablishedMessage(&session, 1234, 56);
	ck_assert_int_eq(session.nid_message, 159);
	ck_assert_int_eq(session.l_message, 11);
	ck_assert_int_eq(session.t_train, 1234);
	ck_assert_int_eq(session.nid_engine, 56);
 }
 END_TEST
 
 START_TEST(init_ValidatedTrainDataMessage)
 {
	printf("\tInitializing GSMR_ValidatedTrainDataMessage\n");
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
	ck_assert_int_eq(posReport.nid_message, 129);
	ck_assert_int_eq(posReport.l_message, 54);
	ck_assert_int_eq(posReport.t_train, 1234);
	ck_assert_int_eq(posReport.nid_engine, 56);
	ck_assert_int_eq(posReport.packetNb0.nid_lrbg.nid_c, 25);
	ck_assert_int_eq(posReport.packetNb0.nid_lrbg.nid_bg, 45);
	ck_assert_int_eq(posReport.packetNb11.engine_identifier[0].m_voltage, 3);
	ck_assert_int_eq(posReport.packetNb11.engine_identifier[0].nid_ctraction, 314);
 }
 END_TEST

 START_TEST(init_ACKTrainDataMessage)
 {
	printf("\tInitializing GSMR_ACKTrainDataMessage\n");
	GSMR_ACKTrainDataMessage ackRBC;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_ACKTrainDataMessage(&ackRBC, 1234, 0, balise, 345);
	ck_assert_int_eq(ackRBC.nid_message, 8);
	ck_assert_int_eq(ackRBC.l_message, 16);
	ck_assert_int_eq(ackRBC.t_train, 1234);
	ck_assert_int_eq(ackRBC.m_ack, 0);
	ck_assert_int_eq(ackRBC.nid_lrbg.nid_c, 25);
	ck_assert_int_eq(ackRBC.nid_lrbg.nid_bg, 45);
	ck_assert_int_eq(ackRBC.t_trainMessageOrigin, 345);
 }
 END_TEST

 START_TEST(init_MARequestMessage)
 {
	printf("\tInitializing GSMR_MARequestMessage\n");
	GSMR_MARequestMessage MAreq;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	GSMR_PositionReportPacket packet0;
	initGSMR_PositionReportPacket(&packet0, 1, balise, 987, 1, 1, 7, 5, 1, 300,	85, 1, 2, 2, 0);
	initGSMR_MARequestMessage(&MAreq, 1234, 56, 1, &packet0);
	ck_assert_int_eq(MAreq.nid_message, 132);
	ck_assert_int_eq(MAreq.l_message, 36);
	ck_assert_int_eq(MAreq.t_train, 1234);
	ck_assert_int_eq(MAreq.nid_engine, 56);
 	ck_assert_int_eq(MAreq.packetNb0.nid_lrbg.nid_c, 25);
	ck_assert_int_eq(MAreq.packetNb0.nid_lrbg.nid_bg, 45);
}
 END_TEST

 START_TEST(init_MovementAuthorityMessage)
 {
	printf("\tInitializing GSMR_MovementAuthorityMessage\n");
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
	ck_assert_int_eq(MAmess.nid_message, 3);
	ck_assert_int_eq(MAmess.l_message, 45);
	ck_assert_int_eq(MAmess.t_train, 1234);
	ck_assert_int_eq(MAmess.m_ack, 0);
 }
 END_TEST

 START_TEST(init_SRAuthorisationMessage)
 {
	printf("\tInitializing GSMR_SRAuthorisationMessage\n");
	GSMR_SRAuthorisationMessage SRAmess;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_SRAuthorisationMessage(&SRAmess, 1234, 0, balise, 1, 345);
	ck_assert_int_eq(SRAmess.nid_message, 2);
	ck_assert_int_eq(SRAmess.l_message, 15);
	ck_assert_int_eq(SRAmess.t_train, 1234);
	ck_assert_int_eq(SRAmess.m_ack, 0);
	ck_assert_int_eq(SRAmess.nid_lrbg.nid_c, 25);
	ck_assert_int_eq(SRAmess.nid_lrbg.nid_bg, 45);
 }
 END_TEST

 START_TEST(init_Acknowledgment)
 {
	printf("\tInitializing GSMR_Acknowledgment\n");
	GSMR_Acknowledgment ackTrain;
	initGSMR_Acknowledgment(&ackTrain, 1234, 56, 345);
	ck_assert_int_eq(ackTrain.nid_message, 146);
	ck_assert_int_eq(ackTrain.l_message, 15);
	ck_assert_int_eq(ackTrain.t_train, 1234);
	ck_assert_int_eq(ackTrain.nid_engine, 56);
	ck_assert_int_eq(ackTrain.t_trainMessageOrigin, 345);
 }
 END_TEST
 
START_TEST(init_EndOfMission)
 {
	printf("\tInitializing GSMR_EndOfMission\n");
	GSMR_EndOfMission EOM;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	GSMR_PositionReportPacket packet0;
	initGSMR_PositionReportPacket(&packet0, 1, balise, 987, 1, 1, 7, 5, 1, 300,	85, 1, 2, 2, 0);
	initGSMR_EndOfMission(&EOM, 1234, 56, &packet0);
	ck_assert_int_eq(EOM.nid_message, 150);
	ck_assert_int_eq(EOM.l_message, 35);
	ck_assert_int_eq(EOM.t_train, 1234);
	ck_assert_int_eq(EOM.nid_engine, 56);
 	ck_assert_int_eq(EOM.packetNb0.nid_lrbg.nid_c, 25);
	ck_assert_int_eq(EOM.packetNb0.nid_lrbg.nid_bg, 45);
}
 END_TEST

START_TEST(init_AckTerminationCommunicationSession)
 {
	printf("\tInitializing GSMR_AckTerminationCommunicationSession\n");
	GSMR_AckTerminationCommunicationSession termACK;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_AckTerminationCommunicationSession(&termACK, 1234, 0, balise);
	ck_assert_int_eq(termACK.nid_message, 39);
	ck_assert_int_eq(termACK.l_message, 12);
	ck_assert_int_eq(termACK.t_train, 1234);
	ck_assert_int_eq(termACK.m_ack, 0);
	ck_assert_int_eq(termACK.nid_lrbg.nid_c, 25);
	ck_assert_int_eq(termACK.nid_lrbg.nid_bg, 45);
 }
 END_TEST

START_TEST(init_NRBC_preAnnouncement)
 {
	printf("\tInitializing NRBC_preAnnouncement\n");
	NRBC_preAnnouncement preAnn;
	GSMR_ValidatedTrainDataPacket trainPacket;
	GSMR_engine_identifier engDescript[32];
	engDescript[0].m_voltage = 3;
	engDescript[0].nid_ctraction = 314;
	uint8_t idNat[32];
	initGSMR_ValidatedTrainDataPacket(&trainPacket, 1, 1, 150, 130, 1, 2, 1, 10, 1, engDescript, 0, idNat);
	initNRBC_preAnnouncement(&preAnn, 0x0123, 0x1234, 0x80808080, 0x9876, 0x8765, 0x5555, 0, 1, 0, trainPacket, NULL);
	ck_assert_int_eq(preAnn.nid_nrbcmessage, 201);
	ck_assert_int_eq(preAnn.l_message, 45);
	ck_assert_int_eq(preAnn.t_rbc, 0x5555);
	ck_assert_int_eq(preAnn.m_ack, 1);
	ck_assert_int_eq(preAnn.trainNumber.nid_packet, EMPTY_CONTENT);
 }
 END_TEST
