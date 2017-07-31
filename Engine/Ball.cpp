#include "Ball.h"

Ball::Ball(Vec2 pos, float& speed)
	:
	pos(pos),
	speed(speed)
{
	this->pos.y -= radius;
}

void Ball::Draw(Graphics & gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(Keyboard & kbd, float dt)
{
	pos += dir * speed * dt;
	KeepInsideScreen();

	// change dirrection 
	if (!kbd.KeyIsEmpty())
	{
		const auto e = kbd.ReadKey();
		if (e.IsPress())
		{
			dir = dir * -1.0f;  
		}
	}
}

float Ball::GetX() const
{
	return pos.x;
}

void Ball::SetX(float x)
{
	pos.x = x;
}

void Ball::SetDirToRight()
{
	if(dir.x < 0.0f)
	{
		dir.x *= -1.0f;
	}
}

void Ball::KeepInsideScreen()
{	
	if (pos.x < radius)
	{
		pos.x = radius;
	}
	if (pos.x >= float(Graphics::ScreenWidth) - radius)
	{
		pos.x = float(Graphics::ScreenWidth) - radius - 1.0f;
	}
}
