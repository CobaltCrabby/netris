#pragma once
#include "mino.h"
#include "enum.h"

class Tetramino {
	Mino* minos[4];
	enum piece type;
	int rotation = 0;

	public:
		Tetramino(enum piece shape);
		void addMinos(Mino*** minoGrid, int gx, int gy);
		Mino* addToGrid(Mino*** minoGrid, enum color c, int x, int y, int gx, int gy);
		Mino** getMinos();
		enum piece getType();
		int getRotation();
		void setRotation(int num);
};