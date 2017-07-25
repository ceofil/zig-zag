#pragma once
#include "Vec2.h"
#include "RectF.h"

class Line
{
public:
	Line() = default;
	Line(Vec2 point1, Vec2 point2);
	bool orientation(Vec2 A, Vec2 B, Vec2 C) const;
	bool OverlappingWith_Line(Vec2 C, Vec2 D) const;
	bool OverlappingWith_Rect(RectF rect) const;
public:
	Vec2 p1;
	Vec2 p2;
};