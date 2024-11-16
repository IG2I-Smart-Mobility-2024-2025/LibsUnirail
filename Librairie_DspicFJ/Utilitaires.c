
#include "Utilitaires.h"


////////////////////////////////////////////
// programme de convertion ascii vers hexa
////////////////////////////////////////////

unsigned char ascii_to_hexa(unsigned char x) {
    if (x <= '9')
        x &= 0x0f;
    else
        x = (x & 0x0f) + 9;
    return (x);
}

////////////////////////////////////////////
// programme de convertion hexa vers ascii
////////////////////////////////////////////

unsigned char hexa_to_ascii(unsigned char x)
{
	if (x < 10)
		x += 0x30;
	else
		x = x + ('A' - 0x0a);
	return(x);
}

////////////////////////////////////////////
// programme de convertion 2 octets ascii vers hexa
////////////////////////////////////////////

unsigned char two_bytes_ascii_to_hexa(unsigned char a,unsigned char b)
{
	//uint8_t temp_uint8;
	unsigned char temp_uint8;
	
	temp_uint8 = ascii_to_hexa(a);
	temp_uint8 = (temp_uint8 << 4) + ascii_to_hexa(b);
	return temp_uint8;
}