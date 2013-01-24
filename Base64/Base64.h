// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BASE64_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BASE64_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once

#ifdef BASE64_EXPORTS
#define BASE64_API __declspec(dllexport)
#else
#define BASE64_API __declspec(dllimport)
#endif

//lookup array used by both base64 encoder & decoder to get base64 chars as defined by PEM standard
static const char* BASE64_LOOKUP_ARRAY = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

BASE64_API void toBase64(unsigned char *in, size_t size, unsigned char *out);
BASE64_API void decodeBase64(unsigned char* in, size_t size, unsigned char* out, size_t* outBufferLen);