#pragma once
#include <raylib.h>
#include <string>
#include "Vec2.h"


namespace raycpp
{
	void DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color);
	void DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThick, Color color);
	void DrawCircle(Vec2<int> center, int radius, Color color);
	void DrawRing(Vec2<int> center, int innerRadius, int outerRadius, float startAngle, float endAngle, int segments, Color color);//Draws a ring : angles in degrees, number of segments automatically calculated if given < 4
	void DrawText(const std::string& text, Vec2<int> pos, int fontSize, Color color);
}