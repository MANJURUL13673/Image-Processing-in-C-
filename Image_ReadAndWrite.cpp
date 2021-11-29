// Image Processing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//#define _CRT_SECURE_NO_WARNINGS
using namespace std;

int main()
{
	FILE *streamIn = fopen("D:/Learning from Udemy/Image Processing/1 - DATA/cameraman.bmp", "rb");
	FILE *streamOut = fopen("D:/Learning from Udemy/Image Processing/1 - RESULT/cameraman_copy.bmp", "wb");

	if (streamIn == (FILE*)0)
	{
		cout << "File can not able to open!!!" << endl;
	}
    
	unsigned char header[54];
	unsigned char colorTable[1024];
	for (int i = 0; i < 54; i++)
	{
		header[i] = getc(streamIn);
	}
	int width = *(int *)&header[18];
	int height = *(int *)&header[22];
	int bitDepth = *(int *)&header[28];

	if (bitDepth <= 8)
	{
		fread(colorTable, sizeof(unsigned char), 1024, streamIn);
	}
	fwrite(header, sizeof(unsigned char), 54, streamOut);
	unsigned char *buf = new unsigned char[height * width];
	fread(buf, sizeof(unsigned char), height * width, streamIn);
	
	if (bitDepth <= 8)
	{
		fwrite(colorTable, sizeof(unsigned char), 1024, streamOut);
	}
	fwrite(buf, sizeof(unsigned char), height * width, streamOut);
	fclose(streamIn);
	fclose(streamOut);
	delete[] buf;

	cout << "Success!!!!" << endl;
	cout << "Width: " << width << endl;
	cout << "Heigh: " << height << endl;
	//cout << bitDepth << endl;
}

