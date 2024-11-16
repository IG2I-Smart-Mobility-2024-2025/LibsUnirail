#include "ertms.h"


	/*--------------------------------------Packets--------------------------------------*/

void initEBT_LevelTransitionOrder(EBT_LevelTransitionOrder* pointer, uint8_t q_scale, uint16_t d_leveltr,
	uint8_t m_leveltr, uint8_t nid_ntc, uint16_t l_ackleveltr, uint8_t n_iter_next, uint8_t m_leveltr_next[8], 
	uint8_t nid_ntc_next[8], uint16_t l_ackleveltr_next[8])
{
	int i = 0;
	pointer->nid_packet = 41;
	pointer->q_dir = 1;	//Nominal (Balise->train)
	pointer->l_packet = 12 + (4 * n_iter_next);
	pointer->q_scale = q_scale;
	pointer->d_leveltr = d_leveltr;
	pointer->m_leveltr = m_leveltr;
	pointer->nid_ntc = nid_ntc;
	pointer->l_ackleveltr = l_ackleveltr;
	pointer->n_iter_next = n_iter_next;
	for (i = 0; i<n_iter_next; i++)
	{
		pointer->m_leveltr_next[i] = m_leveltr_next[i];
		pointer->nid_ntc_next[i] = nid_ntc_next[i];
		pointer->l_ackleveltr_next[i] = l_ackleveltr_next[i];
	}
}

void initEBT_Level1MovementAuthority(EBT_Level1MovementAuthority* pointer, uint8_t q_scale, uint8_t v_main, uint8_t v_ema, uint16_t t_ema,
	uint8_t n_iter_sections, GSMR_SectionDescription section[32], GSMR_SectionDescription endsection, ERTMS_SectionTimer end,
	uint8_t q_dangerpoint, uint16_t d_dp, uint8_t v_releasedp, ERTMS_SectionTimer overlap, uint16_t d_startol, uint8_t v_releaseol)
{
	int i = 0;
	pointer->nid_packet = 12;
	pointer->q_dir = 1;	//Nominal (Balise->train)
	pointer->l_packet = 34 + (7 * n_iter_sections);
	pointer->q_scale = q_scale;
	pointer->v_main = v_main;
	pointer->v_ema = v_ema;
	pointer->t_ema = t_ema;
	pointer->n_iter_sections = n_iter_sections;
	for (i = 0; i<n_iter_sections; i++)
	{
		pointer->section[i] = section[i];
	}
	pointer->endsection = endsection;
	pointer->end = end;
	pointer->q_dangerpoint = q_dangerpoint;
	pointer->d_dp = d_dp;
	pointer->v_releasedp = v_releasedp;
	pointer->overlap = overlap;
	pointer->d_startol = d_startol;
	pointer->v_releaseol = v_releaseol;
}

void initEBT_RBCTransitionOrder(EBT_RBCTransitionOrder* pointer, uint8_t q_scale, uint16_t d_rbctr, uint16_t nid_c,
	uint16_t nid_rbc, uint64_t nid_radio, uint8_t q_sleepsession)
{
	pointer->nid_packet = 131;
	pointer->q_dir = 1;	//Nominal (Balise->train)
	pointer->l_packet = 20;
	pointer->q_scale = q_scale;
	pointer->d_rbctr = d_rbctr;
	pointer->nid_c = nid_c;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_radio = nid_radio;
	pointer->q_sleepsession = q_sleepsession;
}

void initGSMR_TrainRunningNumber(GSMR_TrainRunningNumber* pointer, uint32_t nid_operational)
{
	pointer->nid_packet = 5;
	pointer->l_packet = 7;
	pointer->nid_operational = nid_operational;
}

void initGSMR_PositionReportPacket(GSMR_PositionReportPacket* pointer, uint8_t q_scale, GSMR_nid_lrbg nid_lrbg, int16_t d_lrbg,
	uint8_t q_dirlrbg, uint8_t q_dlrbg, uint16_t l_doubtover, uint16_t l_doubtunder, uint8_t q_length, uint16_t l_traininit,
	uint8_t v_train, uint8_t q_dirtrain, uint8_t m_mode, uint8_t m_level, uint8_t nid_ntc)
{
	pointer->nid_packet = 0;
	pointer->l_packet = 24;
	pointer->q_scale = q_scale;
	pointer->nid_lrbg = nid_lrbg;
	pointer->d_lrbg = d_lrbg;
	pointer->q_dirlrbg = q_dirlrbg;
	pointer->q_dlrbg = q_dlrbg;
	pointer->l_doubtover = l_doubtover;
	pointer->l_doubtunder = l_doubtunder;
	pointer->q_length = q_length;
	pointer->l_traininit = l_traininit;
	pointer->v_train = v_train;
	pointer->q_dirtrain = q_dirtrain;
	pointer->m_mode = m_mode;
	pointer->m_level = m_level;
	pointer->nid_ntc = nid_ntc;
}

void initGSMR_PositionReportPacketTwoBaliseGroups(GSMR_PositionReportPacketTwoBaliseGroups* pointer, uint8_t q_scale, GSMR_nid_lrbg nid_lrbg, 
	GSMR_nid_lrbg nid_prvlrbg, uint16_t d_lrbg, uint8_t q_dirlrbg, uint8_t q_dlrbg, uint16_t l_doubtover, uint16_t l_doubtunder,
	uint8_t q_length, uint16_t l_traininit, uint8_t v_train, uint8_t q_dirtrain, uint8_t m_mode, uint8_t m_level, uint8_t nid_ntc)
{
	pointer->nid_packet = 1;
	pointer->l_packet = 28;
	pointer->q_scale = q_scale;
	pointer->nid_lrbg = nid_lrbg;
	pointer->nid_prvlrbg = nid_prvlrbg;
	pointer->d_lrbg = d_lrbg;
	pointer->q_dirlrbg = q_dirlrbg;
	pointer->q_dlrbg = q_dlrbg;
	pointer->l_doubtover = l_doubtover;
	pointer->l_doubtunder = l_doubtunder;
	pointer->q_length = q_length;
	pointer->l_traininit = l_traininit;
	pointer->v_train = v_train;
	pointer->q_dirtrain = q_dirtrain;
	pointer->m_mode = m_mode;
	pointer->m_level = m_level;
	pointer->nid_ntc = nid_ntc;
}

void initGSMR_ValidatedTrainDataPacket(GSMR_ValidatedTrainDataPacket* pointer, uint8_t nc_cdtrain, uint16_t nc_train, 
	uint16_t l_train, uint8_t v_maxtrain, uint8_t m_loadinggauge, uint8_t m_axleloadcat, uint8_t m_airtight, uint16_t n_axle,
	uint8_t n_iter_engine, GSMR_engine_identifier engine_identifier[32], uint8_t n_iter_ntc, uint8_t nid_ntc[32])
{
	int i = 0;
	pointer->nid_packet = 11;
	pointer->l_packet = 16 + (3*n_iter_engine) + n_iter_ntc;
	pointer->nc_cdtrain = nc_cdtrain;
	pointer->nc_train = nc_train;
	pointer->l_train = l_train;
	pointer->v_maxtrain = v_maxtrain;
	pointer->m_loadinggauge = m_loadinggauge;
	pointer->m_axleloadcat = m_axleloadcat;
	pointer->m_airtight = m_airtight;
	pointer->n_axle = n_axle;
	pointer->n_iter_engine = n_iter_engine;
	for (i = 0; i<n_iter_engine; i++)
	{
		pointer->engine_identifier[i] = engine_identifier[i];
	}
	pointer->n_iter_ntc = n_iter_ntc;
	for (i = 0; i<n_iter_ntc; i++)
	{
		pointer->nid_ntc[i] = nid_ntc[i];
	}
}

void initGSMR_DataOutsideErtmsPacket(GSMR_DataOutsideErtmsPacket* pointer, uint8_t q_dir, uint16_t nid_xuser, uint8_t nid_ntc,
	uint8_t n_iter_stops, GSMR_ItineraryDescription stops[32])
{
	int i = 0;
	pointer->nid_packet = 44;
	pointer->q_dir = q_dir;
	pointer->nid_xuser = nid_xuser;
	pointer->nid_ntc = nid_ntc;
	pointer->n_iter_stops = n_iter_stops;
	pointer->l_packet = 6;
	switch ( nid_xuser )
	{
		case 102:	//nid_ntc
			pointer->l_packet +=1;
			break;
		case 204:	//n_iter_stops et stops
			pointer->l_packet += 1 + (n_iter_stops* 8);
			for (i = 0; i<n_iter_stops; i++)
			{
				pointer->stops[i] = stops[i];
			}
			break;
		default:
			break;
	}
}

void initGSMR_Level2_3MovementAuthorityPacket(GSMR_Level2_3MovementAuthorityPacket* pointer, uint8_t q_dir,	uint8_t q_scale,
	uint8_t v_ema, uint16_t t_ema, uint8_t n_iter_section, GSMR_SectionDescription section[32], GSMR_SectionDescription endsection,
	ERTMS_SectionTimer end, uint8_t q_dangerpoint, uint16_t d_dp, uint8_t v_releasedp, ERTMS_SectionTimer overlap, uint16_t d_startol,
	uint8_t v_releaseol)
{
	int i = 0;
	pointer->nid_packet = 15;
	pointer->l_packet = 33 + (7*n_iter_section);
	pointer->q_dir = q_dir;
	pointer->q_scale = q_scale;
	pointer->v_ema = v_ema;
	pointer->t_ema = t_ema;
	pointer->n_iter_section = n_iter_section;
	for (i = 0; i<n_iter_section; i++)
	{
		pointer->section[i] = section[i];
	}
	pointer->endsection = endsection;
	pointer->end = end;
	pointer->q_dangerpoint = q_dangerpoint;
	pointer->d_dp = d_dp;
	pointer->v_releasedp = v_releasedp;
	pointer->overlap = overlap;
	pointer->d_startol = d_startol;
	pointer->v_releaseol = v_releaseol;
}

void initGSMR_GradientProfilePacket(GSMR_GradientProfilePacket* pointer, uint8_t q_dir,	uint8_t q_scale, uint16_t d_gradient_first,
	uint8_t q_gdir_first, uint8_t g_a_first, uint8_t n_iter, uint16_t d_gradient[32], uint8_t q_gdir[32], uint8_t g_a[32])
{
	int i = 0;
	pointer->nid_packet = 21;
	pointer->l_packet = 10 + (4*n_iter);
	pointer->q_dir = q_dir;
	pointer->q_scale = q_scale;
	pointer->d_gradient_first = d_gradient_first;
	pointer->q_gdir_first = q_gdir_first;
	pointer->g_a_first = g_a_first;
	pointer->n_iter = n_iter;
	for (i = 0; i<n_iter; i++)
	{
		pointer->d_gradient[i] = d_gradient[i];
		pointer->q_gdir[i] = q_gdir[i];
		pointer->g_a[i] = g_a[i];
	}
}

void initGSMR_IntStatSpeedProfile(GSMR_IntStatSpeedProfile* pointer, uint8_t q_dir, uint8_t q_scale, uint16_t d_staticFisrt,
	uint8_t v_staticFirst, uint8_t q_frontFirst, uint8_t n_iterDiffFirst, uint8_t q_diffFirst[32], uint8_t nc_cddiffFirst[32], uint8_t v_diffFirst[32],
	uint8_t n_iterStatic, uint16_t d_static[32], uint8_t v_static[32], uint8_t q_front[32], uint8_t n_iterDiff[32], uint8_t q_diff[32][32],
	uint8_t nc_cddiff[32][32], uint8_t v_diff[32][32])
{
	int i = 0, j = 0;
	pointer->nid_packet = 27;
	pointer->l_packet = 11 + (3*n_iterDiffFirst) + (5*n_iterStatic);		// la longueur sera mise a jour selon chaque valeur de n_iterDiff
	pointer->q_dir = q_dir;
	pointer->q_scale = q_scale;
	pointer->d_staticFisrt = d_staticFisrt;
	pointer->v_staticFirst = v_staticFirst;
	pointer->q_frontFirst = q_frontFirst;
	pointer->n_iterDiffFirst = n_iterDiffFirst;
	for (i=0;i<n_iterDiffFirst; i++)
	{
		pointer->q_diffFirst[i] =  q_diffFirst[i];
		if (q_diffFirst[i])
			pointer->nc_diffFirst[i] = nc_cddiffFirst[i];
		else
			pointer->nc_cddiffFirst[i] = nc_cddiffFirst[i];
		pointer->v_diffFirst[i] = v_diffFirst[i];
	}
	pointer->n_iterStatic = n_iterStatic;
	for (i=0;i<n_iterStatic; i++)
	{
		pointer->d_static[i] =  d_static[i];
		pointer->v_static[i] =  v_static[i];
		pointer->q_front[i] =  q_front[i];
		pointer->n_iterDiff[i] =  n_iterDiff[i];
		for (j=0;j<n_iterDiff[i]; j++)
		{
			pointer->q_diff[i][j] =  q_diff[i][j];
			if (q_diff[i][j])
				pointer->nc_diff[i][j] = nc_cddiff[i][j];
			else
				pointer->nc_cddiff[i][j] = nc_cddiff[i][j];
			pointer->l_packet += 4;
			pointer->v_diff[i][j] = v_diff[i][j];
		}
	}
}

/*--------------------------------------EBT & GSMR messages--------------------------------------*/

void initEBT(EBT_Message* pointer, uint8_t m_version, uint8_t n_pig, uint8_t n_total, uint8_t m_dup,
	uint8_t m_mcount, GSMR_nid_lrbg nid_lrbg, uint8_t q_link, void* packetPointer)
{
	pointer->q_updown = 1;
	pointer->m_version = m_version;
	pointer->q_media = 0;
	pointer->n_pig = n_pig;
	pointer->n_total = n_total;
	pointer->m_dup = m_dup;
	pointer->m_mcount = m_mcount;
	pointer->nid_lrbg = nid_lrbg;
	pointer->q_link = q_link;
	uint8_t *idPacket = packetPointer;
	EBT_Level1MovementAuthority *MApack;
	EBT_RepositioningInformation *RePos;
	EBT_LevelTransitionOrder *LvlTrans;
	EBT_RBCTransitionOrder *RbcTrans;
	switch (*idPacket)
	{
		case 12:	//EBT_Level1MovementAuthority
			MApack = packetPointer;
			pointer->packetNb12 = *MApack;
			break;
		case 16:	//EBT_RepositioningInformation
			RePos = packetPointer;
			pointer->packetNb16 = *RePos;
			break;
		case 41:	//EBT_LevelTransitionOrder
			LvlTrans = packetPointer;
			pointer->packetNb41 = *LvlTrans;
			break;
		case 131:	//EBT_RBCTransitionOrder
			RbcTrans = packetPointer;
			pointer->packetNb131 = *RbcTrans;
			break;
		default:
#ifdef DEBUG
			printf("Error: invalid packet pointer: #%d not treated\n", *idPacket);
#endif
			break;
	}
}

void initGSMR_CommunicationInitiationMessage(GSMR_CommunicationInitiationMessage* pointer, uint32_t timeStamp, uint32_t nidEngine)
{
	pointer->nid_message = 155;
	pointer->l_message = 11;
	pointer->t_train = timeStamp;
	pointer->nid_engine = nidEngine;
}
	
void initGSMR_RBCSystemVersionMessage(GSMR_RBCSystemVersionMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint8_t m_version)
{
	pointer->nid_message = 32;
	pointer->l_message = 13;
	pointer->t_train = timeStamp;
	pointer->m_ack = m_ack;
	pointer->nid_lrbg = nid_lrbg;
	pointer->m_version = m_version;
}
	
void initGSMR_SessionEstablishedMessage(GSMR_SessionEstablishedMessage* pointer, uint32_t timeStamp, uint32_t nidEngine)
{
	pointer->nid_message = 159;
	pointer->l_message = 11;
	pointer->t_train = timeStamp;
	pointer->nid_engine = nidEngine;
}
	
void initGSMR_NoCompatibleVersionSupported(GSMR_NoCompatibleVersionSupported* pointer, uint32_t timeStamp, uint32_t nidEngine)
{
	pointer->nid_message = 154;
	pointer->l_message = 11;
	pointer->t_train = timeStamp;
	pointer->nid_engine = nidEngine;
}
	
void initGSMR_SoM_PositionReport(GSMR_SoM_PositionReport* pointer, uint32_t timeStamp, uint32_t nidEngine, uint8_t q_status, void* positionPacketPointer,
	GSMR_TrainRunningNumber* trainNumber, GSMR_DataOutsideErtmsPacket* itinerary )
{
	pointer->nid_message = 157;
	pointer->l_message = 12;	//Temporaire, selon la taille du packet il sera mis a jour
	pointer->t_train = timeStamp;
	pointer->nid_engine = nidEngine;
	pointer->q_status = q_status;
	///Encapsuler...
	uint8_t *idPacket = positionPacketPointer;
	if ( *idPacket == 0)	//GSMR_PositionReportPacket
	{
		GSMR_PositionReportPacket *posRepPtr = positionPacketPointer;
		pointer->l_message += posRepPtr->l_packet;
		pointer->packetNb0 = *posRepPtr;
	}
	else if ( *idPacket == 1)	//GSMR_PositionReportPacketTwoBaliseGroups
	{
		GSMR_PositionReportPacketTwoBaliseGroups *posRepBGPtr = positionPacketPointer;
		pointer->l_message += posRepBGPtr->l_packet;
		pointer->packetNb1 = *posRepBGPtr;
	}
#ifdef DEBUG
	else
	{
		printf("Error: invalid packet pointer: #%d not treated\n", *idPacket);
	}
#endif
	if (trainNumber!= NULL)
	{
		GSMR_TrainRunningNumber *runningNumber = trainNumber;
		pointer->l_message += runningNumber->l_packet;
		pointer->trainNumber = *runningNumber;
	}
	else
		pointer->trainNumber.nid_packet = EMPTY_CONTENT;
	if (itinerary!= NULL)
	{
		GSMR_DataOutsideErtmsPacket *itninInfo = itinerary;
		pointer->l_message += itninInfo->l_packet;
		pointer->itinerary = *itninInfo;
	}
	else
		pointer->itinerary.nid_packet = EMPTY_CONTENT;
		
}
	
void initGSMR_SoMPositionConfirmed(GSMR_SoMPositionConfirmed* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg)
{
	pointer->nid_message = 43;
	pointer->l_message = 12;
	pointer->t_train = timeStamp;
	pointer->m_ack = m_ack;
	pointer->nid_lrbg = nid_lrbg;
}
	
void initGSMR_ValidatedTrainDataMessage(GSMR_ValidatedTrainDataMessage* pointer, uint32_t timeStamp, uint32_t nidEngine, void* packetPointer, GSMR_ValidatedTrainDataPacket packetNb11)
{
	pointer->nid_message = 129;
	pointer->l_message = 11;	//Temporaire, selon la taille du packet il sera mis a jour
	pointer->t_train = timeStamp;
	pointer->nid_engine = nidEngine;
	///Encapsuler...
	uint8_t *idPacket = packetPointer;
	if ( *idPacket == 0)	//GSMR_PositionReportPacket
	{
		GSMR_PositionReportPacket *posRepPtr = packetPointer;
		pointer->l_message += posRepPtr->l_packet;
		pointer->packetNb0 = *posRepPtr;
	}
	else if ( *idPacket == 1)	//GSMR_PositionReportPacketTwoBaliseGroups
	{
		GSMR_PositionReportPacketTwoBaliseGroups *posRepBGPtr = packetPointer;
		pointer->l_message += posRepBGPtr->l_packet;
		pointer->packetNb1 = *posRepBGPtr;
	}
#ifdef DEBUG
	else
	{
		printf("Error: invalid packet pointer: #%d not treated\n", *idPacket);
	}
#endif
	
	pointer->packetNb11 = packetNb11;
	pointer->l_message +=packetNb11.l_packet;
}
	
void initGSMR_ACKTrainDataMessage(GSMR_ACKTrainDataMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint32_t firstTimeStamp)
{
	pointer->nid_message = 8;
	pointer->l_message = 16;
	pointer->t_train = timeStamp;
	pointer->m_ack = m_ack;
	pointer->nid_lrbg = nid_lrbg;
	pointer->t_trainMessageOrigin = firstTimeStamp;
}
	
void initGSMR_MARequestMessage(GSMR_MARequestMessage* pointer, uint32_t timeStamp, uint32_t nidEngine, uint8_t q_marqstreason, void* packetPointer)
{
	pointer->nid_message = 132;
	pointer->l_message = 12;	//Temporaire, selon la taille du packet il sera mis a jour
	pointer->t_train = timeStamp;
	pointer->nid_engine = nidEngine;
	pointer->q_marqstreason = q_marqstreason;
	uint8_t *idPacket = packetPointer;
	if ( *idPacket == 0)	//GSMR_PositionReportPacket
	{
		GSMR_PositionReportPacket *posRepPtr = packetPointer;
		pointer->l_message += posRepPtr->l_packet;
		pointer->packetNb0 = *posRepPtr;
	}
	else if ( *idPacket == 1)	//GSMR_PositionReportPacketTwoBaliseGroups
	{
		GSMR_PositionReportPacketTwoBaliseGroups *posRepBGPtr = packetPointer;
		pointer->l_message += posRepBGPtr->l_packet;
		pointer->packetNb1 = *posRepBGPtr;
	}
#ifdef DEBUG
	else
	{
		printf("Error: invalid packet pointer: #%d not treated\n", *idPacket);
	}
#endif
}
	
void initGSMR_MovementAuthorityMessage(GSMR_MovementAuthorityMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, GSMR_Level2_3MovementAuthorityPacket packetnb15)
{
	pointer->nid_message = 3;
	pointer->l_message = 12 + packetnb15.l_packet;
	pointer->t_train = timeStamp;
	pointer->m_ack = m_ack;
	pointer->nid_lrbg = nid_lrbg;
	pointer->packetnb15 = packetnb15;
}
	
void initGSMR_SRAuthorisationMessage(GSMR_SRAuthorisationMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint8_t q_scale, uint16_t d_sr)
{
	pointer->nid_message = 2;
	pointer->l_message = 15;
	pointer->t_train = timeStamp;
	pointer->m_ack = m_ack;
	pointer->nid_lrbg = nid_lrbg;
	pointer->q_scale = q_scale;
	pointer->d_sr = d_sr;
}
	
void initGSMR_Acknowledgment(GSMR_Acknowledgment* pointer, uint32_t timeStamp, uint32_t nidEngine, uint32_t firstTimeStamp)
{
	pointer->nid_message = 146;
	pointer->l_message = 15;
	pointer->t_train = timeStamp;
	pointer->nid_engine = nidEngine;
	pointer->t_trainMessageOrigin = firstTimeStamp;
}

void initGSMR_EndOfMission(GSMR_EndOfMission* pointer, uint32_t timeStamp, uint32_t nidEngine, void* packetPointer)
{
	pointer->nid_message = 150;
	pointer->l_message = 11;
	pointer->t_train = timeStamp;
	pointer->nid_engine = nidEngine;
	uint8_t *idPacket = packetPointer;
	if ( *idPacket == 0)	//GSMR_PositionReportPacket
	{
		GSMR_PositionReportPacket *posRepPtr = packetPointer;
		pointer->l_message += posRepPtr->l_packet;
		pointer->packetNb0 = *posRepPtr;
	}
	else if ( *idPacket == 1)	//GSMR_PositionReportPacketTwoBaliseGroups
	{
		GSMR_PositionReportPacketTwoBaliseGroups *posRepBGPtr = packetPointer;
		pointer->l_message += posRepBGPtr->l_packet;
		pointer->packetNb1 = *posRepBGPtr;
	}
#ifdef DEBUG
	else
	{
		printf("Error: invalid packet pointer: #%d not treated\n", *idPacket);
	}
#endif
}
	
void initGSMR_AckTerminationCommunicationSession(GSMR_AckTerminationCommunicationSession* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg)
{
	pointer->nid_message = 39;
	pointer->l_message = 12;
	pointer->t_train = timeStamp;
	pointer->m_ack = m_ack;
	pointer->nid_lrbg = nid_lrbg;
}
	/*--------------------------------------NRBC--------------------------------------*/
	
void initNRBC_preAnnouncement(NRBC_preAnnouncement* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg,
	uint32_t timeStamp, uint8_t m_mode, uint8_t q_masterengine, uint32_t nidLeadingEngine, GSMR_ValidatedTrainDataPacket packetNb11, GSMR_TrainRunningNumber* trainNumber)
{
	pointer->nid_nrbcmessage = 201;
	pointer->l_message = 26+packetNb11.l_packet;	//Temporaire, selon la taille du packet il sera mis a jour
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack = 1;
	pointer->m_mode = m_mode;
	pointer->q_masterengine = q_masterengine;
	pointer->nid_leadingEngine = nidLeadingEngine;
	pointer->packetNb11 = packetNb11;
	
	if (trainNumber!= NULL)
	{
		GSMR_TrainRunningNumber *runningNumber = trainNumber;
		pointer->l_message += runningNumber->l_packet;
		pointer->trainNumber = *runningNumber;
	}
	else
		pointer->trainNumber.nid_packet = EMPTY_CONTENT;
}

void initNRBC_RRI_request(NRBC_RRI_request* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack,
	uint16_t d_remaindistance, uint8_t n_remaineoaintervals, uint8_t n_remaintsr, uint8_t q_addrestrictions, uint8_t n_remainlinkedbg, uint8_t n_remaingradientchange, uint8_t n_remainmasection,
	uint8_t n_remainspeedchange, uint8_t n_remaintrackcondition, uint8_t n_remainasp, uint8_t n_remainmodeprofile, uint8_t n_remainlx, uint8_t n_remainplatform, uint8_t n_remainpbd,
	uint8_t q_remainaxleload, uint8_t q_remainloadinggauge, uint8_t q_remaintraction, uint8_t q_remainleveltransition, uint8_t q_remaintractionsystemchange, uint8_t q_remaincurrent)
{
	pointer->nid_nrbcmessage = 202;
	pointer->l_message = 41;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack = m_ack;
	pointer->d_remaindistance = d_remaindistance;
	pointer->n_remaineoaintervals = n_remaineoaintervals;
	pointer->n_remaintsr = n_remaintsr;
	pointer->q_addrestrictions = q_addrestrictions;
	pointer->n_remainlinkedbg = n_remainlinkedbg;
	pointer->n_remaingradientchange = n_remaingradientchange;
	pointer->n_remainmasection = n_remainmasection;
	pointer->n_remainspeedchange = n_remainspeedchange;
	pointer->n_remaintrackcondition = n_remaintrackcondition;
	pointer->n_remainasp = n_remainasp;
	pointer->n_remainmodeprofile = n_remainmodeprofile;
	pointer->n_remainlx = n_remainlx;
	pointer->n_remainplatform = n_remainplatform;
	pointer->n_remainpbd = n_remainpbd;
	pointer->q_remainaxleload = q_remainaxleload;
	pointer->q_remainloadinggauge = q_remainloadinggauge;
	pointer->q_remaintraction = q_remaintraction;
	pointer->q_remainleveltransition = q_remainleveltransition;
	pointer->q_remaintractionsystemchange = q_remaintractionsystemchange;
	pointer->q_remaincurrent = q_remaincurrent;
}

void initNRBC_announcement(NRBC_announcement* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack)
{
	pointer->nid_nrbcmessage = 203;
	pointer->l_message = 20;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack = m_ack;
}

void initNRBC_RRI_confirmation(NRBC_RRI_confirmation* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack, 
	uint32_t t_rbcconf, uint8_t q_rriconfstatus)
{
	pointer->nid_nrbcmessage = 206;
	pointer->l_message = 25;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack = m_ack;
	pointer->t_rbcconf = t_rbcconf;
	pointer->q_rriconfstatus = q_rriconfstatus;
}

void initNRBC_TrainData(NRBC_TrainData* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack, 
	GSMR_ValidatedTrainDataPacket trainData)
{
	pointer->nid_nrbcmessage = 207;
	pointer->l_message = 20+trainData.l_packet;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack = m_ack;
	pointer->packetNb11 = trainData;
}

void initNRBC_TrainRunningNumber(NRBC_TrainRunningNumber* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack, 
	GSMR_TrainRunningNumber trainNumber)
{
	pointer->nid_nrbcmessage = 207;
	pointer->l_message = 20+trainNumber.l_packet;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack = m_ack;
	pointer->trainNumber = trainNumber;
}

void initNRBC_RRI(NRBC_RRI* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack, uint8_t rrimachange, 
	uint8_t tdchange, uint8_t matimer, GSMR_Level2_3MovementAuthorityPacket MA, GSMR_GradientProfilePacket gradient, GSMR_IntStatSpeedProfile SSP)
{
	pointer->nid_nrbcmessage = 221;
	pointer->l_message = 23 + MA.l_packet + gradient.l_packet + SSP.l_packet;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack = m_ack;
	pointer->q_rrimachange = rrimachange;
	pointer->q_tdchange = tdchange;
	pointer->q_matimer = matimer;
	pointer->packetnb15 = MA;
	pointer->packetnb21 = gradient;
	pointer->packetnb27 = SSP;
}

void initNRBC_TakingOverResponsibility(NRBC_TakingOverResponsibility* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack)
{
	pointer->nid_nrbcmessage = 222;
	pointer->l_message = 20;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack = m_ack;
}

void initNRBC_RequestRRIConfirmation(NRBC_RequestRRIConfirmation* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t q_rrimachange,
	uint8_t q_tdchange, uint8_t q_matimer, GSMR_Level2_3MovementAuthorityPacket MA)
{
	pointer->nid_nrbcmessage = 222;
	pointer->l_message = 23 + MA.l_packet;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack =1;
	pointer->q_rrimachange = q_rrimachange;
	pointer->q_tdchange = q_tdchange;
	pointer->q_matimer = q_matimer;
	pointer->packetnb15 = MA;
}

void initNRBC_ACK(NRBC_ACK* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint32_t origTimeStamp)
{
	pointer->nid_nrbcmessage = 205;
	pointer->l_message = 24;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack =0;
	pointer->t_rbcack = origTimeStamp;
}

void initNRBC_Cancellation(NRBC_Cancellation* pointer, uint16_t nid_cRBC, uint16_t nid_rbc, uint32_t nidEngine, uint16_t nid_cBG, uint16_t nid_bg, uint32_t timeStamp, uint8_t m_ack)
{
	pointer->nid_nrbcmessage = 204;
	pointer->l_message = 20;
	pointer->nid_cRBC = nid_cRBC;
	pointer->nid_rbc = nid_rbc;
	pointer->nid_engine = nidEngine;
	pointer->nid_cBG = nid_cBG;
	pointer->nid_bg = nid_bg;
	pointer->t_rbc = timeStamp;
	pointer->m_ack =m_ack;
}

void initNRBC_LifeSign(NRBC_LifeSign* pointer, uint16_t nid_c, uint16_t nid_rbc, uint32_t timeStamp)
{
	pointer->nid_nrbcmessage = 223;
	pointer->l_message = 11;
	pointer->nid_c = nid_c;
	pointer->nid_rbc = nid_rbc;
	pointer->t_rbc = timeStamp;
}


/*----------------------------Serialize----------------------------*/

uint16_t serializeUint16(uint16_t* dataPointer, uint8_t* buffer, uint16_t counter)
{
	buffer[counter++] = (*dataPointer>>8)&0xFF;
	buffer[counter++] = *dataPointer&0xFF;
	return counter;
}
	
uint16_t serializeUint32(uint32_t* dataPointer, uint8_t* buffer, uint16_t counter)
{
	buffer[counter++] = *dataPointer>>24;
	buffer[counter++] = (*dataPointer>>16)&0xFF;
	buffer[counter++] = (*dataPointer>>8)&0xFF;
	buffer[counter++] = *dataPointer&0xFF;
	return counter;
}
	
uint16_t serializeUint64(uint64_t* dataPointer, uint8_t* buffer, uint16_t counter)
{
	buffer[counter++] = *dataPointer>>56;
	buffer[counter++] = (*dataPointer>>48)&0xFF;
	buffer[counter++] = (*dataPointer>>40)&0xFF;
	buffer[counter++] = (*dataPointer>>32)&0xFF;
	buffer[counter++] = (*dataPointer>>24)&0xFF;
	buffer[counter++] = (*dataPointer>>16)&0xFF;
	buffer[counter++] = (*dataPointer>>8)&0xFF;
	buffer[counter++] = *dataPointer&0xFF;
	return counter;
}
	
uint16_t serializeEBT_Level1MovementAuthority(EBT_Level1MovementAuthority* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	buffer[counter++] = dataPointer->nid_packet;
	buffer[counter++] = dataPointer->q_dir;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->q_scale;
	buffer[counter++] = dataPointer->v_main;
	buffer[counter++] = dataPointer->v_ema;
	counter = serializeUint16(&dataPointer->t_ema, buffer, counter);
	buffer[counter++] = dataPointer->n_iter_sections;
	for (i = 0; i<dataPointer->n_iter_sections; i++)
	{
		counter = serializeUint16(&dataPointer->section[i].l_section, buffer, counter);
		buffer[counter++] = dataPointer->section[i].section.q_timer;
		counter = serializeUint16(&dataPointer->section[i].section.t_section, buffer, counter);
		counter = serializeUint16(&dataPointer->section[i].section.d_section, buffer, counter);
	}
	counter = serializeUint16(&dataPointer->endsection.l_section, buffer, counter);
	buffer[counter++] = dataPointer->endsection.section.q_timer;
	counter = serializeUint16(&dataPointer->endsection.section.t_section, buffer, counter);
	counter = serializeUint16(&dataPointer->endsection.section.d_section, buffer, counter);
	buffer[counter++] = dataPointer->end.q_timer;
	counter = serializeUint16(&dataPointer->end.t_section, buffer, counter);
	counter = serializeUint16(&dataPointer->end.d_section, buffer, counter);
	buffer[counter++] = dataPointer->q_dangerpoint;
	counter = serializeUint16(&dataPointer->d_dp, buffer, counter);
	buffer[counter++] = dataPointer->v_releasedp;
	buffer[counter++] = dataPointer->overlap.q_timer;
	counter = serializeUint16(&dataPointer->d_startol, buffer, counter);
	counter = serializeUint16(&dataPointer->overlap.t_section, buffer, counter);
	counter = serializeUint16(&dataPointer->overlap.d_section, buffer, counter);
	buffer[counter++] = dataPointer->v_releaseol;

	return counter;
}
	
uint16_t serializeEBT_LevelTransitionOrder(EBT_LevelTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	buffer[counter++] = dataPointer->nid_packet;
	buffer[counter++] = dataPointer->q_dir;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->q_scale;
	counter = serializeUint16(&dataPointer->d_leveltr, buffer, counter);
	buffer[counter++] = dataPointer->m_leveltr;
	buffer[counter++] = dataPointer->nid_ntc;
	counter = serializeUint16(&dataPointer->l_ackleveltr, buffer, counter);
	buffer[counter++] = dataPointer->n_iter_next;
	for (i = 0; i<dataPointer->n_iter_next; i++)
	{
		buffer[counter++] = dataPointer->m_leveltr_next[i];
		buffer[counter++] = dataPointer->nid_ntc_next[i];
		counter = serializeUint16(&dataPointer->l_ackleveltr_next[i], buffer, counter);
	}

	return counter;
}
	
uint16_t serializeEBT_RBCTransitionOrder(EBT_RBCTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter)
{
	buffer[counter++] = dataPointer->nid_packet;
	buffer[counter++] = dataPointer->q_dir;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->q_scale;
	counter = serializeUint16(&dataPointer->d_rbctr, buffer, counter);
	counter = serializeUint16(&dataPointer->nid_c, buffer, counter);
	counter = serializeUint16(&dataPointer->nid_rbc, buffer, counter);
	counter = serializeUint64(&dataPointer->nid_radio, buffer, counter);
	buffer[counter++] = dataPointer->q_sleepsession;

	return counter;
}
	
uint16_t serializeGSMR_TrainRunningNumber(GSMR_TrainRunningNumber* dataPointer, uint8_t* buffer, uint16_t counter)
{
	buffer[counter++] = dataPointer->nid_packet;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	counter = serializeUint32(&dataPointer->nid_operational, buffer, counter);

	return counter;
}
	
uint16_t serializeGSMR_PositionReportPacketTwoBaliseGroups(GSMR_PositionReportPacketTwoBaliseGroups* dataPointer, uint8_t* buffer, uint16_t counter)
{
	buffer[counter++] = dataPointer->nid_packet;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->q_scale;
	counter = serializeUint16(&dataPointer->nid_lrbg.nid_c, buffer, counter);
	counter = serializeUint16(&dataPointer->nid_lrbg.nid_bg, buffer, counter);
	counter = serializeUint16(&dataPointer->nid_prvlrbg.nid_c, buffer, counter);
	counter = serializeUint16(&dataPointer->nid_prvlrbg.nid_bg, buffer, counter);
	counter = serializeUint16(&dataPointer->d_lrbg, buffer, counter);
	buffer[counter++] = dataPointer->q_dirlrbg;
	buffer[counter++] = dataPointer->q_dlrbg;
	counter = serializeUint16(&dataPointer->l_doubtover, buffer, counter);
	counter = serializeUint16(&dataPointer->l_doubtunder, buffer, counter);
	buffer[counter++] = dataPointer->q_length;
	counter = serializeUint16(&dataPointer->l_traininit, buffer, counter);
	buffer[counter++] = dataPointer->v_train;
	buffer[counter++] = dataPointer->q_dirtrain;
	buffer[counter++] = dataPointer->m_mode;
	buffer[counter++] = dataPointer->m_level;
	buffer[counter++] = dataPointer->nid_ntc;

	return counter;
}
	
uint16_t serializeGSMR_PositionReportPacket(GSMR_PositionReportPacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	buffer[counter++] = dataPointer->nid_packet;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->q_scale;
	counter = serializeUint16(&dataPointer->nid_lrbg.nid_c, buffer, counter);
	counter = serializeUint16(&dataPointer->nid_lrbg.nid_bg, buffer, counter);
	counter = serializeUint16(&dataPointer->d_lrbg, buffer, counter);
	buffer[counter++] = dataPointer->q_dirlrbg;
	buffer[counter++] = dataPointer->q_dlrbg;
	counter = serializeUint16(&dataPointer->l_doubtover, buffer, counter);
	counter = serializeUint16(&dataPointer->l_doubtunder, buffer, counter);
	buffer[counter++] = dataPointer->q_length;
	counter = serializeUint16(&dataPointer->l_traininit, buffer, counter);
	buffer[counter++] = dataPointer->v_train;
	buffer[counter++] = dataPointer->q_dirtrain;
	buffer[counter++] = dataPointer->m_mode;
	buffer[counter++] = dataPointer->m_level;
	buffer[counter++] = dataPointer->nid_ntc;

	return counter;
}

uint16_t serializeGSMR_ValidatedTrainDataPacket(GSMR_ValidatedTrainDataPacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	buffer[counter++] = dataPointer->nid_packet;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->nc_cdtrain;
	counter = serializeUint16(&dataPointer->nc_train, buffer, counter);
	counter = serializeUint16(&dataPointer->l_train, buffer, counter);
	buffer[counter++] = dataPointer->v_maxtrain;
	buffer[counter++] = dataPointer->m_loadinggauge;
	buffer[counter++] = dataPointer->m_axleloadcat;
	buffer[counter++] = dataPointer->m_airtight;
	counter = serializeUint16(&dataPointer->n_axle, buffer, counter);
	buffer[counter++] = dataPointer->n_iter_engine;
	for (i = 0; i<dataPointer->n_iter_engine; i++)
	{
		buffer[counter++] = dataPointer->engine_identifier[i].m_voltage;
		counter = serializeUint16(&dataPointer->engine_identifier[i].nid_ctraction, buffer, counter);
	}
	buffer[counter++] = dataPointer->n_iter_ntc;
	for (i = 0; i<dataPointer->n_iter_ntc; i++)
	{
		buffer[counter++] = dataPointer->nid_ntc[i];
	}
		
	return counter;
}

uint16_t serializeGSMR_DataOutsideErtmsPacket(GSMR_DataOutsideErtmsPacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	buffer[counter++] = dataPointer->nid_packet;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->q_dir;
	counter = serializeUint16(&dataPointer->nid_xuser, buffer, counter);
	switch ( dataPointer->nid_xuser )
	{
		case 102:	//nid_ntc
			buffer[counter++] = dataPointer->nid_ntc;
			break;
		case 204:	//n_iter_stops et stops
			buffer[counter++] = dataPointer->n_iter_stops;
			for (i = 0; i<dataPointer->n_iter_stops; i++)
			{
				counter = serializeUint32(&dataPointer->stops[i].t_train, buffer, counter);
				counter = serializeUint16(&dataPointer->stops[i].nid_rbg.nid_c, buffer, counter);
				counter = serializeUint16(&dataPointer->stops[i].nid_rbg.nid_bg, buffer, counter);
			}
			break;
		default:
#ifdef DEBUG
			printf("nid_xuser=%d value unknown\n", dataPointer->nid_xuser);
#endif
		break;
	}
	return counter;
}

uint16_t serializeGSMR_Level2_3MovementAuthorityPacket(GSMR_Level2_3MovementAuthorityPacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	buffer[counter++] = dataPointer->nid_packet;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->q_dir;
	buffer[counter++] = dataPointer->q_scale;
	buffer[counter++] = dataPointer->v_ema;
	counter = serializeUint16(&dataPointer->t_ema, buffer, counter);
	buffer[counter++] = dataPointer->n_iter_section;
	for (i = 0; i<dataPointer->n_iter_section; i++)
	{
		counter = serializeUint16(&dataPointer->section[i].l_section, buffer, counter);
		buffer[counter++] = dataPointer->section[i].section.q_timer;
		counter = serializeUint16(&dataPointer->section[i].section.t_section, buffer, counter);
		counter = serializeUint16(&dataPointer->section[i].section.d_section, buffer, counter);
	}
	counter = serializeUint16(&dataPointer->endsection.l_section, buffer, counter);
	buffer[counter++] = dataPointer->endsection.section.q_timer;
	counter = serializeUint16(&dataPointer->endsection.section.t_section, buffer, counter);
	counter = serializeUint16(&dataPointer->endsection.section.d_section, buffer, counter);
	buffer[counter++] = dataPointer->end.q_timer;
	counter = serializeUint16(&dataPointer->end.t_section, buffer, counter);
	counter = serializeUint16(&dataPointer->end.d_section, buffer, counter);
	buffer[counter++] = dataPointer->q_dangerpoint;
	counter = serializeUint16(&dataPointer->d_dp, buffer, counter);
	buffer[counter++] = dataPointer->v_releasedp;
	buffer[counter++] = dataPointer->overlap.q_timer;
	counter = serializeUint16(&dataPointer->d_startol, buffer, counter);
	counter = serializeUint16(&dataPointer->overlap.t_section, buffer, counter);
	counter = serializeUint16(&dataPointer->overlap.d_section, buffer, counter);
	buffer[counter++] = dataPointer->v_releaseol;
		
	return counter;
}
	
uint16_t serializeGSMR_GradientProfilePacket(GSMR_GradientProfilePacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	buffer[counter++] = dataPointer->nid_packet;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->q_dir;
	buffer[counter++] = dataPointer->q_scale;
	counter = serializeUint16(&dataPointer->d_gradient_first, buffer, counter);
	buffer[counter++] = dataPointer->q_gdir_first;
	buffer[counter++] = dataPointer->g_a_first;
	buffer[counter++] = dataPointer->n_iter;
	for (i = 0; i<dataPointer->n_iter; i++)
	{
		counter = serializeUint16(&dataPointer->d_gradient[i], buffer, counter);
		buffer[counter++] = dataPointer->q_gdir[i];
		buffer[counter++] = dataPointer->g_a[i];
	}
	
	return counter;
}
	
uint16_t serializeGSMR_IntStatSpeedProfile(GSMR_IntStatSpeedProfile* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0, j=0;
	buffer[counter++] = dataPointer->nid_packet;
	counter = serializeUint16(&dataPointer->l_packet, buffer, counter);
	buffer[counter++] = dataPointer->q_dir;
	buffer[counter++] = dataPointer->q_scale;
	counter = serializeUint16(&dataPointer->d_staticFisrt, buffer, counter);
	buffer[counter++] = dataPointer->v_staticFirst;
	buffer[counter++] = dataPointer->q_frontFirst;
	buffer[counter++] = dataPointer->n_iterDiffFirst;
	for (i = 0; i<dataPointer->n_iterDiffFirst; i++)
	{
		buffer[counter++] = dataPointer->q_diffFirst[i];
		buffer[counter++] = dataPointer->nc_cddiffFirst[i];
		buffer[counter++] = dataPointer->v_diffFirst[i];
	}
	buffer[counter++] = dataPointer->n_iterStatic;
	for (i = 0; i<dataPointer->n_iterStatic; i++)
	{
		counter = serializeUint16(&dataPointer->d_static[i], buffer, counter);
		buffer[counter++] = dataPointer->v_static[i];
		buffer[counter++] = dataPointer->q_front[i];
		buffer[counter++] = dataPointer->n_iterDiff[i];
		for (j = 0; j<dataPointer->n_iterDiff[i]; j++)
		{
			buffer[counter++] = dataPointer->q_diff[i][j];
			buffer[counter++] = dataPointer->nc_cddiff[i][j];
			buffer[counter++] = dataPointer->v_diff[i][j];
		}
	}
	
	return counter;
}
	
int serializeEBT (EBT_Message* messagePointer, uint8_t* buffer)
{
	if (messagePointer!=NULL)
	{
		uint8_t *peek;
		uint16_t counter = 0;
		buffer[counter++] = messagePointer->q_updown;
		buffer[counter++] = messagePointer->m_version;
		buffer[counter++] = messagePointer->q_media;
		buffer[counter++] = messagePointer->n_pig;
		buffer[counter++] = messagePointer->n_total;
		buffer[counter++] = messagePointer->m_dup;
		buffer[counter++] = messagePointer->m_mcount;
		counter = serializeUint16(&messagePointer->nid_lrbg.nid_c, buffer, counter);
		counter = serializeUint16(&messagePointer->nid_lrbg.nid_bg, buffer, counter);
		buffer[counter++] = messagePointer->q_link;
		peek = &messagePointer->packetNb12.nid_packet;
		switch (*peek)
		{
			case 12:		//EBT_Level1MovementAuthority
				counter = serializeEBT_Level1MovementAuthority(&messagePointer->packetNb12, buffer, counter);
				break;
			case 41:		//EBT_LevelTransitionOrder
				counter = serializeEBT_LevelTransitionOrder(&messagePointer->packetNb41, buffer, counter);
				break;
			case 131:		//EBT_RBCTransitionOrder
				counter = serializeEBT_RBCTransitionOrder(&messagePointer->packetNb131, buffer, counter);
				break;
			default:
#ifdef DEBUG
				printf("Error: invalid packet pointer: #%d not treated\n", *peek);
#endif
				break;
			
		}
		buffer[counter++] = 0xFF;	///<Marqueur de fin de message
#ifdef DEBUG
		printf("EBT data: ");
		int i;
		for (i=0; i<counter; i++)
			printf("%d ", buffer[i]);
		printf("\n");
#endif
		return 0;
	}
	else
	{
		printf("Error, invalid pointer\n");
		return -1;
	}
}

int serializeMessage (void* messagePointer, uint8_t* buffer)
{
	if (messagePointer!=NULL)
	{
			
		uint8_t *nid = messagePointer;
		uint16_t counter = 0;
		buffer[counter++] = *nid;
		GSMR_CommunicationInitiationMessage *temp1;
		GSMR_NoCompatibleVersionSupported  *temp14;
		GSMR_SoM_PositionReport *temp12;
		GSMR_SoMPositionConfirmed *temp13;
		GSMR_RBCSystemVersionMessage *temp2;
		GSMR_SessionEstablishedMessage *temp3;
		GSMR_ACKTrainDataMessage *temp4;
		GSMR_Acknowledgment *temp5;
		GSMR_ValidatedTrainDataMessage *temp6;
		GSMR_MARequestMessage *temp7;
		GSMR_MovementAuthorityMessage *temp8;
		GSMR_SRAuthorisationMessage *temp9;
		GSMR_EndOfMission *temp10;
		GSMR_AckTerminationCommunicationSession *temp11;
		switch (*nid)
		{
			case 2:		//GSMR_SRAuthorisationMessage
				temp9 = messagePointer;
				counter = serializeUint16(&temp9->l_message, buffer, counter);
				counter = serializeUint32(&temp9->t_train, buffer, counter);
				buffer[counter++] = temp9->m_ack;
				counter = serializeUint16(&temp9->nid_lrbg.nid_c, buffer, counter);
				counter = serializeUint16(&temp9->nid_lrbg.nid_bg, buffer, counter);
				buffer[counter++] = temp9->q_scale;
				counter = serializeUint16(&temp9->d_sr, buffer, counter);
				break;
			case 3:		//GSMR_MovementAuthorityMessage
				temp8 = messagePointer;
				counter = serializeUint16(&temp8->l_message, buffer, counter);
				counter = serializeUint32(&temp8->t_train, buffer, counter);
				buffer[counter++] = temp8->m_ack;
				counter = serializeUint16(&temp8->nid_lrbg.nid_c, buffer, counter);
				counter = serializeUint16(&temp8->nid_lrbg.nid_bg, buffer, counter);
				counter = serializeGSMR_Level2_3MovementAuthorityPacket(&temp8->packetnb15, buffer, counter);
				break;
			case 8:		//GSMR_ACKTrainDataMessage
				temp4 = messagePointer;
				counter = serializeUint16(&temp4->l_message, buffer, counter);
				counter = serializeUint32(&temp4->t_train, buffer, counter);
				buffer[counter++] = temp4->m_ack;
				counter = serializeUint16(&temp4->nid_lrbg.nid_c, buffer, counter);
				counter = serializeUint16(&temp4->nid_lrbg.nid_bg, buffer, counter);
				counter = serializeUint32(&temp4->t_trainMessageOrigin, buffer, counter);
				break;
			case 32:		//GSMR_RBCSystemVersionMessage
				temp2 = messagePointer;
				counter = serializeUint16(&temp2->l_message, buffer, counter);
				counter = serializeUint32(&temp2->t_train, buffer, counter);
				buffer[counter++] = temp2->m_ack;
				counter = serializeUint16(&temp2->nid_lrbg.nid_c, buffer, counter);
				counter = serializeUint16(&temp2->nid_lrbg.nid_bg, buffer, counter);
				buffer[counter++] = temp2->m_version;
				break;
			case 39:		//GSMR_AckTerminationCommunicationSession
				temp11 = messagePointer;
				counter = serializeUint16(&temp11->l_message, buffer, counter);
				counter = serializeUint32(&temp11->t_train, buffer, counter);
				buffer[counter++] = temp11->m_ack;
				counter = serializeUint16(&temp11->nid_lrbg.nid_c, buffer, counter);
				counter = serializeUint16(&temp11->nid_lrbg.nid_bg, buffer, counter);
				break;
			case 43:		//GSMR_SoMPositionConfirmed
				temp13 = messagePointer;
				counter = serializeUint16(&temp13->l_message, buffer, counter);
				counter = serializeUint32(&temp13->t_train, buffer, counter);
				buffer[counter++] = temp13->m_ack;
				counter = serializeUint16(&temp13->nid_lrbg.nid_c, buffer, counter);
				counter = serializeUint16(&temp13->nid_lrbg.nid_bg, buffer, counter);
				break;
			case 129:		//GSMR_ValidatedTrainDataMessage
				temp6 = messagePointer;
				counter = serializeUint16(&temp6->l_message, buffer, counter);
				counter = serializeUint32(&temp6->t_train, buffer, counter);
				counter = serializeUint32(&temp6->nid_engine, buffer, counter);
				uint8_t* peek6 = &temp6->packetNb0.nid_packet;
				if (*peek6 == 0)
					counter = serializeGSMR_PositionReportPacket(&temp6->packetNb0, buffer, counter);
				else if (*peek6 == 1)
					counter = serializeGSMR_PositionReportPacketTwoBaliseGroups(&temp6->packetNb1, buffer, counter);
#ifdef DEBUG
				else
				{
					printf("Error: invalid packet pointer: #%d not treated\n", *peek6);
				}
#endif
				counter = serializeGSMR_ValidatedTrainDataPacket(&temp6->packetNb11, buffer, counter);
				break;
			case 132:		//GSMR_MARequestMessage
				temp7 = messagePointer;
				counter = serializeUint16(&temp7->l_message, buffer, counter);
				counter = serializeUint32(&temp7->t_train, buffer, counter);
				counter = serializeUint32(&temp7->nid_engine, buffer, counter);
				buffer[counter++] = temp7->q_marqstreason;
				uint8_t* peek7 = &temp7->packetNb0.nid_packet;
				if (*peek7 == 0)
					counter = serializeGSMR_PositionReportPacket(&temp7->packetNb0, buffer, counter);
				else if (*peek7 == 1)
					counter = serializeGSMR_PositionReportPacketTwoBaliseGroups(&temp7->packetNb1, buffer, counter);
#ifdef DEBUG
				else
				{
					printf("Error: invalid packet pointer: #%d not treated\n", *peek7);
				}
#endif
				break;
			case 146:		//GSMR_Acknowledgment
				temp5 = messagePointer;
				counter = serializeUint16(&temp5->l_message, buffer, counter);
				counter = serializeUint32(&temp5->t_train, buffer, counter);
				counter = serializeUint32(&temp5->nid_engine, buffer, counter);
				counter = serializeUint32(&temp5->t_trainMessageOrigin, buffer, counter);
				break;
			case 150:		//GSMR_EndOfMission
				temp10 = messagePointer;
				counter = serializeUint16(&temp10->l_message, buffer, counter);
				counter = serializeUint32(&temp10->t_train, buffer, counter);
				counter = serializeUint32(&temp10->nid_engine, buffer, counter);
				uint8_t* peek10 = &temp10->packetNb0.nid_packet;
				if (*peek10 == 0)
					counter = serializeGSMR_PositionReportPacket(&temp10->packetNb0, buffer, counter);
				else if (*peek10 == 1)
					counter = serializeGSMR_PositionReportPacketTwoBaliseGroups(&temp10->packetNb1, buffer, counter);
#ifdef DEBUG
				else
				{
					printf("Error: invalid packet pointer: #%d not treated\n", *peek10);
				}
#endif
				break;
			case 154:		//GSMR_NoCompatibleVersionSupported
				temp14 = messagePointer;
				counter = serializeUint16(&temp14->l_message, buffer, counter);
				counter = serializeUint32(&temp14->t_train, buffer, counter);
				counter = serializeUint32(&temp14->nid_engine, buffer, counter);
				break;
			case 155:		//GSMR_CommunicationInitiationMessage
				temp1 = messagePointer;
				counter = serializeUint16(&temp1->l_message, buffer, counter);
				counter = serializeUint32(&temp1->t_train, buffer, counter);				
				counter = serializeUint32(&temp1->nid_engine, buffer, counter);				
				break;
			case 157:		//GSMR_SoM_PositionReport
				temp12 = messagePointer;
				counter = serializeUint16(&temp12->l_message, buffer, counter);
				counter = serializeUint32(&temp12->t_train, buffer, counter);				
				counter = serializeUint32(&temp12->nid_engine, buffer, counter);				
				buffer[counter++] = temp12->q_status;
				uint8_t* peek11 = &temp12->packetNb0.nid_packet;
				if (*peek11 == 0)
					counter = serializeGSMR_PositionReportPacket(&temp12->packetNb0, buffer, counter);
				else if (*peek11 == 1)
					counter = serializeGSMR_PositionReportPacketTwoBaliseGroups(&temp12->packetNb1, buffer, counter);
#ifdef DEBUG
				else
				{
					printf("Error: invalid packet pointer: #%d not treated\n", *peek11);
				}
#endif
				if ((counter < temp12->l_message) && (temp12->trainNumber.nid_packet == 5)) //GSMR_TrainRunningNumber
				{
					counter = serializeGSMR_TrainRunningNumber(&temp12->trainNumber, buffer, counter);
				}
				if ((counter < temp12->l_message) && (temp12->itinerary.nid_packet == 44)) //GSMR_DataOutsideErtmsPacket
				{
					counter = serializeGSMR_DataOutsideErtmsPacket(&temp12->itinerary, buffer, counter);
				}
				break;
			case 159:		//GSMR_SessionEstablishedMessage
				temp3 = messagePointer;
				counter = serializeUint16(&temp3->l_message, buffer, counter);
				counter = serializeUint32(&temp3->t_train, buffer, counter);
				counter = serializeUint32(&temp3->nid_engine, buffer, counter);
				break;
			default:
#ifdef DEBUG
				printf("Error: invalid message pointer: #%d not treated\n", *nid);
#endif
				break;
			
		}
		buffer[counter++] = 0xFF;	///<Marqueur de fin de message
#ifdef DEBUG
		printf("Message # %d: ", buffer[0]);
		int i;
		for (i=0; i<counter; i++)
			printf("%d ", buffer[i]);
		printf("\n");
#endif
		return 0;
	}
	else
	{
		printf("Error, invalid pointer\n");
		return -1;
	}
}

int serializeNRBC (void* nrbcPointer, uint8_t* buffer)
{
	if (nrbcPointer!=NULL)
	{
			
		uint8_t *nid = nrbcPointer;
		uint16_t counter = 0;
		buffer[counter++] = *nid;
		NRBC_preAnnouncement *temp1;
		NRBC_RRI_request *temp2;
		NRBC_announcement *temp3;
		NRBC_RRI_confirmation *temp4;
		NRBC_TrainData *temp5;
		NRBC_TrainRunningNumber *temp6;
		NRBC_RRI *temp7;
		NRBC_TakingOverResponsibility *temp8;
		NRBC_RequestRRIConfirmation *temp9;
		NRBC_ACK *temp10;
		NRBC_Cancellation *temp11;
		NRBC_LifeSign *temp12;
		switch (*nid)
		{
			case 201:		//NRBC_preAnnouncement
				temp1 = nrbcPointer;
				counter = serializeUint16(&temp1->l_message, buffer, counter);
				counter = serializeUint16(&temp1->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp1->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp1->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp1->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp1->nid_bg, buffer, counter);
				counter = serializeUint32(&temp1->t_rbc, buffer, counter);				
				buffer[counter++] = temp1->m_ack;
				buffer[counter++] = temp1->m_mode;
				buffer[counter++] = temp1->q_masterengine;
				counter = serializeUint32(&temp1->nid_leadingEngine, buffer, counter);				
				counter = serializeGSMR_ValidatedTrainDataPacket(&temp1->packetNb11, buffer, counter);
				if (temp1->trainNumber.nid_packet != EMPTY_CONTENT)
					counter = serializeGSMR_TrainRunningNumber(&temp1->trainNumber, buffer, counter);
				break;
			case 202:		//NRBC_RRI_request
				temp2 = nrbcPointer;
				counter = serializeUint16(&temp2->l_message, buffer, counter);
				counter = serializeUint16(&temp2->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp2->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp2->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp2->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp2->nid_bg, buffer, counter);
				counter = serializeUint32(&temp2->t_rbc, buffer, counter);				
				buffer[counter++] = temp2->m_ack;
				counter = serializeUint16(&temp2->d_remaindistance, buffer, counter);
				buffer[counter++] = temp2->n_remaineoaintervals;
				buffer[counter++] = temp2->n_remaintsr;
				buffer[counter++] = temp2->q_addrestrictions;
				buffer[counter++] = temp2->n_remainlinkedbg;
				buffer[counter++] = temp2->n_remaingradientchange;
				buffer[counter++] = temp2->n_remainmasection;
				buffer[counter++] = temp2->n_remainspeedchange;
				buffer[counter++] = temp2->n_remaintrackcondition;
				buffer[counter++] = temp2->n_remainasp;
				buffer[counter++] = temp2->n_remainmodeprofile;
				buffer[counter++] = temp2->n_remainlx;
				buffer[counter++] = temp2->n_remainplatform;
				buffer[counter++] = temp2->n_remainpbd;
				buffer[counter++] = temp2->q_remainaxleload;
				buffer[counter++] = temp2->q_remainloadinggauge;
				buffer[counter++] = temp2->q_remaintraction;
				buffer[counter++] = temp2->q_remainleveltransition;
				buffer[counter++] = temp2->q_remaintractionsystemchange;
				buffer[counter++] = temp2->q_remaincurrent;
				break;
			case 203:		//NRBC_announcement
				temp3 = nrbcPointer;
				counter = serializeUint16(&temp3->l_message, buffer, counter);
				counter = serializeUint16(&temp3->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp3->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp3->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp3->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp3->nid_bg, buffer, counter);
				counter = serializeUint32(&temp3->t_rbc, buffer, counter);				
				buffer[counter++] = temp3->m_ack;
				break;
			case 206:		//NRBC_RRI_confirmation
				temp4 = nrbcPointer;
				counter = serializeUint16(&temp4->l_message, buffer, counter);
				counter = serializeUint16(&temp4->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp4->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp4->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp4->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp4->nid_bg, buffer, counter);
				counter = serializeUint32(&temp4->t_rbc, buffer, counter);				
				buffer[counter++] = temp4->m_ack;
				counter = serializeUint32(&temp4->t_rbcconf, buffer, counter);				
				buffer[counter++] = temp4->q_rriconfstatus;
				break;
			case 207:		//NRBC_TrainData
				temp5 = nrbcPointer;
				counter = serializeUint16(&temp5->l_message, buffer, counter);
				counter = serializeUint16(&temp5->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp5->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp5->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp5->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp5->nid_bg, buffer, counter);
				counter = serializeUint32(&temp5->t_rbc, buffer, counter);				
				buffer[counter++] = temp5->m_ack;
				counter = serializeGSMR_ValidatedTrainDataPacket(&temp5->packetNb11, buffer, counter);				
				break;
			case 208:		//NRBC_TrainRunningNumber
				temp6 = nrbcPointer;
				counter = serializeUint16(&temp6->l_message, buffer, counter);
				counter = serializeUint16(&temp6->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp6->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp6->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp6->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp6->nid_bg, buffer, counter);
				counter = serializeUint32(&temp6->t_rbc, buffer, counter);				
				buffer[counter++] = temp6->m_ack;
				counter = serializeGSMR_TrainRunningNumber(&temp6->trainNumber, buffer, counter);				
				break;
			case 221:		//NRBC_RRI
				temp7 = nrbcPointer;
				counter = serializeUint16(&temp7->l_message, buffer, counter);
				counter = serializeUint16(&temp7->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp7->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp7->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp7->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp7->nid_bg, buffer, counter);
				counter = serializeUint32(&temp7->t_rbc, buffer, counter);				
				buffer[counter++] = temp7->m_ack;
				buffer[counter++] = temp7->q_rrimachange;
				buffer[counter++] = temp7->q_tdchange;
				buffer[counter++] = temp7->q_matimer;
				counter = serializeGSMR_Level2_3MovementAuthorityPacket(&temp7->packetnb15, buffer, counter);				
				counter = serializeGSMR_GradientProfilePacket(&temp7->packetnb21, buffer, counter);				
				counter = serializeGSMR_IntStatSpeedProfile(&temp7->packetnb27, buffer, counter);				
				break;
			case 222:		//NRBC_TakingOverResponsibility
				temp8 = nrbcPointer;
				counter = serializeUint16(&temp8->l_message, buffer, counter);
				counter = serializeUint16(&temp8->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp8->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp8->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp8->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp8->nid_bg, buffer, counter);
				counter = serializeUint32(&temp8->t_rbc, buffer, counter);				
				buffer[counter++] = temp8->m_ack;
				break;
			case 224:		//NRBC_RequestRRIConfirmation
				temp9 = nrbcPointer;
				counter = serializeUint16(&temp9->l_message, buffer, counter);
				counter = serializeUint16(&temp9->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp9->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp9->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp9->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp9->nid_bg, buffer, counter);
				counter = serializeUint32(&temp9->t_rbc, buffer, counter);				
				buffer[counter++] = temp9->m_ack;
				buffer[counter++] = temp9->q_rrimachange;
				buffer[counter++] = temp9->q_tdchange;
				buffer[counter++] = temp9->q_matimer;
				counter = serializeGSMR_Level2_3MovementAuthorityPacket(&temp9->packetnb15, buffer, counter);				
				break;
			case 205:		//NRBC_ACK
				temp10 = nrbcPointer;
				counter = serializeUint16(&temp10->l_message, buffer, counter);
				counter = serializeUint16(&temp10->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp10->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp10->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp10->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp10->nid_bg, buffer, counter);
				counter = serializeUint32(&temp10->t_rbc, buffer, counter);				
				buffer[counter++] = temp10->m_ack;
				counter = serializeUint32(&temp10->t_rbcack, buffer, counter);				
				break;
			case 204:		//NRBC_Cancellation
				temp11 = nrbcPointer;
				counter = serializeUint16(&temp11->l_message, buffer, counter);
				counter = serializeUint16(&temp11->nid_cRBC, buffer, counter);
				counter = serializeUint16(&temp11->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp11->nid_engine, buffer, counter);				
				counter = serializeUint16(&temp11->nid_cBG, buffer, counter);
				counter = serializeUint16(&temp11->nid_bg, buffer, counter);
				counter = serializeUint32(&temp11->t_rbc, buffer, counter);				
				buffer[counter++] = temp11->m_ack;
				break;
			case 223:		//NRBC_LifeSign
				temp12 = nrbcPointer;
				counter = serializeUint16(&temp12->l_message, buffer, counter);
				counter = serializeUint16(&temp12->nid_c, buffer, counter);
				counter = serializeUint16(&temp12->nid_rbc, buffer, counter);
				counter = serializeUint32(&temp12->t_rbc, buffer, counter);				
				break;
			default:
#ifdef DEBUG
				printf("Error: invalid packet pointer: #%d not treated\n", *nid);
#endif
				break;
		}
		buffer[counter++] = 0xFF;	///<Marqueur de fin de message
#ifdef DEBUG
		printf("NRBC # %d: ", buffer[0]);
		int i;
		for (i=0; i<counter; i++)
			printf("%d ", buffer[i]);
		printf("\n");
#endif
		return 0;
	}
	else
	{
		printf("Error, invalid pointer\n");
		return -1;
	}
}


/*----------------------------deSerialize----------------------------*/


uint16_t deSerializeUint16(uint16_t* dataPointer, uint8_t* buffer, uint16_t counter)
{
	*dataPointer = buffer[counter++]<<8;
	*dataPointer += buffer[counter++];
	return counter;
}
	
uint16_t deSerializeUint32(uint32_t* dataPointer, uint8_t* buffer, uint16_t counter)
{
	*dataPointer = (uint32_t)buffer[counter++]<<24;
	*dataPointer += (uint32_t)buffer[counter++]<<16;
	*dataPointer += (uint32_t)buffer[counter++]<<8;
	*dataPointer += (uint32_t)buffer[counter++];
	return counter;
}
	
uint16_t deSerializeUint64(uint64_t* dataPointer, uint8_t* buffer, uint16_t counter)
{
	*dataPointer = (uint64_t)buffer[counter++]<<56;
	*dataPointer = (uint64_t)buffer[counter++]<<48;
	*dataPointer = (uint64_t)buffer[counter++]<<40;
	*dataPointer = (uint64_t)buffer[counter++]<<32;
	*dataPointer = (uint64_t)buffer[counter++]<<24;
	*dataPointer += (uint64_t)buffer[counter++]<<16;
	*dataPointer += (uint64_t)buffer[counter++]<<8;
	*dataPointer += (uint64_t)buffer[counter++];
	return counter;
}
	
uint16_t deSerializeEBT_Level1MovementAuthority(EBT_Level1MovementAuthority* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	dataPointer->nid_packet = buffer[counter++];
	dataPointer->q_dir = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->q_scale = buffer[counter++];
	dataPointer->v_main = buffer[counter++];
	dataPointer->v_ema = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->t_ema, buffer, counter);
	dataPointer->n_iter_sections = buffer[counter++];
	for (i = 0; i<dataPointer->n_iter_sections; i++)
	{
		counter = deSerializeUint16(&dataPointer->section[i].l_section, buffer, counter);
		dataPointer->section[i].section.q_timer = buffer[counter++];
		counter = deSerializeUint16(&dataPointer->section[i].section.t_section, buffer, counter);
		counter = deSerializeUint16(&dataPointer->section[i].section.d_section, buffer, counter);
	}
	counter = deSerializeUint16(&dataPointer->endsection.l_section, buffer, counter);
	dataPointer->endsection.section.q_timer = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->endsection.section.t_section, buffer, counter);
	counter = deSerializeUint16(&dataPointer->endsection.section.d_section, buffer, counter);
	dataPointer->end.q_timer = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->end.t_section, buffer, counter);
	counter = deSerializeUint16(&dataPointer->end.d_section, buffer, counter);
	dataPointer->q_dangerpoint = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->d_dp, buffer, counter);
	dataPointer->v_releasedp = buffer[counter++];
	dataPointer->overlap.q_timer = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->d_startol, buffer, counter);
	counter = deSerializeUint16(&dataPointer->overlap.t_section, buffer, counter);
	counter = deSerializeUint16(&dataPointer->overlap.d_section, buffer, counter);
	dataPointer->v_releaseol = buffer[counter++];

	return counter;
}
	
uint16_t deSerializeEBT_LevelTransitionOrder(EBT_LevelTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	dataPointer->nid_packet = buffer[counter++];
	dataPointer->q_dir = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->q_scale = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->d_leveltr, buffer, counter);
	dataPointer->m_leveltr = buffer[counter++];
	dataPointer->nid_ntc = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_ackleveltr, buffer, counter);
	dataPointer->n_iter_next = buffer[counter++];
	for (i = 0; i<dataPointer->n_iter_next; i++)
	{
		dataPointer->m_leveltr_next[i] = buffer[counter++];
		dataPointer->nid_ntc_next[i] = buffer[counter++];
		counter = deSerializeUint16(&dataPointer->l_ackleveltr_next[i], buffer, counter);
	}

	return counter;
}
	
uint16_t deSerializeEBT_RBCTransitionOrder(EBT_RBCTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter)
{
	dataPointer->nid_packet = buffer[counter++];
	dataPointer->q_dir = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->q_scale = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->d_rbctr, buffer, counter);
	counter = deSerializeUint16(&dataPointer->nid_c, buffer, counter);
	counter = deSerializeUint16(&dataPointer->nid_rbc, buffer, counter);
	counter = deSerializeUint64(&dataPointer->nid_radio, buffer, counter);
	dataPointer->q_sleepsession = buffer[counter++];

	return counter;
}
	
uint16_t deSerializeGSMR_TrainRunningNumber(GSMR_TrainRunningNumber* dataPointer, uint8_t* buffer, uint16_t counter)
{
	dataPointer->nid_packet = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	counter = deSerializeUint32(&dataPointer->nid_operational, buffer, counter);

	return counter;
}
	
uint16_t deSerializeGSMR_PositionReportPacketTwoBaliseGroups(GSMR_PositionReportPacketTwoBaliseGroups* dataPointer, uint8_t* buffer, uint16_t counter)
{
	dataPointer->nid_packet = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->q_scale = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->nid_lrbg.nid_c, buffer, counter);
	counter = deSerializeUint16(&dataPointer->nid_lrbg.nid_bg, buffer, counter);
	counter = deSerializeUint16(&dataPointer->nid_prvlrbg.nid_c, buffer, counter);
	counter = deSerializeUint16(&dataPointer->nid_prvlrbg.nid_bg, buffer, counter);
	counter = deSerializeUint16(&dataPointer->d_lrbg, buffer, counter);
	dataPointer->q_dirlrbg = buffer[counter++];
	dataPointer->q_dlrbg = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_doubtover, buffer, counter);
	counter = deSerializeUint16(&dataPointer->l_doubtunder, buffer, counter);
	dataPointer->q_length = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_traininit, buffer, counter);
	dataPointer->v_train = buffer[counter++];
	dataPointer->q_dirtrain = buffer[counter++];
	dataPointer->m_mode = buffer[counter++];
	dataPointer->m_level = buffer[counter++];
	dataPointer->nid_ntc = buffer[counter++];

	return counter;
}
	
uint16_t deSerializeGSMR_PositionReportPacket(GSMR_PositionReportPacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	dataPointer->nid_packet = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->q_scale = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->nid_lrbg.nid_c, buffer, counter);
	counter = deSerializeUint16(&dataPointer->nid_lrbg.nid_bg, buffer, counter);
	counter = deSerializeUint16(&dataPointer->d_lrbg, buffer, counter);
	dataPointer->q_dirlrbg = buffer[counter++];
	dataPointer->q_dlrbg = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_doubtover, buffer, counter);
	counter = deSerializeUint16(&dataPointer->l_doubtunder, buffer, counter);
	dataPointer->q_length = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_traininit, buffer, counter);
	dataPointer->v_train = buffer[counter++];
	dataPointer->q_dirtrain = buffer[counter++];
	dataPointer->m_mode = buffer[counter++];
	dataPointer->m_level = buffer[counter++];
	dataPointer->nid_ntc = buffer[counter++];

	return counter;
}

uint16_t deSerializeGSMR_ValidatedTrainDataPacket(GSMR_ValidatedTrainDataPacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	dataPointer->nid_packet = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->nc_cdtrain = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->nc_train, buffer, counter);
	counter = deSerializeUint16(&dataPointer->l_train, buffer, counter);
	dataPointer->v_maxtrain = buffer[counter++];
	dataPointer->m_loadinggauge = buffer[counter++];
	dataPointer->m_axleloadcat = buffer[counter++];
	dataPointer->m_airtight = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->n_axle, buffer, counter);
	dataPointer->n_iter_engine = buffer[counter++];
	for (i = 0; i<dataPointer->n_iter_engine; i++)
	{
		dataPointer->engine_identifier[i].m_voltage = buffer[counter++];
		counter = deSerializeUint16(&dataPointer->engine_identifier[i].nid_ctraction, buffer, counter);
	}
	dataPointer->n_iter_ntc = buffer[counter++];
	for (i = 0; i<dataPointer->n_iter_ntc; i++)
	{
		dataPointer->nid_ntc[i] = buffer[counter++];
	}
		
	return counter;
}

uint16_t deSerializeGSMR_DataOutsideErtmsPacket(GSMR_DataOutsideErtmsPacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	dataPointer->nid_packet = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->q_dir = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->nid_xuser, buffer, counter);
	switch ( dataPointer->nid_xuser )
	{
		case 102:	//nid_ntc
			dataPointer->nid_ntc = buffer[counter++];
			break;
		case 204:	//n_iter_stops et stops
			dataPointer->n_iter_stops = buffer[counter++];
			for (i = 0; i<dataPointer->n_iter_stops; i++)
			{
				counter = deSerializeUint32(&dataPointer->stops[i].t_train, buffer, counter);
				counter = deSerializeUint16(&dataPointer->stops[i].nid_rbg.nid_c, buffer, counter);
				counter = deSerializeUint16(&dataPointer->stops[i].nid_rbg.nid_bg, buffer, counter);
			}
			break;
		default:
#ifdef DEBUG
			printf("nid_xuser=%d value unknown\n", dataPointer->nid_xuser);
#endif
		break;
	}

	return counter;
}

uint16_t deSerializeGSMR_Level2_3MovementAuthorityPacket(GSMR_Level2_3MovementAuthorityPacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
#ifdef DEBUG
	uint16_t initialIndex = counter;
#endif
	dataPointer->nid_packet = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->q_dir = buffer[counter++];
	dataPointer->q_scale = buffer[counter++];
	dataPointer->v_ema = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->t_ema, buffer, counter);
	dataPointer->n_iter_section = buffer[counter++];
	for (i = 0; i<dataPointer->n_iter_section; i++)
	{
		counter = deSerializeUint16(&dataPointer->section[i].l_section, buffer, counter);
		dataPointer->section[i].section.q_timer = buffer[counter++];
		counter = deSerializeUint16(&dataPointer->section[i].section.t_section, buffer, counter);
		counter = deSerializeUint16(&dataPointer->section[i].section.d_section, buffer, counter);
	}
	counter = deSerializeUint16(&dataPointer->endsection.l_section, buffer, counter);
	dataPointer->endsection.section.q_timer = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->endsection.section.t_section, buffer, counter);
	counter = deSerializeUint16(&dataPointer->endsection.section.d_section, buffer, counter);
	dataPointer->end.q_timer = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->end.t_section, buffer, counter);
	counter = deSerializeUint16(&dataPointer->end.d_section, buffer, counter);
	dataPointer->q_dangerpoint = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->d_dp, buffer, counter);
	dataPointer->v_releasedp = buffer[counter++];
	dataPointer->overlap.q_timer = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->d_startol, buffer, counter);
	counter = deSerializeUint16(&dataPointer->overlap.t_section, buffer, counter);
	counter = deSerializeUint16(&dataPointer->overlap.d_section, buffer, counter);
	dataPointer->v_releaseol = buffer[counter++];
#ifdef DEBUG
	if( counter-initialIndex != dataPointer->l_packet)
		printf("Error, expected length = %d, found %d\n", dataPointer->l_packet, counter-initialIndex);
#endif
		
	return counter;
}
	
uint16_t deSerializeGSMR_GradientProfilePacket(GSMR_GradientProfilePacket* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0;
	dataPointer->nid_packet = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->q_dir = buffer[counter++];
	dataPointer->q_scale = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->d_gradient_first, buffer, counter);
	dataPointer->q_gdir_first = buffer[counter++];
	dataPointer->g_a_first = buffer[counter++];
	dataPointer->n_iter = buffer[counter++];
	for (i = 0; i<dataPointer->n_iter; i++)
	{
		counter = deSerializeUint16(&dataPointer->d_gradient[i], buffer, counter);
		dataPointer->q_gdir[i] = buffer[counter++];
		dataPointer->g_a[i] = buffer[counter++];
	}
	
	return counter;
}
	
uint16_t deSerializeGSMR_IntStatSpeedProfile(GSMR_IntStatSpeedProfile* dataPointer, uint8_t* buffer, uint16_t counter)
{
	int i = 0, j=0;
	dataPointer->nid_packet = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->l_packet, buffer, counter);
	dataPointer->q_dir = buffer[counter++];
	dataPointer->q_scale = buffer[counter++];
	counter = deSerializeUint16(&dataPointer->d_staticFisrt, buffer, counter);
	dataPointer->v_staticFirst = buffer[counter++];
	dataPointer->q_frontFirst = buffer[counter++];
	dataPointer->n_iterDiffFirst = buffer[counter++];
	for (i = 0; i<dataPointer->n_iterDiffFirst; i++)
	{
		dataPointer->q_diffFirst[i] = buffer[counter++];
		dataPointer->nc_cddiffFirst[i] = buffer[counter++];
		dataPointer->v_diffFirst[i] = buffer[counter++];
	}
	dataPointer->n_iterStatic = buffer[counter++];
	for (i = 0; i<dataPointer->n_iterStatic; i++)
	{
		counter = deSerializeUint16(&dataPointer->d_static[i], buffer, counter);
		dataPointer->v_static[i] = buffer[counter++];
		dataPointer->q_front[i] = buffer[counter++];
		dataPointer->n_iterDiff[i] = buffer[counter++];
		for (j = 0; j<dataPointer->n_iterDiff[i]; j++)
		{
			dataPointer->q_diff[i][j] = buffer[counter++];
			dataPointer->nc_cddiff[i][j] = buffer[counter++];
			dataPointer->v_diff[i][j] = buffer[counter++];
		}
	}
	
	return counter;
}	

int deSerializeEBT (EBT_Message* messagePointer, uint8_t* buffer)
{
	if (buffer!=NULL)
	{
		uint16_t counter = 0;
		messagePointer->q_updown = buffer[counter++];
		messagePointer->m_version = buffer[counter++];
		messagePointer->q_media = buffer[counter++];
		messagePointer->n_pig = buffer[counter++];
		messagePointer->n_total = buffer[counter++];
		messagePointer->m_dup = buffer[counter++];
		messagePointer->m_mcount = buffer[counter++];
		counter = deSerializeUint16(&messagePointer->nid_lrbg.nid_c, buffer, counter);
		counter = deSerializeUint16(&messagePointer->nid_lrbg.nid_bg, buffer, counter);
		messagePointer->q_link = buffer[counter++];
		switch (buffer[counter])
		{
			case 12:		//EBT_Level1MovementAuthority
				counter = deSerializeEBT_Level1MovementAuthority(&messagePointer->packetNb12, buffer, counter);
				break;
			case 41:		//EBT_LevelTransitionOrder
				counter = deSerializeEBT_LevelTransitionOrder(&messagePointer->packetNb41, buffer, counter);
				break;
			case 131:		//EBT_RBCTransitionOrder
				counter = deSerializeEBT_RBCTransitionOrder(&messagePointer->packetNb131, buffer, counter);
				break;
			default:
#ifdef DEBUG
				printf("Error: invalid packet pointer: #%d not treated\n", buffer[counter]);
#endif
				break;
			
		}
		if (buffer[counter] == 0xFF)	///<Marqueur de fin de message
		{
#ifdef DEBUG
			printf("EBT # %d successfully decoded\n", buffer[12]);
#endif
			return 0;
		}
		else
		{
#ifdef DEBUG
			printf("Error decoding message, EOM flag = %d\n", buffer[counter]);
#endif
			return -2;
		}
	}
	else
	{
#ifdef DEBUG
		printf("Error, invalid data stream\n");
#endif
		return -1;
	}	
}
	
int deserializeMessage(uint8_t* buffer, uint8_t messNb, void* messagePointer)
{
	if (buffer!=NULL)
	{
		uint16_t counter = 1;
		GSMR_CommunicationInitiationMessage *temp1;
		GSMR_NoCompatibleVersionSupported *temp14;
		GSMR_SoM_PositionReport *temp12;
		GSMR_SoMPositionConfirmed *temp13;
		GSMR_RBCSystemVersionMessage *temp2;
		GSMR_SessionEstablishedMessage *temp3;
		GSMR_ACKTrainDataMessage *temp4;
		GSMR_Acknowledgment *temp5;
		GSMR_ValidatedTrainDataMessage *temp6;
		GSMR_MARequestMessage *temp7;
		GSMR_MovementAuthorityMessage *temp8;
		GSMR_SRAuthorisationMessage *temp9;
		GSMR_EndOfMission *temp10;
		GSMR_AckTerminationCommunicationSession *temp11;
		switch (messNb)
		{
			case 2:		//GSMR_SRAuthorisationMessage
				temp9 = messagePointer;
				counter = deSerializeUint16(&temp9->l_message, buffer, counter);
				counter = deSerializeUint32(&temp9->t_train, buffer, counter);
				temp9->m_ack = buffer[counter++];
				counter = deSerializeUint16(&temp9->nid_lrbg.nid_c, buffer, counter);
				counter = deSerializeUint16(&temp9->nid_lrbg.nid_bg, buffer, counter);
				temp9->q_scale = buffer[counter++];
				counter = deSerializeUint16(&temp9->d_sr, buffer, counter);
				break;
			case 3:		//GSMR_MovementAuthorityMessage
				temp8 = messagePointer;
				counter = deSerializeUint16(&temp8->l_message, buffer, counter);
				counter = deSerializeUint32(&temp8->t_train, buffer, counter);
				temp8->m_ack = buffer[counter++];
				counter = deSerializeUint16(&temp8->nid_lrbg.nid_c, buffer, counter);
				counter = deSerializeUint16(&temp8->nid_lrbg.nid_bg, buffer, counter);
				counter = deSerializeGSMR_Level2_3MovementAuthorityPacket(&temp8->packetnb15, buffer, counter);
				break;
			case 8:		//GSMR_ACKTrainDataMessage
				temp4 = messagePointer;
				counter = deSerializeUint16(&temp4->l_message, buffer, counter);
				counter = deSerializeUint32(&temp4->t_train, buffer, counter);
				temp4->m_ack = buffer[counter++];
				counter = deSerializeUint16(&temp4->nid_lrbg.nid_c, buffer, counter);
				counter = deSerializeUint16(&temp4->nid_lrbg.nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp4->t_trainMessageOrigin, buffer, counter);
				break;
			case 32:		//GSMR_RBCSystemVersionMessage
				temp2 = messagePointer;
				counter = deSerializeUint16(&temp2->l_message, buffer, counter);
				counter = deSerializeUint32(&temp2->t_train, buffer, counter);
				temp2->m_ack = buffer[counter++];
				counter = deSerializeUint16(&temp2->nid_lrbg.nid_c, buffer, counter);
				counter = deSerializeUint16(&temp2->nid_lrbg.nid_bg, buffer, counter);
				temp2->m_version = buffer[counter++];
				break;
			case 39:		//GSMR_AckTerminationCommunicationSession
				temp11 = messagePointer;
				counter = deSerializeUint16(&temp11->l_message, buffer, counter);
				counter = deSerializeUint32(&temp11->t_train, buffer, counter);
				temp11->m_ack = buffer[counter++];
				counter = deSerializeUint16(&temp11->nid_lrbg.nid_c, buffer, counter);
				counter = deSerializeUint16(&temp11->nid_lrbg.nid_bg, buffer, counter);
				break;
			case 43:		//GSMR_SoMPositionConfirmed
				temp13 = messagePointer;
				counter = deSerializeUint16(&temp13->l_message, buffer, counter);
				counter = deSerializeUint32(&temp13->t_train, buffer, counter);
				temp13->m_ack = buffer[counter++];
				counter = deSerializeUint16(&temp13->nid_lrbg.nid_c, buffer, counter);
				counter = deSerializeUint16(&temp13->nid_lrbg.nid_bg, buffer, counter);
				break;
			case 129:		//GSMR_ValidatedTrainDataMessage
				temp6 = messagePointer;
				counter = deSerializeUint16(&temp6->l_message, buffer, counter);
				counter = deSerializeUint32(&temp6->t_train, buffer, counter);
				counter = deSerializeUint32(&temp6->nid_engine, buffer, counter);
				uint8_t* peek6 = &buffer[counter];
				if (*peek6 == 0)
					counter = deSerializeGSMR_PositionReportPacket(&temp6->packetNb0, buffer, counter);
				else if (*peek6 == 1)
					counter = deSerializeGSMR_PositionReportPacketTwoBaliseGroups(&temp6->packetNb1, buffer, counter);
				counter = deSerializeGSMR_ValidatedTrainDataPacket(&temp6->packetNb11, buffer, counter);
				break;
			case 132:		//GSMR_MARequestMessage
				temp7 = messagePointer;
				counter = deSerializeUint16(&temp7->l_message, buffer, counter);
				counter = deSerializeUint32(&temp7->t_train, buffer, counter);
				counter = deSerializeUint32(&temp7->nid_engine, buffer, counter);
				temp7->q_marqstreason = buffer[counter++];
				uint8_t* peek7 = &buffer[counter];
				if (*peek7 == 0)
					counter = deSerializeGSMR_PositionReportPacket(&temp7->packetNb0, buffer, counter);
				else if (*peek7 == 1)
					counter = deSerializeGSMR_PositionReportPacketTwoBaliseGroups(&temp7->packetNb1, buffer, counter);
				break;
			case 146:		//GSMR_Acknowledgment
				temp5 = messagePointer;
				counter = deSerializeUint16(&temp5->l_message, buffer, counter);
				counter = deSerializeUint32(&temp5->t_train, buffer, counter);
				counter = deSerializeUint32(&temp5->nid_engine, buffer, counter);
				counter = deSerializeUint32(&temp5->t_trainMessageOrigin, buffer, counter);
				break;
			case 150:		//GSMR_EndOfMission
				temp10 = messagePointer;
				counter = deSerializeUint16(&temp10->l_message, buffer, counter);
				counter = deSerializeUint32(&temp10->t_train, buffer, counter);
				counter = deSerializeUint32(&temp10->nid_engine, buffer, counter);
				uint8_t* peek10 = &temp10->packetNb0.nid_packet;
				if (*peek10 == 0)
					counter = deSerializeGSMR_PositionReportPacket(&temp10->packetNb0, buffer, counter);
				else if (*peek10 == 1)
					counter = deSerializeGSMR_PositionReportPacketTwoBaliseGroups(&temp10->packetNb1, buffer, counter);
				break;
			case 154:		//GSMR_NoCompatibleVersionSupported
				temp14 = messagePointer;
				counter = deSerializeUint16(&temp14->l_message, buffer, counter);
				counter = deSerializeUint32(&temp14->t_train, buffer, counter);
				counter = deSerializeUint32(&temp14->nid_engine, buffer, counter);
				break;
			case 155:		//GSMR_CommunicationInitiationMessage
				temp1 = messagePointer;
				counter = deSerializeUint16(&temp1->l_message, buffer, counter);
				counter = deSerializeUint32(&temp1->t_train, buffer, counter);				
				counter = deSerializeUint32(&temp1->nid_engine, buffer, counter);				
				break;
			case 157:		//GSMR_SoM_PositionReport
				temp12 = messagePointer;
				counter = deSerializeUint16(&temp12->l_message, buffer, counter);
				counter = deSerializeUint32(&temp12->t_train, buffer, counter);				
				counter = deSerializeUint32(&temp12->nid_engine, buffer, counter);				
				temp12->q_status = buffer[counter++];
				uint8_t* peek11 = &buffer[counter];
				if (*peek11 == 0)
					counter = deSerializeGSMR_PositionReportPacket(&temp12->packetNb0, buffer, counter);
				else if (*peek11 == 1)
					counter = deSerializeGSMR_PositionReportPacketTwoBaliseGroups(&temp12->packetNb1, buffer, counter);
				peek11 = &buffer[counter];
				if ((counter < temp12->l_message-1) && (*peek11 == 5)) //GSMR_TrainRunningNumber
				{
					counter = deSerializeGSMR_TrainRunningNumber(&temp12->trainNumber, buffer, counter);
				}
				if ((counter < temp12->l_message-1) && (*peek11 == 44)) //GSMR_DataOutsideErtmsPacket
				{
					counter = deSerializeGSMR_DataOutsideErtmsPacket(&temp12->itinerary, buffer, counter);
				}
				break;
			case 159:		//GSMR_SessionEstablishedMessage
				temp3 = messagePointer;
				counter = deSerializeUint16(&temp3->l_message, buffer, counter);
				counter = deSerializeUint32(&temp3->t_train, buffer, counter);
				counter = deSerializeUint32(&temp3->nid_engine, buffer, counter);
				break;
			default:
#ifdef DEBUG
				printf("Error: invalid message pointer: #%d not treated\n", buffer[counter]);
#endif
				break;
			
		}
		if (buffer[counter] == 0xFF)	///<Marqueur de fin de message
		{
#ifdef DEBUG
			printf("Message # %d successfully decoded\n", buffer[0]);
#endif
			return 0;
		}
		else
		{
#ifdef DEBUG
			printf("Error decoding message, EOM flag = %d at index %d\n", buffer[counter], counter);
#endif
			return -2;
		}
	}
	else
	{
#ifdef DEBUG
		printf("Error, invalid data stream\n");
#endif
		return -1;
	}	
}

int deSerializeNRBC (uint8_t* buffer, uint8_t messNb, void* nrbcPointer)
{
	if (buffer!=NULL)
	{
		uint16_t counter = 1;
		NRBC_preAnnouncement *temp1;
		NRBC_RRI_request *temp2;
		NRBC_announcement *temp3;
		NRBC_RRI_confirmation *temp4;
		NRBC_TrainData *temp5;
		NRBC_TrainRunningNumber *temp6;
		NRBC_RRI *temp7;
		NRBC_TakingOverResponsibility *temp8;
		NRBC_RequestRRIConfirmation *temp9;
		NRBC_ACK *temp10;
		NRBC_Cancellation *temp11;
		NRBC_LifeSign *temp12;
		switch (messNb)
		{
			case 201:		//NRBC_preAnnouncement
				temp1 = nrbcPointer;
				counter = deSerializeUint16(&temp1->l_message, buffer, counter);
				counter = deSerializeUint16(&temp1->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp1->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp1->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp1->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp1->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp1->t_rbc, buffer, counter);				
				temp1->m_ack = buffer[counter++];
				temp1->m_mode = buffer[counter++];
				temp1->q_masterengine = buffer[counter++];
				counter = deSerializeUint32(&temp1->nid_leadingEngine, buffer, counter);				
				counter = deSerializeGSMR_ValidatedTrainDataPacket(&temp1->packetNb11, buffer, counter);
				uint8_t* peek1 = &buffer[counter];
				if (*peek1 == 5)	//GSMR_TrainRunningNumber
					counter = deSerializeGSMR_TrainRunningNumber(&temp1->trainNumber, buffer, counter);
				else
					temp1->trainNumber.nid_packet = EMPTY_CONTENT;
				break;
			case 202:		//NRBC_RRI_request
				temp2 = nrbcPointer;
				counter = deSerializeUint16(&temp2->l_message, buffer, counter);
				counter = deSerializeUint16(&temp2->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp2->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp2->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp2->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp2->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp2->t_rbc, buffer, counter);				
				temp2->m_ack = buffer[counter++];
				counter = deSerializeUint16(&temp2->d_remaindistance, buffer, counter);
				temp2->n_remaineoaintervals = buffer[counter++];
				temp2->n_remaintsr = buffer[counter++];
				temp2->q_addrestrictions = buffer[counter++];
				temp2->n_remainlinkedbg = buffer[counter++];
				temp2->n_remaingradientchange = buffer[counter++];
				temp2->n_remainmasection = buffer[counter++];
				temp2->n_remainspeedchange = buffer[counter++];
				temp2->n_remaintrackcondition = buffer[counter++];
				temp2->n_remainasp = buffer[counter++];
				temp2->n_remainmodeprofile = buffer[counter++];
				temp2->n_remainlx = buffer[counter++];
				temp2->n_remainplatform = buffer[counter++];
				temp2->n_remainpbd = buffer[counter++];
				temp2->q_remainaxleload = buffer[counter++];
				temp2->q_remainloadinggauge = buffer[counter++];
				temp2->q_remaintraction = buffer[counter++];
				temp2->q_remainleveltransition = buffer[counter++];
				temp2->q_remaintractionsystemchange = buffer[counter++];
				temp2->q_remaincurrent = buffer[counter++];
				break;
			case 203:		//NRBC_announcement
				temp3 = nrbcPointer;
				counter = deSerializeUint16(&temp3->l_message, buffer, counter);
				counter = deSerializeUint16(&temp3->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp3->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp3->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp3->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp3->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp3->t_rbc, buffer, counter);				
				temp3->m_ack = buffer[counter++];
				break;
			case 206:		//NRBC_RRI_confirmation
				temp4 = nrbcPointer;
				counter = deSerializeUint16(&temp4->l_message, buffer, counter);
				counter = deSerializeUint16(&temp4->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp4->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp4->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp4->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp4->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp4->t_rbc, buffer, counter);				
				temp4->m_ack = buffer[counter++];
				counter = deSerializeUint32(&temp4->t_rbcconf, buffer, counter);				
				temp4->q_rriconfstatus = buffer[counter++];
				break;
			case 207:		//NRBC_TrainData
				temp5 = nrbcPointer;
				counter = deSerializeUint16(&temp5->l_message, buffer, counter);
				counter = deSerializeUint16(&temp5->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp5->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp5->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp5->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp5->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp5->t_rbc, buffer, counter);				
				temp5->m_ack = buffer[counter++];
				counter = deSerializeGSMR_ValidatedTrainDataPacket(&temp5->packetNb11, buffer, counter);				
				break;
			case 208:		//NRBC_TrainRunningNumber
				temp6 = nrbcPointer;
				counter = deSerializeUint16(&temp6->l_message, buffer, counter);
				counter = deSerializeUint16(&temp6->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp6->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp6->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp6->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp6->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp6->t_rbc, buffer, counter);				
				temp6->m_ack = buffer[counter++];
				counter = deSerializeGSMR_TrainRunningNumber(&temp6->trainNumber, buffer, counter);				
				break;
			case 221:		//NRBC_RRI
				temp7 = nrbcPointer;
				counter = deSerializeUint16(&temp7->l_message, buffer, counter);
				counter = deSerializeUint16(&temp7->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp7->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp7->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp7->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp7->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp7->t_rbc, buffer, counter);				
				temp7->m_ack = buffer[counter++];
				temp7->q_rrimachange = buffer[counter++];
				temp7->q_tdchange = buffer[counter++];
				temp7->q_matimer = buffer[counter++];
				counter = deSerializeGSMR_Level2_3MovementAuthorityPacket(&temp7->packetnb15, buffer, counter);				
				counter = deSerializeGSMR_GradientProfilePacket(&temp7->packetnb21, buffer, counter);				
				counter = deSerializeGSMR_IntStatSpeedProfile(&temp7->packetnb27, buffer, counter);				
				break;
			case 222:		//NRBC_TakingOverResponsibility
				temp8 = nrbcPointer;
				counter = deSerializeUint16(&temp8->l_message, buffer, counter);
				counter = deSerializeUint16(&temp8->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp8->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp8->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp8->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp8->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp8->t_rbc, buffer, counter);				
				temp8->m_ack = buffer[counter++];
				break;
			case 224:		//NRBC_RequestRRIConfirmation
				temp9 = nrbcPointer;
				counter = deSerializeUint16(&temp9->l_message, buffer, counter);
				counter = deSerializeUint16(&temp9->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp9->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp9->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp9->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp9->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp9->t_rbc, buffer, counter);				
				temp9->m_ack = buffer[counter++];
				temp9->q_rrimachange = buffer[counter++];
				temp9->q_tdchange = buffer[counter++];
				temp9->q_matimer = buffer[counter++];
				counter = deSerializeGSMR_Level2_3MovementAuthorityPacket(&temp9->packetnb15, buffer, counter);				
				break;
			case 205:		//NRBC_ACK
				temp10 = nrbcPointer;
				counter = deSerializeUint16(&temp10->l_message, buffer, counter);
				counter = deSerializeUint16(&temp10->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp10->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp10->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp10->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp10->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp10->t_rbc, buffer, counter);				
				temp10->m_ack = buffer[counter++];
				counter = deSerializeUint32(&temp10->t_rbcack, buffer, counter);				
				break;
			case 204:		//NRBC_Cancellation
				temp11 = nrbcPointer;
				counter = deSerializeUint16(&temp11->l_message, buffer, counter);
				counter = deSerializeUint16(&temp11->nid_cRBC, buffer, counter);
				counter = deSerializeUint16(&temp11->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp11->nid_engine, buffer, counter);				
				counter = deSerializeUint16(&temp11->nid_cBG, buffer, counter);
				counter = deSerializeUint16(&temp11->nid_bg, buffer, counter);
				counter = deSerializeUint32(&temp11->t_rbc, buffer, counter);				
				temp11->m_ack = buffer[counter++];
				break;
			case 223:		//NRBC_LifeSign
				temp12 = nrbcPointer;
				counter = deSerializeUint16(&temp12->l_message, buffer, counter);
				counter = deSerializeUint16(&temp12->nid_c, buffer, counter);
				counter = deSerializeUint16(&temp12->nid_rbc, buffer, counter);
				counter = deSerializeUint32(&temp12->t_rbc, buffer, counter);				
				break;
			default:
#ifdef DEBUG
				printf("Error: invalid message pointer: #%d not treated\n", buffer[counter]);
#endif
				break;
			
		}
		if (buffer[counter] == 0xFF)	///<Marqueur de fin de message
		{
#ifdef DEBUG
			printf("Message # %d successfully decoded\n", buffer[0]);
#endif
			return 0;
		}
		else
		{
#ifdef DEBUG
			printf("Error decoding message, EOM flag = %d at index %d\n", buffer[counter], counter);
#endif
			return -2;
		}
	}
	else
	{
#ifdef DEBUG
		printf("Error, invalid data stream\n");
#endif
		return -1;
	}	
}
	
