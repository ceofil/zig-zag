#pragma once
#include <random>
#include "Graphics.h"
#include "Vec2.h"

class Path
{
public:
	Path() = default;
	Path( float speed );
	~Path();
	void Draw( Graphics& gfx );
	void DrawBlock(Vec2 A, Vec2 B, float width, Color c, Graphics& gfx );
	void Update( float dt, int& score );

private:
	struct Corner
	{
		Corner() = default;
		Corner(Corner* previous, Corner* next, Vec2 pos);
		Corner* previous;
		Corner* next;
		Vec2 pos;
	};

private:
	Corner* first = nullptr;
	Corner* last = nullptr;
	void AddCorner(Vec2 pos);
	void DeleteLastCorner();
	void SpawnCorner();

private:
	static constexpr float width = 50.0f;
	float speed;
	Vec2 cornerDir = Vec2(2.0f,-1.0f).GetNormalized(); 
	float perspective = -cornerDir.y / cornerDir.x;

private:
	Color pathColor = Color(255,165,0);
	Color wallsColor = Color(175, 85, 0);

private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> lengthRange;
};

