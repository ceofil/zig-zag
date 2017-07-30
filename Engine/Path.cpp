#include "Path.h"
#include <algorithm>

Path::Path(int&score,int&highScore,float speed, Vec2 cornerDir, Ball& ball)
	:
	score(score),
	highScore(highScore),
	startingSpeed(speed),
	startingCornerDir(cornerDir.GetNormalized()),
	perspective(-cornerDir.y / cornerDir.x),
	rng(rd()),
	lengthRange(70,200)
{
	Reset(ball);
}

void Path::Reset(Ball& ball)
{
	speed = startingSpeed;
	cornerDir = startingCornerDir;

	//delete the current corners
	Corner* ptr = first;
	while (ptr)
	{
		Corner* nxt = ptr->next;
		delete ptr;
		ptr = nxt;
	}

	first = new Corner(nullptr, nullptr, Graphics::GetCenter());
	last = first;

	SetStartingBlock(this->cornerDir);

	//spawning another corner so there will be one below yCenter and one above, the one that is above will become currBlock
	SpawnCorner();
	SetCurrBlock();

	ball.SetX(float(Graphics::ScreenWidth/2) + width / 2.0f);
	ball.SetDirToRight();
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
	if (startingBlockTopLeft.y < float(Graphics::ScreenHeight))
	{
		DrawStartingBlock(gfx);
	}

	//highlight for the currBlock
	//gfx.DrawParallelogram(currBlock->pos, currBlock->next->pos, width, Color(15,180,255));
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
				gfx.DrawHorizontalLine(y, x, x + int(width), c);
				if (dx > 0)
				{
					gfx.DrawFadedVerticalLine(x, y, y + 100, wallsColorLeft);
				}
				else
				{
					gfx.DrawFadedVerticalLine(x + int(width), y, y + 100, wallsColorRight);
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
				gfx.DrawHorizontalLine(y, x, x + int(width), c);
				if (dx > 0)
				{
					gfx.DrawFadedVerticalLine(x, y, y + 100, wallsColorLeft);
				}
				else
				{
					gfx.DrawFadedVerticalLine(x + int(width), y, y + 100, wallsColorRight);
				}
			}
		}
	}
}

void Path::Update(float dt)
{
	float delta = dt * speed * perspective;


	if (startingBlockTopLeft.y < float(Graphics::ScreenHeight))
	{
		startingBlockTopLeft.y += delta;
		startingBlockBottomLeft.y += delta;
		startingBlockBottomRight.y += delta;
		startingBlockTopRight.y += delta;
	}

	Corner* ptr = first;
	while (ptr)
	{
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

	if (last->previous->pos.y > float(Graphics::ScreenHeight) )
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

void Path::DrawStartingBlock(Graphics & gfx)
{
	//path
	gfx.DrawTriangle(startingBlockTopLeft, startingBlockTopRight, startingBlockBottomLeft, pathColor);
	gfx.DrawTriangle(startingBlockTopLeft, startingBlockTopRight, startingBlockBottomRight, pathColor);
	gfx.DrawTriangle(startingBlockBottomLeft, startingBlockBottomRight, startingBlockTopLeft, pathColor);
	gfx.DrawTriangle(startingBlockBottomLeft, startingBlockBottomRight, startingBlockTopRight, pathColor);

	//shadow
	DrawBlock(startingBlockBottomLeft, startingBlockBottomRight, 0, wallsColorLeft, gfx);
	DrawBlock(startingBlockTopRight, startingBlockBottomRight, 0, wallsColorRight, gfx);
}

void Path::SetStartingBlock(Vec2 cornerDir)
{
	cornerDir.x *= -1.0f;
	Vec2 startingBlockDelta = cornerDir * startingBlockWidth * -1.0f + Vec2(0.5f, 0.5f);

	cornerDir.x *= -1.0f;
	startingBlockTopLeft = first->pos;
	first->pos -= cornerDir * (width * perspective + 0.5f);

	cornerDir.x *= -1.0f;
	startingBlockTopRight = startingBlockTopLeft + startingBlockDelta;

	cornerDir.x *= -1.0f;
	startingBlockBottomLeft = startingBlockTopLeft - cornerDir * startingBlockLength;
	startingBlockBottomRight = startingBlockBottomLeft + startingBlockDelta;
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
