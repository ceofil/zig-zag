#pragma once
#include "Graphics.h"
#include <d3d9.h>

struct BitmapFileHeader
{
	unsigned int fileSize;
	unsigned short reserved1, reserved2;
	unsigned int offsetToPixelData;
};

struct BitmapInfoHeader 
{
	unsigned int headerSize;
	int width, height;
	unsigned short int planes;
	unsigned short int bits;
	unsigned int compression;
	unsigned int imagesize;
	int xresolution, yresolution;
	unsigned int ncolours;
	unsigned int importcolours;
};

struct Pixel24
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

void LoadBmp( const char* filename,  Color* surface);

void DrawSurface(int xoff, int yoff, int width, int height, const Color* surface, Graphics& gfx);