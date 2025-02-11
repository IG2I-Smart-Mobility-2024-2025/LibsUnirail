#ifndef GSM_R_PACKET_H
	#define	GSM_R_PACKET_H
	
	#include <stdint.h>
	/** Legende:
		A_         Acceleration<BR>
		D_         distance<BR>
		G_         Gradient<BR>
		L_         length<BR>
		M_         Miscellaneous<BR>
		N_         Number<BR>
		NC_        class number<BR>
		NID_       identity number<BR>
		Q_         Qualifier<BR>
		T_         time/date<BR>
		V_         Speed<BR>
		X_         Text<BR>
	*/
	///GSMR_nid_lrbg:
	/**Taille:4<BR>
		nid_lrbg: Identity of last relevant balise group = Country/region identity (NID_C, 10bits) + balise identity number of last relevant balise group (NID_BG, 14bits) 
	*/
	typedef struct 
	{
		uint16_t nid_c;
		uint16_t nid_bg;
	} GSMR_nid_lrbg;
	
	///GSMR_engine_identifier: Variable intermediaire, non existant dans la doc originale.
	/**Taille:1-3<BR>
		engine_identifier: Elle existe car elle peut exister en plusieurs exemplaires, selon la valeur de n_iter immediatement superieure 
		\todo: la taille du packet envoye sera plus petite que celle-ci at a calculer avant chaque envoi, attention a cela!
		\todo nid_ctraction existe si m_voltage!=0
	*/
	typedef struct 
	{
		uint8_t m_voltage;
		uint16_t nid_ctraction;
	} GSMR_engine_identifier;
	
	///GSMR_PositionReportPacket: reports the train position and speed as well as some additional information (e.g. mode, level, etc.)
	/**Taille:21-24<BR>
		ID packet:0<BR>
		\todo l_traininit est optionnel selon la valeur de q_length
		\todo nid_ntc existe si m_level=NTC (1)
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 0
		uint16_t l_packet;	///< = 24
		uint8_t q_scale;
		GSMR_nid_lrbg nid_lrbg;
		uint16_t d_lrbg;
		uint8_t q_dirlrbg;
		uint8_t q_dlrbg;
		uint16_t l_doubtover;
		uint16_t l_doubtunder;
		uint8_t q_length;
		uint16_t l_traininit;
		uint8_t v_train;
		uint8_t q_dirtrain;
		uint8_t m_mode;
		uint8_t m_level;
		uint8_t nid_ntc;
	} GSMR_PositionReportPacket;
	
	///GSMR_PositionReportPacketTwoBaliseGroups: extension of the â€œstandard position report â€œ packet 0.
	/**Taille:25-28<BR>
		ID packet:1<BR>
		It is used in case of single balise groups if the orientation of the LRBG is unknown but the on-board equipment is able to report a second balise group (the one detected before) to give a direction reference for the directional information in the position report.
		\todo l_traininit est optionnel selon la valeur de q_length
		\todo nid_ntc existe si m_level=NTC (1)
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 1
		uint16_t l_packet;	///< = 28
		uint8_t q_scale;
		GSMR_nid_lrbg nid_lrbg;
		GSMR_nid_lrbg nid_prvlrbg;
		uint16_t d_lrbg;
		uint8_t q_dirlrbg;
		uint8_t q_dlrbg;
		uint16_t l_doubtover;
		uint16_t l_doubtunder;
		uint8_t q_length;
		uint16_t l_traininit;
		uint8_t v_train;
		uint8_t q_dirtrain;
		uint8_t m_mode;
		uint8_t m_level;
		uint8_t nid_ntc;
	} GSMR_PositionReportPacketTwoBaliseGroups;
	
	///GSMR_Level2_3TransitionInformationPacket: Identity of the level 2/3 transition balise group.
	/**Taille:7<BR>
		ID packet:9<BR>
		It is used in case of single balise groups if the orientation of the LRBG is unknown but the on-board equipment is able to report a second balise group (the one detected before) to give a direction reference for the directional information in the position report.
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 9
		uint16_t l_packet;	///< = 7
		GSMR_nid_lrbg nid_lrbg;
	} GSMR_Level2_3TransitionInformationPacket;
	
	///GSMR_ValidatedTrainDataPacket: Validated train data.
	/**Taille:16-144<BR>
		ID packet:11<BR>
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 11
		uint16_t l_packet;
		uint8_t nc_cdtrain;
		uint16_t nc_train;
		uint16_t l_train;
		uint8_t v_maxtrain;
		uint8_t m_loadinggauge;
		uint8_t m_axleloadcat;
		uint8_t m_airtight;
		uint16_t n_axle;
		uint8_t n_iter_engine;
		GSMR_engine_identifier engine_identifier[32];
		uint8_t n_iter_ntc;
		uint8_t nid_ntc[32];
	} GSMR_ValidatedTrainDataPacket;
	
	///GSMR_SectionTimer: Variable intermediaire. 
	/**Taille:5<BR>
		Contient s'il y a un timer (q_timer), sa valeur (t_section) et la distance de validite depuis le debut du tronÃ§on ("stop location", pour la plupart)
	*/
	typedef struct 
	{
		uint8_t q_timer;
		uint16_t t_section;
		uint16_t d_section;
	} ERTMS_SectionTimer;
	
	///GSMR_SectionDescription: Variable intermediaire. 
	/**Taille:3-7<BR>
		\todo t_sectiontimer et d_sectiontimerstoploc existent si q_sectiontimer=1
	*/
	typedef struct 
	{
		uint16_t l_section;
		ERTMS_SectionTimer section;
	} GSMR_SectionDescription;
	
	///GSMR_Level2_3MovementAuthorityPacket: Transmission of a movement authority for levels 2/3. 
	/**Taille:33-257<BR>
		ID packet:15<BR>
		\todo t_endtimer et d_endtimerstoploc existent si q_endtimer=1
		\todo d_dp et v_releasedp existent si q_dangerpoint=1
		\todo d_startol, t_ol et v_releaseol existent si q_overlap=1
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 15
		uint16_t l_packet;
		uint8_t q_dir;
		uint8_t q_scale;
		uint8_t v_ema;
		uint16_t t_ema;
		uint8_t n_iter_section;
		GSMR_SectionDescription section[32];
		GSMR_SectionDescription endsection;
		ERTMS_SectionTimer end;
		uint8_t q_dangerpoint;
		uint16_t d_dp;
		uint8_t v_releasedp;
		ERTMS_SectionTimer overlap;
		uint16_t d_startol;
		uint8_t v_releaseol;
	} GSMR_Level2_3MovementAuthorityPacket;
	
	///GSMR_ItineraryDescription: Variable intermediaire. 
	/**Taille:8<BR>
		Contient une etape d'un itineraire, avec:<BR>
		le temps(t_train)<BR>
		la balise de reference(nid_rbg)
	*/
	typedef struct 
	{
		uint32_t t_train;
		GSMR_nid_lrbg nid_rbg;
	} GSMR_ItineraryDescription;
	
	///GSMR_DataOutsideErtmsPacket: Data used by applications outside the ERTMS/ETCS system. 
	/**Taille:6-263<BR>
		ID packet:44<BR>
		\todo nid_ntc existe si nid_xuser=102
		\todo n_iter_stops et stops existent si nid_xuser=204
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 44
		uint16_t l_packet;
		uint8_t q_dir;
		uint16_t nid_xuser;
		uint8_t nid_ntc;
		uint8_t n_iter_stops;
		GSMR_ItineraryDescription stops[32];
	} GSMR_DataOutsideErtmsPacket;

	///GSMR_TrainRunningNumber: Train running number. 
	/**Taille:7<BR>
		ID packet:5<BR>
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 5
		uint16_t l_packet;	///< = 7
		uint32_t nid_operational;
	} GSMR_TrainRunningNumber;

	///GSMR_GradientProfilePacket: Transmission of the gradient.
	/**Taille: 10-138<BR>
		ID packet:21<BR>
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 21
		uint8_t q_dir;
		uint16_t l_packet;
		uint8_t q_scale;
		uint16_t d_gradient_first;
		uint8_t q_gdir_first;
		uint8_t g_a_first;
		uint8_t n_iter;
		uint16_t d_gradient[32];
		uint8_t q_gdir[32];
		uint8_t g_a[32];
	} GSMR_GradientProfilePacket;

	///GSMR_IntStatSpeedProfile: Static speed profile and optionally speed limits depending on the international train category.
	/**Taille: 11-3339<BR>
		ID packet:27<BR>
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 27
		uint8_t q_dir;
		uint16_t l_packet;
		uint8_t q_scale;
		uint16_t d_staticFisrt;
		uint8_t v_staticFirst;
		uint8_t q_frontFirst;
		uint8_t n_iterDiffFirst;
		uint8_t q_diffFirst[32];
		union
		{
			uint8_t nc_cddiffFirst[32];	///<If Q_DIFF(n) = 0
			uint8_t nc_diffFirst[32];	///<If Q_DIFF(n) = 1 or 2
		};
		uint8_t v_diffFirst[32];
		uint8_t n_iterStatic;
		uint16_t d_static[32];
		uint8_t v_static[32];
		uint8_t q_front[32];
		uint8_t n_iterDiff[32];
		uint8_t q_diff[32][32];
		union
		{
			uint8_t nc_cddiff[32][32];	///<If Q_DIFF(k,m) = 0
			uint8_t nc_diff[32][32];	///<If Q_DIFF(k,m) = 1 or 2
		};
		uint8_t v_diff[32][32];
	
	} GSMR_IntStatSpeedProfile;
	
#endif	
