#include "Bitmap.h"
#include <stdio.h>
#include <assert.h>

void LoadBmp(const char * filename, Color * surface)
{
	FILE* bmpFile = fopen( filename, "rb" );
	char signature[ 2 ];
	fread( signature, sizeof(char), 2, bmpFile );
	assert(signature[ 0 ] == 'B' && signature[ 1 ] == 'M');

	BitmapFileHeader fileHeader;
	fread( &fileHeader, sizeof( fileHeader ), 1, bmpFile );

	BitmapInfoHeader infoHeader;
	fread( &infoHeader, sizeof( infoHeader ), 1, bmpFile );

	fseek(bmpFile, fileHeader.offsetToPixelData, SEEK_SET);

	int nPixels = infoHeader.width * infoHeader.height;
	int nPaddingByresPerRow = 4 - ( ( infoHeader.width * 3 ) % 4 );
	for (int y = infoHeader.height - 1; y >= 0; y--)
	{
		for (int x = 0; x < infoHeader.width; x++)
		{
			Pixel24 pixel;
			fread(&pixel, sizeof(pixel), 1, bmpFile);
			surface[ x + y * infoHeader.width ] = Color(pixel.red, pixel.green, pixel.blue);
		}
		fseek(bmpFile, nPaddingByresPerRow, SEEK_CUR);
	}





	fclose( bmpFile );
}

void DrawSurface(int xoff, int yoff, int width, int height, const Color * surface, Graphics& gfx)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			gfx.PutPixel(x + xoff, y + yoff, surface[x + y * width]);
		}
	}
}
