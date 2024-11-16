#ifndef NRBC_MESSAGE_H
	#define	NRBC_MESSAGE_H
	
	#include "EBT_packet.h"
	#include "GSM_R_packet.h"

	///NRBC_preAnnouncement: The Handing Over RBC informs the Accepting RBC that a given train is approaching its area at a specific border location.
	/**Taille: 30-181<BR>
		\todo q_masterengine existe si m_mode = 11
		\todo nid_leadingEngine existe si m_mode = 11 et q_masterengine = 1
		\todo packetNb11 existe si m_mode != 11 
		Peut contenir les paquets optionnels:<BR>
		- GSMR_TrainRunningNumber (numero de circulation du train)
		- on-board supported system versions (non implemente)
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 201
		uint16_t l_message;
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;			///< = 1
		uint8_t m_mode;			///< Only 0, 1, 2, 7, 8, 11 or 12
		uint8_t q_masterengine;
		uint32_t nid_leadingEngine;
		GSMR_ValidatedTrainDataPacket packetNb11;
		GSMR_TrainRunningNumber trainNumber;
	} NRBC_preAnnouncement;
	
	///NRBC_RRI_request: The Handing Over RBC requests route related information from the Accepting RBC.
	/**Taille: 25-41<BR>
		\todo n_remainlinkedbg jusqu'a q_remaincurrent existent si q_addrestrictions = 1
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 202
		uint16_t l_message;
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;
		uint16_t d_remaindistance;
		uint8_t n_remaineoaintervals;
		uint8_t n_remaintsr;
		uint8_t q_addrestrictions;
		uint8_t n_remainlinkedbg;
		uint8_t n_remaingradientchange;
		uint8_t n_remainmasection;
		uint8_t n_remainspeedchange;
		uint8_t n_remaintrackcondition;
		uint8_t n_remainasp;
		uint8_t n_remainmodeprofile;
		uint8_t n_remainlx;
		uint8_t n_remainplatform;
		uint8_t n_remainpbd;
		uint8_t q_remainaxleload;
		uint8_t q_remainloadinggauge;
		uint8_t q_remaintraction;
		uint8_t q_remainleveltransition;
		uint8_t q_remaintractionsystemchange;
		uint8_t q_remaincurrent;
	} NRBC_RRI_request;
	
	///NRBC_announcement: The Handing Over RBC informs the Accepting RBC that the maximum safe front end of the train has passed the location corresponding to the border.
	/**Taille: 20<BR>
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 203
		uint16_t l_message;			///< = 20
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;
	} NRBC_announcement;
	
	///NRBC_RRI_confirmation: The Handing Over RBC confirms that the RRI has been processed according to the information in this RRI Confirmation message.
	/**Taille: 25<BR>
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 206
		uint16_t l_message;			///< = 25
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;
		uint32_t t_rbcconf;
		uint8_t q_rriconfstatus;
	} NRBC_RRI_confirmation;
	
	///NRBC_TrainData: The Handing Over RBC informs the Accepting RBC about train data received from an ETCS on-board equipment.
	/**Taille: 36-164<BR>
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 207
		uint16_t l_message;
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;			///< = 1
		GSMR_ValidatedTrainDataPacket packetNb11;
	} NRBC_TrainData;
	
	///NRBC_TrainRunningNumber: The Handing Over RBC informs the Accepting RBC about train running number of an engine being handed over.
	/**Taille: 27<BR>
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 208
		uint16_t l_message;			///< = 27
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;
		GSMR_TrainRunningNumber trainNumber;
	} NRBC_TrainRunningNumber;
	
	///NRBC_RRI: Route information from the Accepting RBC to the Handing Over RBC.
	/**Taille: 76-3757<BR>
		\todo q_tdchange existe si q_rrimachange = 0
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 221
		uint16_t l_message;
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;
		uint8_t q_rrimachange;
		uint8_t q_tdchange;
		uint8_t q_matimer;
		GSMR_Level2_3MovementAuthorityPacket packetnb15;
		GSMR_GradientProfilePacket packetnb21;
		GSMR_IntStatSpeedProfile packetnb27;
	} NRBC_RRI;
	
	///NRBC_TakingOverResponsibility: The Accepting RBC informs the Handing Over RBC that it has taken over the responsibility.
	/**Taille: 20<BR>
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 222
		uint16_t l_message;			///< = 20
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;				///< = 0
	} NRBC_TakingOverResponsibility;
	
	///NRBC_RequestRRIConfirmation: Request for confirmation including request for shortening of MA, from the Accepting RBC to the Handing Over RBC.
	/**Taille: 56-280<BR>
		\todo Packet 80 (optionnel)
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 221
		uint16_t l_message;
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;				///< = 1
		uint8_t q_rrimachange;
		uint8_t q_tdchange;
		uint8_t q_matimer;
		GSMR_Level2_3MovementAuthorityPacket packetnb15;
	} NRBC_RequestRRIConfirmation;
	
	///NRBC_ACK: The RBC acknowledges a received message according to M_ACK. The meaning of the acknowledgement from its sender point of view is: the acknowledged message is consistent.
	/**Taille: 24<BR>
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 205
		uint16_t l_message;			///< = 24
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;				///< = 0
		uint32_t t_rbcack;
	} NRBC_ACK;
	
	///NRBC_Cancellation: When an RBC detects that the transition to or from a neighbour RBC is to be cancelled, it sends this information.
	/**Taille: 20<BR>
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 204
		uint16_t l_message;			///< = 20
		uint16_t nid_cRBC;
		uint16_t nid_rbc;
		uint32_t nid_engine;
		uint16_t nid_cBG;
		uint16_t nid_bg;
		uint32_t t_rbc;
		uint8_t m_ack;
	} NRBC_Cancellation;
	
	///NRBC_LifeSign: This message is sent if a specified time has passed since any message was sent.
	/**Taille: 11<BR>
	*/
	typedef struct 
	{
		uint8_t nid_nrbcmessage;	///< = 223
		uint16_t l_message;			///< = 11
		uint16_t nid_c;
		uint16_t nid_rbc;
		uint32_t t_rbc;
	} NRBC_LifeSign;
	
#endif