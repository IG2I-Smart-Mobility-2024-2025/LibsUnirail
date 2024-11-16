#ifndef ERTMS_H
	#define ERTMS_H
#define DEBUG
#define EMPTY_CONTENT 0xEC	///<flag to signal an empty optional value
#include <stdio.h>
#include "GSM_R_message.h"
#include "NRBC_message.h"
#include "EBT_message.h"

/// Facteur d'echelle pour les distances (par rapport aux valeurs de Q_SCALE de ERTMS-> pour une echelle de 1/500 cela donne: (rappel: echelle O=(~1/50))
/**
    <table>
    <caption id="Transformation d'echelles">Transformation des echelles selon le facteur d'echelles</caption>
    <tr><th>Valeur Q_SCALE 		<th>0 		<th>1 		<th>2  		<th>3
    <tr><td>Echelle ERTMS 		<td>10cm	<td>1m 		<td>10m 	<td>spare
    <tr><td>Echelle transformee <td>0.2mm	<td>2mm		<td>2cm		<td>spare
    </table>
	Cela s'applique aussi aux longueurs des trains, ou la resolution passe de 1m a 2cm, et L_DOUBTOVER et L_DOUBTUNDER qui sont affectes par Q_SCALE
 */
#define SCALE_FACTOR_DISTANCE 0.002 

/// Facteur d'echelle pour le temps (qui affecte aux resolutions de T_TRAIN, T_SECTIONTIMER et avec SCALE_FACTOR_DISTANCE, aux vitesses -> pour une echelle 0.28 cela donne:
/**
    <table>
    <caption id="Transformation de temps">Transformation des temps et vitesses selon le facteur</caption>
    <tr><th>Variables	 			<th>T_TRAIN 		<th>T_SECTIONTIMER et timeouts	<th>V_MAXTRAIN et autre vitesses
    <tr><td>Resolution ERTMS 		<td>10ms			<td>1s 							<td>5km/h						
    <tr><td>Resolution transformee 	<td>2.8ms	 		<td>0.28s						<td>0.99cm/s
    </table>
 */
#define SCALE_FACTOR_TIME 0.277

	/*--------------------------------------Packets--------------------------------------*/

/// Fonction d'initialisation du packet EBT_Level1MovementAuthority.
/**
nid_packet(12), q_dir(1) et l_packet(17-258) sont remplies automatiquement.
 */
void initEBT_Level1MovementAuthority(EBT_Level1MovementAuthority* pointer, uint8_t q_scale, uint8_t v_main, uint8_t v_ema, uint16_t t_ema,
	uint8_t n_iter_sections, GSMR_SectionDescription section[32], GSMR_SectionDescription endsection, ERTMS_SectionTimer end,
	uint8_t q_dangerpoint, uint16_t d_dp, uint8_t v_releasedp, ERTMS_SectionTimer overlap, uint16_t d_startol, uint8_t v_releaseol);
	
/// Fonction d'initialisation du packet EBT_LevelTransitionOrder.
/**
nid_packet(41), q_dir(1) et l_packet(12-257) sont remplies automatiquement.
 */
void initEBT_LevelTransitionOrder(EBT_LevelTransitionOrder* pointer, uint8_t q_scale, uint16_t d_leveltr,
	uint8_t m_leveltr, uint8_t nid_ntc, uint16_t l_ackleveltr, uint8_t n_iter_next, uint8_t m_leveltr_next[8], 
	uint8_t nid_ntc_next[8], uint16_t l_ackleveltr_next[8]);
	
/// Fonction d'initialisation du packet EBT_RBCTransitionOrder.
/**
nid_packet(131), q_dir(1) et l_packet(20) sont remplies automatiquement.
 */
void initEBT_RBCTransitionOrder(EBT_RBCTransitionOrder* pointer, uint8_t q_scale, uint16_t d_rbctr, uint16_t nid_c,
	uint16_t nid_rbc, uint64_t nid_radio, uint8_t q_sleepsession);
	
/// Fonction d'initialisation du packet GSMR_TrainRunningNumber.
/**
nid_packet(5) et l_packet(7) sont remplies automatiquement.
 */
void initGSMR_TrainRunningNumber(GSMR_TrainRunningNumber* pointer, uint32_t nid_operational);
	
/// Fonction d'initialisation du packet GSMR_PositionReportPacket.
/**
nid_packet(0) et l_packet(24) sont remplies automatiquement.
 */
void initGSMR_PositionReportPacket(GSMR_PositionReportPacket* pointer, uint8_t q_scale, GSMR_nid_lrbg nid_lrbg, int16_t d_lrbg,
	uint8_t q_dirlrbg, uint8_t q_dlrbg, uint16_t l_doubtover, uint16_t l_doubtunder, uint8_t q_length, uint16_t l_traininit,
	uint8_t v_train, uint8_t q_dirtrain, uint8_t m_mode, uint8_t m_level, uint8_t nid_ntc);
	
/// Fonction d'initialisation du packet GSMR_PositionReportPacketTwoBaliseGroups.
/**
nid_packet(1) et l_packet(28) sont remplies automatiquement.
 */
void initGSMR_PositionReportPacketTwoBaliseGroups(GSMR_PositionReportPacketTwoBaliseGroups* pointer, uint8_t q_scale, GSMR_nid_lrbg nid_lrbg, 
	GSMR_nid_lrbg nid_prvlrbg, uint16_t d_lrbg, uint8_t q_dirlrbg, uint8_t q_dlrbg, uint16_t l_doubtover, uint16_t l_doubtunder,
	uint8_t q_length, uint16_t l_traininit, uint8_t v_train, uint8_t q_dirtrain, uint8_t m_mode, uint8_t m_level, uint8_t nid_ntc);

/// Fonction d'initialisation du packet GSMR_ValidatedTrainDataPacket.
/**
nid_packet(11) et l_packet(16-144) sont remplies automatiquement.
 */
void initGSMR_ValidatedTrainDataPacket(GSMR_ValidatedTrainDataPacket* pointer, uint8_t nc_cdtrain, uint16_t nc_train, 
	uint16_t l_train, uint8_t v_maxtrain, uint8_t m_loadinggauge, uint8_t m_axleloadcat, uint8_t m_airtight, uint16_t n_axle,
	uint8_t n_iter_engine, GSMR_engine_identifier engine_identifier[32], uint8_t n_iter_ntc, uint8_t nid_ntc[32]);

/// Fonction d'initialisation du packet GSMR_DataOutsideErtmsPacket.
/**
nid_packet(44) et l_packet(6-263) sont remplies automatiquement.
 */
void initGSMR_DataOutsideErtmsPacket(GSMR_DataOutsideErtmsPacket* pointer, uint8_t q_dir, uint16_t nid_xuser, uint8_t nid_ntc,
	uint8_t n_iter_stops, GSMR_ItineraryDescription stops[32]);

/// Fonction d'initialisation du packet GSMR_Level2_3MovementAuthorityPacket.
/**
nid_packet(15) et l_packet(33-257) sont remplies automatiquement.
 */
void initGSMR_Level2_3MovementAuthorityPacket(GSMR_Level2_3MovementAuthorityPacket* pointer, uint8_t q_dir,	uint8_t q_scale,
	uint8_t v_ema, uint16_t t_ema, uint8_t n_iter_section, GSMR_SectionDescription section[32], GSMR_SectionDescription endsection,
	ERTMS_SectionTimer end, uint8_t q_dangerpoint, uint16_t d_dp, uint8_t v_releasedp, ERTMS_SectionTimer overlap, uint16_t d_startol,
	uint8_t v_releaseol);

/// Fonction d'initialisation du packet GSMR_GradientProfilePacket.
/**
nid_packet(21) et l_packet(10-138) sont remplies automatiquement.
 */
void initGSMR_GradientProfilePacket(GSMR_GradientProfilePacket* pointer, uint8_t q_dir,	uint8_t q_scale, uint16_t d_gradient_first,
	uint8_t q_gdir_first, uint8_t g_a_first, uint8_t n_iter, uint16_t d_gradient[32], uint8_t q_gdir[32], uint8_t g_a[32]);

/// Fonction d'initialisation du packet GSMR_IntStatSpeedProfile.
/**
nid_packet(27) et l_packet(11-3339) sont remplies automatiquement.
	nc_cddiffFirst et nc_cddiff peuvent contenir nc_diffFirst ou nc_diff
 */
void initGSMR_IntStatSpeedProfile(GSMR_IntStatSpeedProfile* pointer, uint8_t q_dir, uint8_t q_scale, uint16_t d_staticFisrt,
	uint8_t v_staticFirst, uint8_t q_frontFirst, uint8_t n_iterDiffFirst, uint8_t q_diffFirst[32], uint8_t nc_cddiffFirst[32], uint8_t v_diffFirst[32],
	uint8_t n_iterStatic, uint16_t d_static[32], uint8_t v_static[32], uint8_t q_front[32], uint8_t n_iterDiff[32], uint8_t q_diff[32][32],
	uint8_t nc_cddiff[32][32], uint8_t v_diff[32][32]);

	/*--------------------------------------EBT & GSMR messages--------------------------------------*/
	
	
/// Fonction d'initialisation d'un EBT_Message.
/**
q_updown(1) et q_media(0) sont remplies automatiquement (pas de support format EuroLoop).
packetPointer doit etre du type:EBT_Level1MovementAuthority, EBT_RepositioningInformation, EBT_LevelTransitionOrder ou EBT_NationalValues
 */
void initEBT(EBT_Message* pointer, uint8_t m_version, uint8_t n_pig, uint8_t n_total, uint8_t m_dup,
	uint8_t m_mcount, GSMR_nid_lrbg nid_lrbg, uint8_t q_link, void* packetPointer);

/// Fonction d'initialisation du message GSMR_CommunicationInitiationMessage.
/**
nid_message(155) et l_message(8) sont remplies automatiquement.
 */
void initGSMR_CommunicationInitiationMessage(GSMR_CommunicationInitiationMessage* pointer, uint32_t timeStamp, uint32_t nidEngine);

/// Fonction d'initialisation du message GSMR_RBCSystemVersionMessage.
/**
nid_message(32) et l_message(13) sont remplies automatiquement.
 */
void initGSMR_RBCSystemVersionMessage(GSMR_RBCSystemVersionMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint8_t m_version);

/// Fonction d'initialisation du message GSMR_SessionEstablishedMessage.
/**
nid_message(159) et l_message(8) sont remplies automatiquement.
 */
void initGSMR_SessionEstablishedMessage(GSMR_SessionEstablishedMessage* pointer, uint32_t timeStamp, uint32_t nidEngine);

/// Fonction d'initialisation du message GSMR_NoCompatibleVersionSupported.
/**
nid_message(154) et l_message(11) sont remplies automatiquement.
 */
void initGSMR_NoCompatibleVersionSupported(GSMR_NoCompatibleVersionSupported* pointer, uint32_t timeStamp, uint32_t nidEngine);

/// Fonction d'initialisation du message GSMR_SoM_PositionReport.
/**
nid_message(157) et l_message(30-307) sont remplies automatiquement.<BR>
GSMR_TrainRunningNumber et GSMR_DataOutsideErtmsPacket sont optionnels, NULL si inexistants
 */
void initGSMR_SoM_PositionReport(GSMR_SoM_PositionReport* pointer, uint32_t timeStamp, uint32_t nidEngine, uint8_t q_status, void* positionPacketPointer,
	GSMR_TrainRunningNumber* trainNumber, GSMR_DataOutsideErtmsPacket* itinerary );

/// Fonction d'initialisation du message GSMR_SoMPositionConfirmed.
/**
nid_message(43) et l_message(12) sont remplies automatiquement.<BR>
*/
void initGSMR_SoMPositionConfirmed(GSMR_SoMPositionConfirmed* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg);

/// Fonction d'initialisation du message GSMR_ValidatedTrainDataMessage.
/**
nid_message(129) et l_message(45-180) sont remplies automatiquement.
packetPointer doit etre du type:GSMR_PositionReportPacket ou GSMR_PositionReportPacketTwoBaliseGroups
 */
void initGSMR_ValidatedTrainDataMessage(GSMR_ValidatedTrainDataMessage* pointer, uint32_t timeStamp, uint32_t nidEngine, void* packetPointer, GSMR_ValidatedTrainDataPacket packetNb11);

/// Fonction d'initialisation du message GSMR_ACKTrainDataMessage.
/**
nid_message(32) et l_message(13) sont remplies automatiquement.
 */
void initGSMR_ACKTrainDataMessage(GSMR_ACKTrainDataMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint32_t firstTimeStamp);

/// Fonction d'initialisation du message GSMR_MARequestMessage.
/**
nid_message(132) et l_message(33-37) sont remplies automatiquement.
packetPointer doit etre du type:GSMR_PositionReportPacket ou GSMR_PositionReportPacketTwoBaliseGroups
 */
void initGSMR_MARequestMessage(GSMR_MARequestMessage* pointer, uint32_t timeStamp, uint32_t nidEngine, uint8_t q_marqstreason, void* packetPointer);

/// Fonction d'initialisation du message GSMR_MovementAuthorityMessage.
/**
nid_message(3) et l_message(27-269) sont remplies automatiquement.
 */
void initGSMR_MovementAuthorityMessage(GSMR_MovementAuthorityMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, GSMR_Level2_3MovementAuthorityPacket packetnb15);

/// Fonction d'initialisation du message GSMR_SRAuthorisationMessage.
/**
nid_message(2) et l_message(15) sont remplies automatiquement.
 */
void initGSMR_SRAuthorisationMessage(GSMR_SRAuthorisationMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint8_t q_scale, uint16_t d_sr);

/// Fonction d'initialisation du message GSMR_Acknowledgment.
/**
nid_message(146) et l_message(12) sont remplies automatiquement.
 */
void initGSMR_Acknowledgment(GSMR_Acknowledgment* pointer, uint32_t timeStamp, uint32_t nidEngine, uint32_t firstTimeStamp);

/// Fonction d'initialisation du message GSMR_EndOfMission.
/**
nid_message(150) et l_message(29-36) sont remplies automatiquement.
packetPointer doit etre du type:GSMR_PositionReportPacket ou GSMR_PositionReportPacketTwoBaliseGroups
 */
void initGSMR_EndOfMission(GSMR_EndOfMission* pointer, uint32_t timeStamp, uint32_t nidEngine, void* packetPointer);

/// Fonction d'initialisation du message GSMR_AckTerminationCommunicationSession.
/**
nid_message(39) et l_message(12) sont remplies automatiquement.
 */
void initGSMR_AckTerminationCommunicationSession(GSMR_AckTerminationCommunicationSession* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg);

	/*--------------------------------------NRBC--------------------------------------*/
	
/// Fonction d'initialisation du message NRBC_preAnnouncement.
/**
nid_nrbcmessage(201), l_message(30-181) et m_ack(1) sont remplies automatiquement.
GSMR_TrainRunningNumber est optionnel, NULL si inexistant
 */
void initNRBC_preAnnouncement(NRBC_preAnnouncement* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg,
	uint32_t timeStamp, uint8_t m_mode, uint8_t q_masterengine, uint32_t nidLeadingEngine, GSMR_ValidatedTrainDataPacket packetNb11, GSMR_TrainRunningNumber* trainNumber);
	
/// Fonction d'initialisation du message NRBC_RRI_request.
/**
nid_nrbcmessage(202), et l_message(25-41) sont remplies automatiquement.
*/
void initNRBC_RRI_request(NRBC_RRI_request* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack,
	uint16_t d_remaindistance, uint8_t n_remaineoaintervals, uint8_t n_remaintsr, uint8_t q_addrestrictions, uint8_t n_remainlinkedbg, uint8_t n_remaingradientchange, uint8_t n_remainmasection,
	uint8_t n_remainspeedchange, uint8_t n_remaintrackcondition, uint8_t n_remainasp, uint8_t n_remainmodeprofile, uint8_t n_remainlx, uint8_t n_remainplatform, uint8_t n_remainpbd,
	uint8_t q_remainaxleload, uint8_t q_remainloadinggauge, uint8_t q_remaintraction, uint8_t q_remainleveltransition, uint8_t q_remaintractionsystemchange, uint8_t q_remaincurrent);

/// Fonction d'initialisation du message NRBC_announcement.
/**
nid_nrbcmessage(203), et l_message(20) sont remplies automatiquement.
*/
void initNRBC_announcement(NRBC_announcement* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack);

/// Fonction d'initialisation du message NRBC_RRI_confirmation.
/**
nid_nrbcmessage(206), et l_message(25) sont remplies automatiquement.
*/
void initNRBC_RRI_confirmation(NRBC_RRI_confirmation* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack, 
	uint32_t t_rbcconf, uint8_t q_rriconfstatus);

/// Fonction d'initialisation du message NRBC_TrainData.
/**
nid_nrbcmessage(207), et l_message(36-164) sont remplies automatiquement.
*/
void initNRBC_TrainData(NRBC_TrainData* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack, 
	GSMR_ValidatedTrainDataPacket trainData);

/// Fonction d'initialisation du message NRBC_TrainRunningNumber.
/**
nid_nrbcmessage(208), et l_message(27) sont remplies automatiquement.
*/
void initNRBC_TrainRunningNumber(NRBC_TrainRunningNumber* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack, 
	GSMR_TrainRunningNumber trainNumber);

/// Fonction d'initialisation du message NRBC_RRI.
/**
nid_nrbcmessage(221), et l_message(76-3757) sont remplies automatiquement.
*/
void initNRBC_RRI(NRBC_RRI* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack, uint8_t rrimachange, 
	uint8_t tdchange, uint8_t matimer, GSMR_Level2_3MovementAuthorityPacket MA, GSMR_GradientProfilePacket gradient, GSMR_IntStatSpeedProfile SSP);

/// Fonction d'initialisation du message NRBC_TakingOverResponsibility.
/**
nid_nrbcmessage(222), et l_message(20) sont remplies automatiquement.
*/
void initNRBC_TakingOverResponsibility(NRBC_TakingOverResponsibility* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack);

/// Fonction d'initialisation du message NRBC_RequestRRIConfirmation.
/**
nid_nrbcmessage(224), l_message(56-280) et m_ack (1) sont remplies automatiquement.
*/
void initNRBC_RequestRRIConfirmation(NRBC_RequestRRIConfirmation* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t q_rrimachange,
	uint8_t q_tdchange, uint8_t q_matimer, GSMR_Level2_3MovementAuthorityPacket MA);

/// Fonction d'initialisation du message NRBC_ACK.
/**
nid_nrbcmessage(205), l_message(24) et m_ack (1) sont remplies automatiquement.
*/
void initNRBC_ACK(NRBC_ACK* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint32_t origTimeStamp);

/// Fonction d'initialisation du message NRBC_Cancellation.
/**
nid_nrbcmessage(204), et l_message(20) sont remplies automatiquement.
*/
void initNRBC_Cancellation(NRBC_Cancellation* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack);

/// Fonction d'initialisation du message NRBC_LifeSign.
/**
nid_nrbcmessage(223), et l_message(11) sont remplies automatiquement.
*/
void initNRBC_LifeSign(NRBC_LifeSign* pointer, uint16_t nid_c, uint16_t nid_rbc, uint32_t timeStamp);


	/*--------------------------------------Serialisation et deserialisation--------------------------------------*/
	
/// Fonction de serialisation EBT_Message.
/**
La trame finit par 0xFF (255)
 */
int serializeEBT (EBT_Message* messagePointer, uint8_t* buffer);
/// Fonction de serialisation GSMR_Message.
/**
La trame finit par 0xFF (255)
 */
int serializeMessage (void* messagePointer, uint8_t* buffer);

/// Fonction de serialisation NRBC.
/**
La trame finit par 0xFF (255)
 */
int serializeNRBC (void* nrbcPointer, uint8_t* buffer);

uint16_t serializeUint16(uint16_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeUint32(uint32_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeUint64(uint64_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeEBT_Level1MovementAuthority(EBT_Level1MovementAuthority* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeEBT_LevelTransitionOrder(EBT_LevelTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeEBT_RBCTransitionOrder(EBT_RBCTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_TrainRunningNumber(GSMR_TrainRunningNumber* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_PositionReportPacketTwoBaliseGroups(GSMR_PositionReportPacketTwoBaliseGroups* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_PositionReportPacket(GSMR_PositionReportPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_DataOutsideErtmsPacket(GSMR_DataOutsideErtmsPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_Level2_3MovementAuthorityPacket(GSMR_Level2_3MovementAuthorityPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_ValidatedTrainDataPacket(GSMR_ValidatedTrainDataPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_GradientProfilePacket(GSMR_GradientProfilePacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_IntStatSpeedProfile(GSMR_IntStatSpeedProfile* dataPointer, uint8_t* buffer, uint16_t counter);


int deSerializeEBT (EBT_Message* messagePointer, uint8_t* buffer);
int deserializeMessage(uint8_t* buffer, uint8_t messNb, void* messagePointer);
int deSerializeNRBC (uint8_t* buffer, uint8_t messNb, void* nrbcPointer);

uint16_t deSerializeUint16(uint16_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeUint32(uint32_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeUint64(uint64_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeEBT_Level1MovementAuthority(EBT_Level1MovementAuthority* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeEBT_LevelTransitionOrder(EBT_LevelTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeEBT_RBCTransitionOrder(EBT_RBCTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_TrainRunningNumber(GSMR_TrainRunningNumber* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_PositionReportPacketTwoBaliseGroups(GSMR_PositionReportPacketTwoBaliseGroups* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_PositionReportPacket(GSMR_PositionReportPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_ValidatedTrainDataPacket(GSMR_ValidatedTrainDataPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_DataOutsideErtmsPacket(GSMR_DataOutsideErtmsPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_Level2_3MovementAuthorityPacket(GSMR_Level2_3MovementAuthorityPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_GradientProfilePacket(GSMR_GradientProfilePacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_IntStatSpeedProfile(GSMR_IntStatSpeedProfile* dataPointer, uint8_t* buffer, uint16_t counter);



#endif
	
