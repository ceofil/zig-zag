#include "Path.h"
#include <algorithm>

Path::Path(int&score,int&highScore,float speed)
	:
	score(score),
	highScore(highScore),
	first(new Corner(nullptr, nullptr, Vec2(float(Graphics::ScreenWidth / 2),float(Graphics::ScreenHeight)))),
	last(first),
	speed(speed),
	rng(rd()),
	lengthRange(20,200)
{
	SpawnCorner();
	SpawnCorner();
	SpawnCorner();
	SpawnCorner();
	SpawnCorner();
	SpawnCorner();
	SpawnCorner();
	SpawnCorner();
	SpawnCorner();
	SpawnCorner();
	SpawnCorner();
	SetCurrBlock();
}

Path::~Path()
{
	Corner* ptr = first;
	while(ptr)
	{
		Corner* nxt = ptr->next;
		delete ptr;
		ptr = nxt;
	}
}

void Path::Draw(Graphics & gfx)
{
	Corner* ptr = first;
	while(ptr->next)
	{
		DrawBlock(ptr->pos, ptr->next->pos, width, pathColor, gfx);
		ptr = ptr->next;
	}

	//test 
	gfx.DrawParallelogram(currBlock->pos, currBlock->next->pos, width, Color(15,180,255));
}

void Path::DrawBlock(Vec2 topLeft, Vec2 bottomLeft, float width, Color c, Graphics & gfx)
{
	Vec2 A = topLeft;
	Vec2 B = bottomLeft;

	float dx = B.x - A.x;
	float dy = B.y - A.y;

	if (std::abs(dy) > std::abs(dx))
	{
		float m = dx / dy;
		float b = A.x - m * A.y;

		int y1 = int(std::min(A.y, B.y));
		int y2 = int(std::max(A.y, B.y));

		for (int y = y1; y <= y2; y++)
		{
			int x = int(m * y + b + 0.5f);
			if (gfx.insideScreen(x, y))
			{
				gfx.DrawHorizontalLine(y, x, x + width, c);
				if (dx > 0)
				{
					gfx.DrawFadedVerticalLine(x, y, y + 100, wallsColorLeft);
				}
				else
				{
					gfx.DrawFadedVerticalLine(x + width, y, y + 100, wallsColorRight);
				}
			}

		}
	}
	else
	{
		float m = dy / dx;
		float b = A.y - m * A.x;

		int x1 = int(std::min(A.x, B.x));
		int x2 = int(std::max(A.x, B.x));

		for (int x = x1; x <= x2; x++)
		{
			int y = int(m * x + b + 0.5f);
			if (gfx.insideScreen(x, y))
			{
				gfx.DrawHorizontalLine(y, x, x + width, c);
				if (dx > 0)
				{
					gfx.DrawFadedVerticalLine(x, y, y + 100, wallsColorLeft);
				}
				else
				{
					gfx.DrawFadedVerticalLine(x + width, y, y + 100, wallsColorRight);
				}
			}
		}
	}
}

void Path::Update(float dt)
{
	Corner* ptr = first;
	while (ptr)
	{
		float delta = dt * speed * perspective;
		ptr->pos.y += delta;
		ptr = ptr->next;
	}
	if (currBlock->pos.y > yCenter)
	{
		score++;
		if (score > highScore)
		{
			highScore = score;
		}
		currBlock = currBlock->previous;
	}

	if (last->previous->pos.y > Graphics::ScreenHeight )
	{
		DeleteLastCorner();
	}
	if (first->next->pos.y > 0.0f)
	{
		SpawnCorner();
	}
}

void Path::AddCorner(Vec2 pos)
{
	first = new Corner(nullptr, first, pos);
	first->next->previous = first;
}

void Path::DeleteLastCorner()
{	
	Corner* oldLast = last;
	last = last->previous;
	last->next = nullptr;
	delete oldLast;
}

void Path::SpawnCorner()
{
	Vec2 nextCornerPos = { -1.0f,-1.0f };

	while ( nextCornerPos.x < 0.0f || nextCornerPos.x >= Graphics::ScreenWidth - width - 1 )
	{
		float length = float(lengthRange(rng));
		nextCornerPos = first->pos + cornerDir * length;
	}
	cornerDir.x *= -1.0f;
	AddCorner(nextCornerPos);
}

void Path::SetCurrBlock()
{
	Corner* ptr = first;
	while (ptr)
	{
		if (ptr->pos.y > yCenter )
		{
			currBlock = ptr->previous;
			break;
		}
		ptr = ptr->next;
	}
}

bool Path::ContainsBall(float xBall)
{
	Vec2 A = currBlock->pos;
	Vec2 B = currBlock->next->pos;
	
	float dx = B.x - A.x;
	float dy = B.y - A.y;

	float m = dx / dy;
	float b = A.x - m * A.y;

	float x = m * yCenter + b + 0.5f;


	return xBall > x && xBall < x + width;
}

Path::Corner::Corner(Corner * previous, Corner * next, Vec2 pos)
	:
	previous(previous),
	next(next),
	pos(pos)
{
}
