#pragma once
#include <random>
#include "Graphics.h"
#include "Vec2.h"
#include "Ball.h"
class Path
{
public:
	Path() = default;
	Path( int& score, int& highScore, float& speed, Vec2 cornerDir, Ball& ball );
	void Reset(Ball& ball);
	~Path();
	void Draw( Graphics& gfx );
	void DrawBlock(Vec2 A, Vec2 B, float width, Color c, Graphics& gfx );
	void Update( float dt);
	bool ContainsBall(float xBall);

private:
	int& score;
	int& highScore;
	float& speed;

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
	Corner* currBlock = nullptr;
	void AddCorner(Vec2 pos);
	void DeleteLastCorner();
	void SpawnCorner();
	void SetCurrBlock();
	

private:
	static constexpr float width = 50.0f;
	static constexpr int wallHeight = 75;
	Vec2 cornerDir;
	float perspective;
	Vec2 startingCornerDir;

private:
	Color pathColor = Color(0,165,255);
	Color wallsColorRight = Color(0,85,165);
	Color wallsColorLeft = Color(0, 105, 195);
	static constexpr int yCenter = Graphics::ScreenHeight / 2;

private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> lengthRange;

private:
	static constexpr float startingBlockWidth = 150.0f;
	static constexpr float startingBlockLength = 150.0f;
	Vec2 startingBlockTopLeft;
	Vec2 startingBlockTopRight;
	Vec2 startingBlockBottomLeft;
	Vec2 startingBlockBottomRight;
	void DrawStartingBlock(Graphics& gfx);
	void SetStartingBlock(Vec2 cornerDir);
};

