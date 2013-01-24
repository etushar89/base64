// decoder.cpp : Defines the exported base64 decoder function for the DLL application.
//

#include "stdafx.h"
#include "Base64.h"

//base64 decoder helper function
inline char getIndex(char x){
	for(char i = 0; i < strlen(BASE64_LOOKUP_ARRAY); i++){
		if(x==BASE64_LOOKUP_ARRAY[i])
			return i;
	}
	return 0;
}

//base64 decoder
BASE64_API void decodeBase64(unsigned char* in, size_t size, unsigned char* out, size_t* outBufferLen){

	unsigned int stitchedBytes = 0;
	int padCnt = 0;
	size_t outLen = 0;

	//Each iteration decodes one block (4 bytes in a block)
	for(size_t i = 0; i < size; i++)
	{
		//First stitch all the bytes (3 bytes) together in a single buffer
		stitchedBytes = 0;

		//Stitch first byte in block
		stitchedBytes = getIndex(in[i]);
		stitchedBytes = stitchedBytes << 6;

		//Stitch second byte in block
		stitchedBytes |= getIndex(in[++i]);
		stitchedBytes = stitchedBytes << 6;

		//if third byte is '=' fourth byte will be '=' too
		if(in[i+1]=='=')
			padCnt=2;

		//Stitch third byte in block, if it's '=', 0 will be stitched
		stitchedBytes |= getIndex(in[++i]);
		stitchedBytes = stitchedBytes << 6;

		if(in[i+1]=='=')
			padCnt=1;

		//Stitch fourth byte in block, if it's '=' 0 will be stitched
		stitchedBytes |= getIndex(in[++i]);

		//get 3 bytes one by one from 24-bits stitched above into out chars
		out[outLen++] = (stitchedBytes >> 16) & 0xFF;

		//if there are 2 pad '=', output will have only 1 byte
		if(padCnt==2){
			*outBufferLen = outLen;
			return;
		}
		else{
			out[outLen++] = (stitchedBytes >> 8) & 0xFF;
			//if there is 1 pad '=', output will have only 2 bytes
			if(padCnt){
				*outBufferLen = outLen;
				return;
			}
			else
				//if there wasn't any '=', output will have 3 bytes
				out[outLen++] = (stitchedBytes) & 0xFF;
		}
	}
}
