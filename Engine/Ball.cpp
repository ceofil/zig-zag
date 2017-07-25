#include "Ball.h"

Ball::Ball(Vec2 pos, float speed)
	:
	pos(pos),
	speed(speed)
{
}

void Ball::Draw(Graphics & gfx) const
{
	gfx.DrawCircle(pos, radius, Colors::Yellow);
}

void Ball::Update(Keyboard & kbd, float dt)
{
	pos += dir * speed * dt;
	

	// change dirrection on SPACE press
	if (!kbd.KeyIsEmpty())
	{
		const auto e = kbd.ReadKey();
		if (e.IsRelease())
		{
			if (e.GetCode() == VK_SPACE)
			{
				dir = dir * -1.0f;  
			}
		}
	}
}
