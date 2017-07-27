#include "Ball.h"

Ball::Ball(Vec2 pos, float speed)
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
