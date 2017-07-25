#pragma once
#include <random>
#include "Graphics.h"
#include "Vec2.h"

class Path
{
public:
	Path() = default;
	void Draw(Graphics& gfx);
private:


private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> lenghtRange;
};