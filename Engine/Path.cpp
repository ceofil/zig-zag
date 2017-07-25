#include "Path.h"

Path::Path(float speed)
	:
	first(new Corner(nullptr, nullptr, Vec2(float(Graphics::ScreenWidth / 2),float(Graphics::ScreenHeight)))),
	last(first),
	speed(speed),
	rng(rd()),
	lengthRange(20,200)
{
	SpawnCorner();
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
		gfx.DrawParallelogram(ptr->pos, ptr->next->pos, width, Colors::Gray);
		ptr = ptr->next;
	}
}

void Path::Update(float dt, int& score)
{
	Corner* ptr = first;
	while (ptr)
	{
		float delta = dt * speed * perspective;
		if (ptr->pos.y < Graphics::ScreenHeight / 2 && ptr->pos.y + delta > Graphics::ScreenHeight / 2)
		{
			score++;
		}

		ptr->pos.y += delta;
		ptr = ptr->next;
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

	while ( nextCornerPos.x < 0.0f || nextCornerPos.x >= Graphics::ScreenWidth - width + 1 )
	{
		float length = float(lengthRange(rng));
		nextCornerPos = first->pos + cornerDir * length;
	}
	cornerDir.x *= -1.0f;
	AddCorner(nextCornerPos);
}

Path::Corner::Corner(Corner * previous, Corner * next, Vec2 pos)
	:
	previous(previous),
	next(next),
	pos(pos)
{
}
