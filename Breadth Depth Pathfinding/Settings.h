#pragma once
#include "Vec2.h"
#include "raylibCpp.h"
namespace settings
{
	//Screen settings
	inline constexpr int screenWidth = 1200;
	inline constexpr int screenHeight = 800;
	inline constexpr int fps = 60;
	inline constexpr char title[] = "Pathfinding robot";
	
	//Board settings
	inline constexpr Vec2<int> widthHeight{11,9};
	inline constexpr Vec2<int> boardScreenPos{250,150};
	inline constexpr int cellRadius = 30;
	inline constexpr int padding = 5;
	inline constexpr Color emptyColor = GRAY;
	inline constexpr Color objectiveColor = RAYWHITE;
	inline constexpr Color wallColor = VIOLET;
	inline constexpr Color robotColor = GOLD;
	inline constexpr Color visitedColor = GREEN;
	inline constexpr Color targetedColor = RED;
	inline constexpr Color objectivePathColor = YELLOW;

}