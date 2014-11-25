#include "Snake.h"
#include <iostream>
using namespace std;

int CSnake::delay; 
float CSnake::multiplier;

CSnake::CSnake()
{
	length = 3;
	scorepos.X = 5;
	scorepos.Y = 22;
	food_exists = false;
	//sets random starting position
	srand(static_cast<unsigned int>(time(NULL)));
	SPos.resize(3);
	SPos[2].SCoord.X = rand()%71 + 5;
	SPos[2].SCoord.Y = rand()%11 + 5;
	//sets random starting direction
	ChangeDirection(static_cast<Direction>(rand()%4));
	SPos[1].dir = SPos[2].dir;
	SPos[0].dir = SPos[2].dir;
	//sets two next parts of snake
	switch(SPos[2].dir)
	{
	case up:
		SPos[1].SCoord.X = SPos[2].SCoord.X;
		SPos[1].SCoord.Y = SPos[2].SCoord.Y + 1;
		SPos[0].SCoord.X = SPos[2].SCoord.X;
		SPos[0].SCoord.Y = SPos[2].SCoord.Y + 2;
		break;
	case down:
		SPos[1].SCoord.X = SPos[2].SCoord.X;
		SPos[1].SCoord.Y = SPos[2].SCoord.Y - 1;
		SPos[0].SCoord.X = SPos[2].SCoord.X;
		SPos[0].SCoord.Y = SPos[2].SCoord.Y - 2;
		break;
	case 2: //left
		SPos[1].SCoord.X = SPos[2].SCoord.X + 1;
		SPos[1].SCoord.Y = SPos[2].SCoord.Y;
		SPos[0].SCoord.X = SPos[2].SCoord.X + 2;
		SPos[0].SCoord.Y = SPos[2].SCoord.Y;
		break;
	case 3: //right
		SPos[1].SCoord.X = SPos[2].SCoord.X - 1;
		SPos[1].SCoord.Y = SPos[2].SCoord.Y;
		SPos[0].SCoord.X = SPos[2].SCoord.X - 2;
		SPos[0].SCoord.Y = SPos[2].SCoord.Y;
		break;
	}
}

void CSnake::Draw()
{
	//draw snake
	SetColour(14);
	for(int i = 0; i < length; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SPos[i].SCoord);
		cout << "*";
	}
	Sleep(delay);
	SetColour(0); //black to make snake disappear
	for(int i = 0; i < length; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SPos[i].SCoord);
		cout << "*";
	}
}

int CSnake::Move()
{
	if(WallCollision() == true)
		return 0;
	if(BodyCollision() == true)
		return 0;
	if(FoodCollision() == true)
		EatFood();
	if(food_exists == false)
	{
		CreateFood();
		DrawScore();
	}
	//moves every point of snake
	for(int i = 0; i < length; i++)
	{
		switch(SPos[i].dir)
		{
		case up:
			SPos[i].SCoord.Y -= 1;
			break;
		case down:
			SPos[i].SCoord.Y += 1;
			break;
		case 2: //left
			SPos[i].SCoord.X -= 1;
			break;
		case 3: //right
			SPos[i].SCoord.X += 1;
			break;
		}
	}
	//changes points' directions for the next move
	for(int i = 0 ; i < length - 1; i++)
	{
		SPos[i].dir = SPos[i+1].dir; 
	}
	Draw();
	return 1;
}

void CSnake::ChangeDirection(Direction dir)
{
	SPos[length - 1].dir = dir;
}

bool CSnake::WallCollision()
{
	if(SPos[length-1].SCoord.X == 0 || SPos[length-1].SCoord.X == 78 ||
		SPos[length-1].SCoord.Y == 0 || SPos[length-1].SCoord.Y == 19)
		return true;
	else return false;
}

void CSnake::CreateFood()
{
	srand(static_cast<unsigned int>(time(NULL)));
	bool collision = true;
	while(collision == true)
	{
		collision = false;
		food.X = rand()%77 + 1;
		food.Y = rand()%18 + 1;
		//checks if the coordinates aren't the same as snake's
		for(int i = 0; i < length; i++)
		{
			if(SPos[i].SCoord.X == food.X && SPos[i].SCoord.Y == food.Y)
			{
				collision = true;
				break;
			}
		}
	}
	SetColour(2);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), food);
	cout << "@";
	food_exists = true;
}

bool CSnake::FoodCollision()
{
	for(int i = 0; i < length; i++)
	{
		if(SPos[i].SCoord.X == food.X && SPos[i].SCoord.Y == food.Y)
			return true;
	}
	return false;
}

void CSnake::EatFood()
{
	length++;
	delay *= multiplier;
	SPoint temp = SPos[0];
	switch(temp.dir)
	{
	case up:
		SPos.push_front(temp);
		SPos[0].SCoord.Y = temp.SCoord.Y + 1;
		break;
	case down:
		SPos.push_front(temp);
		SPos[0].SCoord.Y = temp.SCoord.Y - 1;
		break;
	case 2: //left
		SPos.push_front(temp);
		SPos[0].SCoord.X = temp.SCoord.X + 1;
		break;
	case 3: //right
		SPos.push_front(temp);
		SPos[0].SCoord.X = temp.SCoord.X - 1;
		break;
	}
	food_exists = false;
}

bool CSnake::BodyCollision()
{
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length; j++)
		{
			if( i != j &&
				SPos[i].SCoord.X == SPos[j].SCoord.X &&
				SPos[i].SCoord.Y == SPos[j].SCoord.Y)
				return true;
		}
	}
	return false;
}

void CSnake::DrawScore()
{
	SetColour(2);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), scorepos);
	cout << "Score: " << length - 3;
}
