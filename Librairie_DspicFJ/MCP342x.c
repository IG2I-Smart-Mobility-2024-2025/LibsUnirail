

#include <XC.h>
#include "MCP342x.h"


void InitiateConv(int NumeroChannel)
/*	Si BUS I2C = 100KHz
    Temps dans la routine = 220us
 */ {
    switch (NumeroChannel) {
        case 1:
            MyStartI2C(); //Generate Start condition
            MyWriteI2C(MCP342X_DEFAULT_ADDRESS << 1); //Ecriture
            MyWriteI2C(MCP342X_CHANNEL_1 | MCP342X_SIZE_12BIT | MCP342X_GAIN_1X |
                    MCP342X_MODE_ONESHOT | MCP342X_RDY);
            MyStopI2C(); //Send Stop Condition
            break;

        case 2:
            MyStartI2C(); //Generate Start condition
            MyWriteI2C(MCP342X_DEFAULT_ADDRESS << 1); //Ecriture
            MyWriteI2C(MCP342X_CHANNEL_2 | MCP342X_SIZE_12BIT | MCP342X_GAIN_1X |
                    MCP342X_MODE_ONESHOT | MCP342X_RDY);
            MyStopI2C(); //Send Stop Condition
            break;

        default:
            while (1);
            break;

    }
}

unsigned int RecupereResultConvMCP3426NoVerif_RDY(void) {
    unsigned int Val_Lue;
    unsigned char ByteLu;
    //    long ii;
//    unsigned int VAL_Volt_VirguleVolt, ValenVolt, ValenDiziemeDeVolt;
    /*	Si BUS I2C = 100KHz
        Temps dans la routine = 435us
     */

    MyStartI2C(); //Generate Start condition
    MyWriteI2C((MCP342X_DEFAULT_ADDRESS << 1) + 1); //Lecture
    ByteLu = MyReadI2C(); //Lecture poids forts
    AckI2C(); //GENERE UN Acknowledge sur le bus	
    Val_Lue = ByteLu << 8;
    ByteLu = MyReadI2C(); //Lecture poids faibles
    AckI2C(); //GENERE UN Acknowledge sur le bus	
    Val_Lue = Val_Lue | ByteLu;

    ByteLu = MyReadI2C(); //Lecture configuration bits
    MyNotAckI2C(); //Send Not Ack
    MyStopI2C(); //Send Stop Condition	
    return Val_Lue;

//    Val_Lue = Val_Lue * 10; //Rattrapage pont diviseur
//    ValenVolt = Val_Lue / 1000;
//    ValenDiziemeDeVolt = (Val_Lue - (ValenVolt * 1000)) / 10;
//    VAL_Volt_VirguleVolt = (ValenVolt << 8) + ValenDiziemeDeVolt;
//    return VAL_Volt_VirguleVolt;
}

unsigned int LectureTensionBatterie(void) {
    unsigned int Val_Lue, FlagWaitRDY;
    unsigned char ByteLu;
    //	unsigned int tempo;


    MyStartI2C(); //Generate Start condition
    MyWriteI2C(MCP342X_DEFAULT_ADDRESS << 1); //Ecriture
    MyWriteI2C(MCP342X_CHANNEL_2 | MCP342X_SIZE_12BIT |
            MCP342X_GAIN_1X | MCP342X_MODE_ONESHOT | MCP342X_RDY);
    MyStopI2C(); //Send Stop Condition	

    MyStartI2C(); //Generate Start condition
    MyWriteI2C((MCP342X_DEFAULT_ADDRESS << 1) + 1); //Lecture
    ByteLu = MyReadI2C(); //Lecture poids forts
    AckI2C(); //GENERE UN Acknowledge sur le bus	
    Val_Lue = ByteLu << 8;
    ByteLu = MyReadI2C(); //Lecture poids faibles
    AckI2C(); //GENERE UN Acknowledge sur le bus	
    Val_Lue = Val_Lue | ByteLu;

    FlagWaitRDY = 1;
    while (FlagWaitRDY) {
        ByteLu = MyReadI2C(); //Lecture configuration bits
        if (!(ByteLu & MCP342X_RDY)) {
            //Conv termine
            FlagWaitRDY = 0;
            MyNotAckI2C(); //Send Not Ack
            MyStopI2C(); //Send Stop Condition	
        } else {
            AckI2C(); //Pour pouvoir relire le registre conf bits	
        }
    }

    return Val_Lue;

}

unsigned int LectureTensionPower(void) {
    unsigned int Val_Lue, FlagWaitRDY;
    unsigned char ByteLu;


    MyStartI2C(); //Generate Start condition
    MyWriteI2C(MCP342X_DEFAULT_ADDRESS << 1); //Ecriture
    MyWriteI2C(MCP342X_CHANNEL_1 | MCP342X_SIZE_12BIT |
            MCP342X_GAIN_1X | MCP342X_MODE_ONESHOT | MCP342X_RDY);
    MyStopI2C(); //Send Stop Condition

    MyStartI2C(); //Generate Start condition
    MyWriteI2C((MCP342X_DEFAULT_ADDRESS << 1) + 1); //Lecture
    ByteLu = MyReadI2C(); //Lecture poids forts
    AckI2C(); //GENERE UN Acknowledge sur le bus	
    Val_Lue = ByteLu << 8;
    ByteLu = MyReadI2C(); //Lecture poids faibles	
    AckI2C(); //GENERE UN Acknowledge sur le bus	
    Val_Lue = Val_Lue | ByteLu;

    FlagWaitRDY = 1;
    while (FlagWaitRDY) {
        ByteLu = MyReadI2C(); //Lecture configuration bits
        if (!(ByteLu & MCP342X_RDY)) {
            //Conv termine
            FlagWaitRDY = 0;
            MyNotAckI2C(); //Send Not Ack
            MyStopI2C(); //Send Stop Condition	
        } else {
            AckI2C(); //Pour pouvoir relire le registre conf bits	
        }

    }

    return Val_Lue;

}





//unsigned int RecupereResultConvMCP2436 (void)
//{
//	unsigned int Val_Lue, FlagWaitRDY;
//	unsigned char ByteLu;
//	
//Supp =1;
//	MyStartI2C();									//Generate Start condition
//	MyWriteI2C((MCP342X_DEFAULT_ADDRESS << 1) + 1);	//Lecture
//	ByteLu = MyReadI2C();			//Lecture poids forts
//	AckI2C();				//GENERE UN Acknowledge sur le bus	
//	Val_Lue = ByteLu << 8;
//	ByteLu = MyReadI2C();			//Lecture poids faibles
//	AckI2C();				//GENERE UN Acknowledge sur le bus	
//	Val_Lue = Val_Lue | ByteLu;
//	
//	while ( FlagWaitRDY )
//	{		
//		ByteLu = MyReadI2C();		//Lecture configuration bits
//		if ( ! (ByteLu & MCP342X_RDY ))
//		{
//		//Conv termine
//			FlagWaitRDY = 0;
//			MyNotAckI2C();					//Send Not Ack
//			MyStopI2C();						//Send Stop Condition	
//		}
//		else
//		{	
//			AckI2C();				//Pour pouvoir relire le registre conf bits	
//		}
//	}
//Supp =0;
//	return Val_Lue;	
//}