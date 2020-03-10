#include "TETRIS.h"
#include <time.h> 
#include <stdlib.h>

Vector2::Vector2(int ax, int ay) 
{ 
	x = ax;
	y = ay; 
};

Vector2 polygonType[6][4][4] =
{
	// ¦£
	{
			{{-1,-1},{-1,+0},{+0,+0},{+1,+0} },
			{{-1,+1},{+0,+1},{+0,+0},{+0,-1} },
			{{+1,+0},{+1,-1},{+0,-1},{-1,-1} },
			{{+0,-1},{-1,-1},{-1,+0},{-1,+1} }
	},
	// ¦¤
	{
			{{-1,-1},{-1,+0},{+0,-1},{+1,-1} },
			{{+0,+1},{-1,-1},{-1,+0},{-1,+1} },
			{{+1,+0},{+1,-1},{+0,+0},{-1,+0} },
			{{-1,-1},{+0,+1},{+0,+0},{+0,-1} }
	},
	// ¦¢
	{
			{{+1,-1},{+0,-1},{-1,-1},{-2,-1} },
			{{-1,-2},{-1,-1},{-1,+0},{-1,+1} },
			{{+0,-1},{-1,-1},{-2,-1},{-3,-1} },
			{{-1,-3},{-1,-2},{-1,-1},{-1,+0} }
	},
	// ¤±
	{
			{{+0,-1},{+0,+0},{+1,+0},{+1,-1} },
			{{+0,-1},{+0,+0},{+1,+0},{+1,-1} },
			{{+0,-1},{+0,+0},{+1,+0},{+1,-1} },
			{{+0,-1},{+0,+0},{+1,+0},{+1,-1} },
	},
	// 
	{
			{{+1,-1},{+0,-1},{+0,+0},{-1,+0} },
			{{+0,+1},{+0,+0},{-1,+0},{-1,-1} },
			{{+1,-1},{+0,-1},{+0,+0},{-1,+0} },
			{{+0,+1},{+0,+0},{-1,+0},{-1,-1} }
	},
	{
			{{-1,-1},{+0,-1},{+0,+0},{+1,+0} },
			{{+0,-1},{+0,+0},{-1,+0},{-1,+1} },
			{{-1,-1},{+0,-1},{+0,+0},{+1,+0} },
			{{+0,-1},{+0,+0},{-1,+0},{-1,+1} }
	}

};

int board[20][12] =
{
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};

void SetBoard(int y, int x,int n)
{
	if (y < 0 || y >= 20 || x < 0 || x >12)
		return;

	board[y][x] = n;
}

int GetBoard(int y, int x)
{
	//if (y < 0 || y >= 20 || x < 0 || x >12)
	//	return -1;

	return board[y][x];
}

Vector2 GetPolygon(int polygon, int angle, int n)
{
	return polygonType[polygon][angle][n];
}

void DownBlocks(int n)
{
	for (int r = n; r >= 1; r--)
		for (int c = 1; c < 11; c++)
			board[r][c] = board[r - 1][c];
}

bool CanMove(int x, int y, int polygon, int angle)
{
	for (int i = 0; i < 4; i++)
	{
		int ax = x + GetPolygon(polygon, angle, i).x;
		int ay = y + GetPolygon(polygon, angle, i).y;
		if (GetBoard(ay,ax) != 0)
			return false;
	}
	return true;
}

void SetBlock(int x,int y, int polygon, int angle)
{
	for (int i = 0; i < 4; i++)
	{
		int ax = x + GetPolygon(polygon, angle, i).x;
		int ay = y + GetPolygon(polygon, angle, i).y;
		SetBoard(ay, ax, polygon + 2);
	}

	for (int r = 1; r < 19; r++)
	{
		int check = r;
		for (int c = 1; c < 11; c++)
			if (GetBoard(r, c) == 0)
				check = 0;
		if (check != 0)
			DownBlocks(check);
	}
}

int RandomRange(int a, int b)
{
	int iTime = time(0);
	srand(iTime);

	if (b - a <= 0)
		return 0;

	return a + rand() % (b - a);
}

COLORREF GetColor(int n)
{
	switch (n)
	{
	case 1:
		return RGB(255, 255, 255);
	case 2:
		return RGB(255, 0, 0);
	case 3:
		return RGB(0, 0, 255);
	case 4:
		return RGB(0, 255, 0);
	case 5:
		return RGB(255, 255, 0);
	case 6:
		return RGB(0, 255, 255);
	case 7:
		return RGB(255, 0, 255);
	default :
		return RGB(255, 255, 255);
	}
}