#ifndef _IMAGE_H
#define _IMAGE_H

#include "jpeglib.h"



#define TGA_RGB		 2		
#define TGA_A		 3		
#define TGA_RLE		10		

struct tImage
{
	int channels;			
	int sizeX;				
	int sizeY;				
	unsigned char *data;	
};

/** ����λͼ */
tImage *LoadBMP(const char *strFileName);

/** ����TGA�ļ� */
tImage *LoadTGA(const char *strFileName);

/** ����JPG�ļ� */
tImage *LoadJPG(const char *strFileName);

/** ����JPG�ļ� */
void DecodeJPG(jpeg_decompress_struct* cinfo, tImage *pImageData);


#endif
