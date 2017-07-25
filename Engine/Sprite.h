#pragma once
#include "Bitmap.h"

struct Sprite
{
	unsigned int width;
	unsigned int heigth;
	Color key;
	Color* surface;
};
void LoadSprite(Sprite * sprite, Color* surface, const char * filename, unsigned int width, unsigned int height, Color key);
void DrawSprite(Sprite* sprite, int xoff, int yoff, Graphics& gfx);