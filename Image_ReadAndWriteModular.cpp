// Image Processing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define BMP_HEADER_SIZE				54
#define BMP_COLOR_TABLE_SIZE		1024
#define CUSTOM_IMG_SIZE				1024*1024
//#define _CRT_SECURE_NO_WARNINGS
using namespace std;

void imageReader(
	const char* imageName,
	int *_height,
	int *_width,
	int *_bitDepth,
	unsigned char *_header,
	unsigned char *_colorTable,
	unsigned char *_buf
);

void imageWriter(
	const char *imgName,
	unsigned char *header,
	unsigned char *colorTable,
	unsigned char *buf,
	int bitDepth
);

int main()
{
	int imgWidth, imgHeight, imgBitDepth;
	unsigned char *header = new unsigned char[BMP_HEADER_SIZE];
	unsigned char *colorTable = new unsigned char[BMP_COLOR_TABLE_SIZE];
	unsigned char *buf = new unsigned char[CUSTOM_IMG_SIZE];
	return 0;
}

void imageReader(
	const char* imageName,
	int *_height,
	int *_width,
	int *_bitDepth,
	unsigned char *_header,
	unsigned char *_colorTable,
	unsigned char *_buf
) {
	int i;
	FILE *streamIn;
	streamIn = fopen(imageName, "rb");
	if (streamIn == (FILE *)0)
	{
		cout << "Unable to open image!!!" << endl;
	}

	for (int i = 0; i < 54; i++)
	{
		_header[i] = getc(streamIn);
	}

	*_width = *(int *)&_header[18];
	*_height = *(int *)&_header[22];
	*_bitDepth = *(int *)&_header[28];

	if (*_bitDepth <= 8)
	{
		fread(_colorTable, sizeof(unsigned char), 1024, streamIn);
	}
	fread(_buf, sizeof(unsigned char), CUSTOM_IMG_SIZE, streamIn);

	fclose(streamIn);
}

void imageWriter(
	const char *imgName,
	unsigned char *header,
	unsigned char *colorTable,
	unsigned char *buf,
	int bitDepth
) {
	FILE *fo = fopen(imgName, "wb");
	fwrite(header, sizeof(unsigned char), 54, fo);
	if (bitDepth <= 8)
	{
		fwrite(colorTable, sizeof(unsigned char), 1024, fo);
	}
	fwrite(buf, sizeof(unsigned char), CUSTOM_IMG_SIZE, fo);
	
	fclose(fo);
}

