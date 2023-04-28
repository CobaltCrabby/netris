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

	const int NON_I_KICK_TABLE[8][5][2] {
		{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
		{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
		{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
		{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
		{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
		{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
		{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
		{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}
	};

	const int I_KICK_TABLE[8][5][2] {
		{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
		{{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
		{{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
		{{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},
		{{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
		{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
		{{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},
		{{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}}
	};

	//0, R, 2, L (to do ccw just reverse the math)
	const int I_ROTATION[4][4][2]{
		{{2, 1}, {1, 0}, {0, -1}, {-1, -2}}, //0 to R
		{{-2, -2}, {-1, -1}, {0, 0}, {1, 1}}, //R to 2
		{{1, 2}, {0, 1}, {-1, 0}, {-2, -1}}, //2 to L
		{{-1, -1}, {0, 0}, {1, 1}, {2, 2}} //L to 0
	};

	public:
		Grid(int x, int y);
		void draw();
		void resize(int x, int y);
		Mino* add(enum color c, int x, int y);
		void addTetromino(enum piece p);
		bool move(int x, int y);
		void hardDrop();
		void rotate(int direction);
};