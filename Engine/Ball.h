#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "Keyboard.h"
class Ball
{
public:
	Ball() = default;
	Ball(Vec2 pos, float speed);
	void Draw( Graphics& gfx ) const;
	void Update( Keyboard& kbd, float dt );
private:
	Vec2 pos;
	Vec2 dir = { 1.0f,0.0f };
	float speed;
public:
	static constexpr float radius = 7.0f;

};