#include "Line.h"
#include <algorithm>

Line::Line(Vec2 point1, Vec2 point2)
	:
	p1(point1),
	p2(point2)
{
}

bool Line::orientation(Vec2 A, Vec2 B, Vec2 C) const
{
	return ( C.y - A.y ) * ( B.x - A.x ) > ( B.y - A.y ) * ( C.x - A.x );
}

bool Line::OverlappingWith_Line(Vec2 C, Vec2 D) const
{
	return orientation(p1,C,D) != orientation(p2,C,D) && orientation(p1,p2,C) != orientation(p1,p2,D);
}

bool Line::OverlappingWith_Rect(RectF rect) const
{
	Vec2 topLeft = { rect.left, rect.top };
	Vec2 topRight = { rect.right, rect.top };
	Vec2 bottomLeft = { rect.left, rect.bottom };
	Vec2 bottomRight = { rect.right, rect.bottom };

	return
		OverlappingWith_Line(topLeft, topRight) ||
		OverlappingWith_Line(topRight, bottomRight) ||
		OverlappingWith_Line(bottomRight, bottomLeft) ||
		OverlappingWith_Line(bottomLeft, topLeft);
}
