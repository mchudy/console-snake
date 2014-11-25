#pragma once
extern void cls();
extern void SetColour(int colour);

class CBoard
{
	static const short int BOARD_SIZE_X = 80;
	static const short int BOARD_SIZE_Y = 20;
public:
	void DrawBoard()
	{
		cls();
		SetColour(8);
		for(int i = 0; i < BOARD_SIZE_Y; i++)
		{
			cout << "#";
			if( i == 0 || i == BOARD_SIZE_Y - 1)
			{
				for(int j = 1; j < BOARD_SIZE_X - 1; j++)
				{
					cout << "#";
					if (j == BOARD_SIZE_X - 2) cout << endl; 
				}
			}
			else {
				for (int i = 0; i < BOARD_SIZE_X - 3; i++ ) 
				cout << " ";
			cout << "#\n"; 
			}
		}
	}

};
