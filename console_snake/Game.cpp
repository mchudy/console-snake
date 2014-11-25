#include "Game.h"
#include "Board.h"
#include <string>
#include <sstream>

CGame::CGame()
{
	goverpos.X = 60;
	goverpos.Y = 22;
	dif_lvl = medium;
}

void CGame::ShowHighscore() 
{
	cls();
	ifstream fhscore("highscore.snake");
	if(fhscore.is_open() == false)
		cerr << "Couldn't open the file";
	else 
	{
		fhscore.clear();
		fhscore.seekg(0, ios::beg);
		string buf;
		cout << "Your current highscores are:\n" ;
		cout << "\ton easy level: ";
		getline(fhscore, buf);
		cout << buf << endl;
		cout << "\ton medium level: ";
		getline(fhscore, buf);
		cout << buf << endl;
		cout <<"\ton hard level: ";
		getline(fhscore, buf);
		cout << buf << endl;
		cout <<"\ton extreme level: ";
		getline(fhscore, buf);
		cout << buf << endl;
		cout << "Press ENTER to go back... " ;
		fhscore.clear();
		fhscore.close();
	}
	cin.get();
}

bool CGame::SetHighscore(int score, Difficulty dif)
{
	bool new_hscore;
	//creates file if it doesn't exist 
	ofstream create("highscore.snake", ios::app);
	create <<"\n";
	create.close();
	//copying previous highscore file
	ifstream fhscore;
	fhscore.open("highscore.snake", ios::out);
	if(fhscore.is_open() == true)
	{
		fhscore.clear();
		fhscore.seekg(0, ios::beg);
		string temp[4];
		for(int i = 0; i < 4; i++)
		{
			getline(fhscore, temp[i]);
		}
		fhscore.close();
		//creating new highscore file
		ofstream ofhscore("highscore.snake", ios::trunc | ios::in);
		ofhscore.clear();
		if(score > atoi(temp[static_cast<int>(dif)].c_str()))
		{
			ostringstream ss;
			ss << score;
			temp[static_cast<int>(dif)] = ss.str();
			new_hscore = true;
		} else new_hscore = false;
		ofhscore.seekp(0, ios::beg);
		for(int i = 0; i < 4; i++)
		{
			ofhscore << temp[i] << '\n';
		}
		ofhscore.close();
	}
	else 
	{
		cls();
		SetColour(3);
		cerr << "Couldn't open the highscore file";
		cin.get();
	}
	return new_hscore;
}

void CGame::Play()
{
	CBoard *Board = new CBoard;
	Board->DrawBoard();
	delete Board;
	CSnake *Snake = new CSnake;
	//sets difficulty
	switch(dif_lvl)
	{
	case easy:
		CSnake::delay = 160;
		CSnake::multiplier = 1;
		break;
	case medium:
		CSnake::delay = 140;
		CSnake::multiplier = 1;
		break;
	case hard:
		CSnake::delay = 120;
		CSnake::multiplier = 0.9;
		break;
	case extreme:
		CSnake::delay = 100;
		CSnake::multiplier = 0.8;
		break;
	}
	while(Snake->Move() != 0)
	{
		if(GetAsyncKeyState(VK_UP) & 0x8000)
		{
			Snake->ChangeDirection(up);
		}
		else if(GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			Snake->ChangeDirection(down);
		}
		else if(GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			Snake->ChangeDirection(static_cast<Direction>(2));
		}
		else if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			Snake->ChangeDirection(static_cast<Direction>(3));
		}
		else if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break; 
	}
	int score = Snake->GetScore();
	delete Snake;
	GameOver(score);
}

void CGame::GameOver(int score)
{
	SetColour(2);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),goverpos);
	cout << "GAME OVER";
	SetColour(0);
	if(SetHighscore(score, dif_lvl) == true)
	{
		SetColour(2);
		COORD new_hscorepos;
		new_hscorepos.X = 19;
		new_hscorepos.Y = 22;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),new_hscorepos);
		cout << "NEW HIGHSCORE!";
		SetColour(0);
	}
	cin.get();
}

int CGame::Menu()
{
	cls();
	SetColour(3);
	int decision = 0;
	cout << "----------------------------------\n"
		<<  "               SNAKE              \n"
		<<  "----------------------------------\n"
		<< "1. NEW GAME\n"
		<< "2. HIGHSCORE\n"
		<< "3. DIFFICULTY\n"
		<< "0. EXIT\n"
		<< "----------------------------------\n"
		<< "----------------------------------\n";
	cin >> decision;
	cin.ignore();
	if (decision != 1 && decision != 2 && decision != 3) return 0; 
	else return decision;
}

void CGame::SetDifficulty()
{
	cls();
	SetColour(3);
	cout << "The current difficulty level is: ";
	switch(dif_lvl)
	{
		case easy: cout << "EASY\n";		break;
		case medium: cout << "MEDIUM\n";	break;
		case hard: cout << "HARD\n";		break;
		case extreme: cout << "EXTREME\n";	break;
	}
	int decision = -1;
	cout << "Choose level:\n\t0 - EASY\n\t1 - MEDIUM\n\t2 - HARD\n\t"
		<< "3 - EXTREME\n";
	while(decision < 0 || decision > 3)
	{
		cin >> decision;
	}
	switch(decision)
	{
		case 0: dif_lvl = easy;		break;
		case 1: dif_lvl = medium;	break;
		case 2: dif_lvl = hard;		break;
		case 3: dif_lvl = extreme;	break;
	}
}
