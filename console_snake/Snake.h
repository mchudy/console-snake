#pragma once
#include <Windows.h>
#include <deque>
#include <ctime>
using namespace std;

extern void SetColour(int colour);

enum Direction{up, down, left, right};

class CSnake
{
	struct SPoint
	{
		COORD SCoord;
		Direction dir;
	};
	deque<SPoint> SPos;
	int length;
	COORD food;
	bool food_exists;
	void Draw();
	void DrawScore();
	COORD scorepos;
	bool WallCollision();
	bool BodyCollision();
	bool FoodCollision();
	void CreateFood();
	void EatFood();
public:
	static int delay;
	//indicates how delay is changed after increasing length of the snake
	static float multiplier;
	void ChangeDirection(Direction dir);
	int Move();
	int GetScore() { return length - 3; }
	CSnake();
};
