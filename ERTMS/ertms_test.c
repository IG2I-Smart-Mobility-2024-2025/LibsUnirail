#include "ertms_test.h" 


 START_TEST(deSerialize_EBT_MA)
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
	printf("\t");
	deSerializeEBT (&EBT, buffer);
	ck_assert_int_eq((12+EBT.packetNb12.l_packet), i);
 }
 END_TEST

 START_TEST(deSerialize_EBT_TR)
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
	printf("\t");
	deSerializeEBT (&EBT, buffer);
	ck_assert_int_eq((12+EBT.packetNb41.l_packet), i);
 }
 END_TEST

 START_TEST(deSerialize_EBT_RBC)
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
	printf("\t");
	deSerializeEBT (&EBT, buffer);
	ck_assert_int_eq((12+EBT.packetNb131.l_packet), i);
 }
 END_TEST

 START_TEST(deSerialize_CommunicationInitiationMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
	GSMR_CommunicationInitiationMessage startUp;
	initGSMR_CommunicationInitiationMessage(&startUp, 1234, 56);
	serializeMessage(&startUp, buffer);
	ck_assert_int_eq(startUp.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	printf("\t");
	deserializeMessage(buffer, startUp.nid_message, &startUp);
	ck_assert_int_eq(startUp.l_message, result16b);
 }
 END_TEST

START_TEST(deSerialize_SystemVersionMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
 	GSMR_RBCSystemVersionMessage revision;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_RBCSystemVersionMessage(&revision, 1234, 0, balise, 22);
	serializeMessage(&revision, buffer);
	ck_assert_int_eq(revision.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	printf("\t");
	deserializeMessage(buffer, revision.nid_message, &revision);
	ck_assert_int_eq(revision.l_message, result16b);
}
 END_TEST

START_TEST(deSerialize_SessionEstablishedMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
	GSMR_SessionEstablishedMessage session;
	initGSMR_SessionEstablishedMessage(&session, 1234, 56);
	serializeMessage(&session, buffer);
	ck_assert_int_eq(session.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	printf("\t");
	deserializeMessage(buffer, session.nid_message, &session);
	ck_assert_int_eq(session.l_message, result16b);
}
 END_TEST

START_TEST(deSerialize_ValidatedTrainDataMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
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
	printf("\t");
	deserializeMessage(buffer, posReport.nid_message, &posReport);
	ck_assert_int_eq(posReport.l_message, result16b);
}
 END_TEST

START_TEST(deSerialize_ACKTrainDataMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
	GSMR_ACKTrainDataMessage ackRBC;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_ACKTrainDataMessage(&ackRBC, 1234, 0, balise, 345);
	serializeMessage(&ackRBC, buffer);
	ck_assert_int_eq(ackRBC.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	printf("\t");
	deserializeMessage(buffer, ackRBC.nid_message, &ackRBC);
	ck_assert_int_eq(ackRBC.l_message, result16b);
}
 END_TEST

START_TEST(deSerialize_MARequestMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
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
	printf("\t");
	deserializeMessage(buffer, MAreq.nid_message, &MAreq);
	ck_assert_int_eq(MAreq.l_message, result16b);
}
 END_TEST

START_TEST(deSerialize_MovementAuthorityMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
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
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	printf("\t");
	deserializeMessage(buffer, MAmess.nid_message, &MAmess);
	ck_assert_int_eq(MAmess.l_message, result16b);
}
 END_TEST

START_TEST(deSerialize_SRAuthorisationMessage)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
	GSMR_SRAuthorisationMessage SRAmess;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_SRAuthorisationMessage(&SRAmess, 1234, 0, balise, 1, 345);
	serializeMessage(&SRAmess, buffer);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	printf("\t");
	deserializeMessage(buffer, SRAmess.nid_message, &SRAmess);
	ck_assert_int_eq(SRAmess.l_message, result16b);
}
 END_TEST

START_TEST(deSerialize_Acknowledgment)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
	GSMR_Acknowledgment ackTrain;
	initGSMR_Acknowledgment(&ackTrain, 1234, 56, 345);
	serializeMessage(&ackTrain, buffer);
	ck_assert_int_eq(ackTrain.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	printf("\t");
	deserializeMessage(buffer, ackTrain.nid_message, &ackTrain);
	ck_assert_int_eq(ackTrain.l_message, result16b);
}
 END_TEST

START_TEST(deSerialize_EndOfMission)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
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
	printf("\t");
	deserializeMessage(buffer, EOM.nid_message, &EOM);
	ck_assert_int_eq(EOM.l_message, result16b);
}
 END_TEST

START_TEST(deSerialize_AckTerminationCommunicationSession)
 {
	printf("\t");
	uint8_t buffer[300];
	uint16_t result16b;
	GSMR_AckTerminationCommunicationSession termACK;
	GSMR_nid_lrbg balise;
	balise.nid_c =25;
	balise.nid_bg =45;
	initGSMR_AckTerminationCommunicationSession(&termACK, 1234, 0, balise);
	serializeMessage(&termACK, buffer);
	ck_assert_int_eq(termACK.nid_message, buffer[0]);
	result16b = buffer[1]<<8;
	result16b += buffer[2];
	printf("\t");
	deserializeMessage(buffer, termACK.nid_message, &termACK);
	ck_assert_int_eq(termACK.l_message, result16b);
}
 END_TEST
 Suite * ERTMS_init_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("init_messages");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, init_EBT_Level1MovementAuthorityPacket);
    tcase_add_test(tc_core, init_EBT_LevelTransitionOrder);
    tcase_add_test(tc_core, init_EBT_RBCTransitionOrder);
    tcase_add_test(tc_core, init_EBT);
    tcase_add_test(tc_core, init_CommunicationInitiationMessage);
    tcase_add_test(tc_core, init_RBCSystemVersionMessage);
    tcase_add_test(tc_core, init_SessionEstablishedMessage);
    tcase_add_test(tc_core, init_ValidatedTrainDataMessage);
    tcase_add_test(tc_core, init_ACKTrainDataMessage);
    tcase_add_test(tc_core, init_MARequestMessage);
    tcase_add_test(tc_core, init_MovementAuthorityMessage);
    tcase_add_test(tc_core, init_SRAuthorisationMessage);
    tcase_add_test(tc_core, init_Acknowledgment);
    tcase_add_test(tc_core, init_EndOfMission);
    tcase_add_test(tc_core, init_AckTerminationCommunicationSession);
    tcase_add_test(tc_core, init_NRBC_preAnnouncement);
    suite_add_tcase(s, tc_core);

    return s;
}

Suite * ERTMS_serialize_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("serialize_messages");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, serialize_EBT_MA);
    tcase_add_test(tc_core, serialize_EBT_TR);
    tcase_add_test(tc_core, serialize_EBT_RBC);
    tcase_add_test(tc_core, serialize_CommunicationInitiationMessage);
    tcase_add_test(tc_core, serialize_SystemVersionMessage);
    tcase_add_test(tc_core, serialize_SessionEstablishedMessage);
    tcase_add_test(tc_core, serialize_ValidatedTrainDataMessage);
    tcase_add_test(tc_core, serialize_ACKTrainDataMessage);
    tcase_add_test(tc_core, serialize_MARequestMessage);
    tcase_add_test(tc_core, serialize_MovementAuthorityMessage);
    tcase_add_test(tc_core, serialize_SRAuthorisationMessage);
    tcase_add_test(tc_core, serialize_Acknowledgment);
    tcase_add_test(tc_core, serialize_EndOfMission);
    tcase_add_test(tc_core, serialize_AckTerminationCommunicationSession);
    suite_add_tcase(s, tc_core);

    return s;
}

Suite * ERTMS_deSerialize_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("deSerialize_messages");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, deSerialize_EBT_MA);
    tcase_add_test(tc_core, deSerialize_EBT_TR);
    tcase_add_test(tc_core, deSerialize_EBT_RBC);
    tcase_add_test(tc_core, deSerialize_CommunicationInitiationMessage);
    tcase_add_test(tc_core, deSerialize_SystemVersionMessage);
    tcase_add_test(tc_core, deSerialize_SessionEstablishedMessage);
    tcase_add_test(tc_core, deSerialize_ValidatedTrainDataMessage);
    tcase_add_test(tc_core, deSerialize_ACKTrainDataMessage);
    tcase_add_test(tc_core, deSerialize_MARequestMessage);
    tcase_add_test(tc_core, deSerialize_MovementAuthorityMessage);
    tcase_add_test(tc_core, deSerialize_SRAuthorisationMessage);
    tcase_add_test(tc_core, deSerialize_Acknowledgment);
    tcase_add_test(tc_core, deSerialize_EndOfMission);
    tcase_add_test(tc_core, deSerialize_AckTerminationCommunicationSession);
    suite_add_tcase(s, tc_core);

    return s;
}

 int main(void)
 {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = ERTMS_init_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
	
    s = ERTMS_serialize_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
	
    s = ERTMS_deSerialize_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
	
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }