// encoder.cpp : Defines the exported base64 encoder functions for the DLL application.
//

#include "stdafx.h"
#include "Base64.h"

//base64 encoder helper function
inline unsigned int getLookupIndex(unsigned int stitchedBytes, short byteIndex)
{
	unsigned int tmp = 0;

	switch(byteIndex){
	case 4:
		tmp = (stitchedBytes & 0xFF0000) >> 18;
		break;
	case 3:		
		tmp = (stitchedBytes & 0x03F000) >> 12;
		break;
	case 2:
		tmp = (stitchedBytes & 0x000FC0) >> 6;
		break;
	case 1:
		tmp = (stitchedBytes & 0x00003F);
		break;
	}
	return tmp;
}

//base64 encoder
BASE64_API void toBase64(unsigned char *in, size_t size, unsigned char *out)
{
	unsigned int stitchedBytes = 0;
	int i2 = 0;
	int outCharCnt = 2;
	size_t outLen = 0;

	//Each iteration encodes one block (usually 3 bytes in a block, if not last incomplete block)
	for(size_t i = 0; i < size; i++)
	{
		//If there is one byte in input block, there will be two characters in o/p
		outCharCnt = 2;

		//First stitch all the bytes (usually 3, if not last incomplete block)
		//together in a single buffer
		stitchedBytes = 0;

		//Stitch first leftmost byte in block
		stitchedBytes = in[i] << 16;

		//Stitch second byte if available in block
		if(i+1 < size)
		{
			stitchedBytes += in[++i] << 8;
			//If there are two bytes in input block, there will be three characters in o/p
			outCharCnt=3;
		}

		//Stitch third byte if available in block
		if(i+1 < size)
		{
			stitchedBytes += in[++i];
			//If there are three bytes in input block, there will be four characters in o/p
			outCharCnt=4;
		}

		i2 = 4;
		//Fill ouput buffer with encode chars
		while(outCharCnt)
		{
			out[outLen++] = BASE64_LOOKUP_ARRAY[getLookupIndex(stitchedBytes,i2)];
			outCharCnt--;
			i2--;
		}
	}

	int padCnt = (size%3) ? 3-(size%3) : 0;
	//Pad '=' if last block contained less than 3 bytes
	while(padCnt)
	{
		out[outLen++] = '=';
		padCnt--;
	}
}