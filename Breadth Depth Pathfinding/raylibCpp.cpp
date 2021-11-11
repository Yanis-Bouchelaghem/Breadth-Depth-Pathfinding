#include "raylibCpp.h"
#include <assert.h>
void raycpp::DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color)
{
	assert(pos.GetX() >= 0 && pos.GetY() >= 0 &&
		   pos.GetX() < GetScreenWidth() && pos.GetY() < GetScreenHeight()); //If assertion triggers : Trying to draw outside of the screen
	DrawRectangle(pos.GetX(),pos.GetY(),widthHeight.GetX(),widthHeight.GetY(),color);
}

void raycpp::DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThick, Color color)
{
	assert(pos.GetX() >= 0 && pos.GetY() >= 0 &&
		pos.GetX() < GetScreenWidth() && pos.GetY() < GetScreenHeight()); //If assertion triggers : Trying to draw outside of the screen
	assert(lineThick > 0); //If assertion triggers : line thickness is less than 1
	DrawRectangleLinesEx({(float)pos.GetX(),(float)pos.GetY(), (float)widthHeight.GetX(), (float)widthHeight.GetY()}, lineThick, color);
}

void raycpp::DrawCircle(Vec2<int> center, int radius, Color color)
{
	assert(center.GetX() - radius >= 0 &&
		   center.GetY() - radius >= 0 &&
		   center.GetX() + radius < GetScreenWidth() &&
		   center.GetY() + radius < GetScreenHeight());//If assertion triggers: trying to draw outside of screen
	DrawCircle(center.GetX(), center.GetY(), (float)radius, color);
}

void raycpp::DrawRing(Vec2<int> center, int innerRadius, int outerRadius, float startAngle, float endAngle, int segments, Color color)
{
	assert(center.GetX() - outerRadius >= 0 &&
		center.GetY() - outerRadius >= 0 &&
		center.GetX() + outerRadius < GetScreenWidth() &&
		center.GetY() + outerRadius < GetScreenHeight());//If assertion triggers: trying to draw outside of screen
	DrawRing({(float)center.GetX(),(float)center.GetY()}, (float)innerRadius, (float)outerRadius, startAngle, endAngle, segments, color);
}

void raycpp::DrawText(const std::string& text, Vec2<int> pos, int fontSize, Color color)
{
	DrawText(text.c_str(), pos.GetX(), pos.GetY(), fontSize, color);
}
