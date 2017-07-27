#pragma once
#include <random>
#include "Graphics.h"
#include "Vec2.h"

class Path
{
public:
	Path() = default;
	Path( int& score, int& highScore, float speed );
	~Path();
	void Draw( Graphics& gfx );
	void DrawBlock(Vec2 A, Vec2 B, float width, Color c, Graphics& gfx );
	void Update( float dt);

private:
	int& score;
	int& highScore;

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
	Color pathColor = Color(0,165,255);
	Color wallsColorRight = Color(0,85,165);
	Color wallsColorLeft = Color(0, 105, 195);

private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> lengthRange;
};

