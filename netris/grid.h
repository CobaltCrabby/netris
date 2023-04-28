#pragma once
#include "line.h"
#include "mino.h"
#include "tetromino.h"

class Grid {
	Line** gridLines;
	int sizeX, sizeY;
	Mino*** minoGrid;
	Tetromino* currentPiece; 
	float ratio = 1;
	
	public:
		Grid(int x, int y);
		void draw();
		void resize(int x, int y);
		Mino* add(enum color c, int x, int y);
		void addTetromino(enum piece p);
		bool move(int x, int y);
		void hardDrop();
};