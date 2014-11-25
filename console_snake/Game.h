#pragma once
#include<fstream>
#include <iostream>
#include <Windows.h>
#include "Snake.h"
using namespace std;

class CGame
{
	enum Difficulty {easy, medium, hard, extreme};
	Difficulty dif_lvl;
	COORD goverpos;
public:
	void SetDifficulty();
	void ShowHighscore();
	bool SetHighscore(int score, Difficulty dif);
	void GameOver(int score);
	void Play();
	int Menu();
	CGame();
};