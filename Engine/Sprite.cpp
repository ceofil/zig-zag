#include "Sprite.h"

void LoadSprite(Sprite * sprite, Color* surface, const char * filename, unsigned int width, unsigned int height, Color key)
{
	LoadBmp(filename, surface);
	sprite->width = width;
	sprite->heigth = height;
	sprite->key = key;
	sprite->surface = surface;
}

void DrawSprite(Sprite* sprite, int xoff, int yoff, Graphics& gfx)
{
	for (int y = 0; y < sprite->heigth; y++)
	{
		for (int x = 0; x < sprite->width; x++)
		{
			Color c = sprite->surface[x + y * sprite->width];
			if (c.GetR() != sprite->key.GetR() || c.GetG() != sprite->key.GetB() || c.GetB() != sprite->key.GetB())
			{
				gfx.PutPixel(x + xoff, y + yoff, c);
			}
		}
	}
}
