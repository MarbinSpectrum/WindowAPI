#pragma once

#include "framework.h"
#include "resource.h"

class Vector2
{
public:
	int x;
	int y;
	Vector2(int ax, int ay);
};

void SetBoard(int y, int x, int n);
int GetBoard(int y, int x);
Vector2 GetPolygon(int type, int angle, int n);

void DownBlocks(int n);

bool CanMove(int x, int y, int polygon, int angle);
void SetBlock(int x, int y, int polygon, int angle);
int RandomRange(int a, int b);
COLORREF GetColor(int n);