#include "Path.h"

Path::Path(float speed)
	:
	first( new Corner(nullptr, nullptr, Graphics::GetCenter()) ),
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
	gfx.DrawCircle(last->pos, 10.0f, Colors::Red);
}

void Path::Update(float dt)
{
	Corner* ptr = first;
	while (ptr)
	{
		ptr->pos.y += dt * speed * perspective;
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
