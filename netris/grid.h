#pragma once
#include "line.h"
#include "mino.h"
#include "tetramino.h"

class Grid {
	Line** gridLines;
	int sizeX, sizeY;
	Mino*** minoGrid;
	Tetramino* currentPiece;
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
	const int I_ROTATION[4][4][2] {
		{{2, -2}, {1, -1}, {0, 0}, {-1, 1}}, //0 to R
		{{-2, 1}, {-1, 0}, {0, -1}, {1, -2}}, //R to 2
		{{1, -1}, {0, 0}, {-1, 1}, {-2, 2}}, //2 to L
		{{-1, 2}, {0, 1}, {1, 0}, {2, -1}} //L to 0
	};
	
	const int T_ROTATION[4][4][2] {
		{{1, -1}, {0, 0}, {0, 0}, {0, 0}},
		{{-1, 1}, {0, -1}, {0, -1}, {0, 0}},
		{{0, 0}, {0, 0}, {0, 0}, {-1, 1}},
		{{0, 0}, {0, 1}, {0, 1}, {1, -1}}
	};

	const int S_ROTATION[4][4][2]{
		{{1, 0}, {0, 1}, {1, -2}, {0, -1}},
		{{-1, -1}, {0, -2}, {-1, 1}, {0, 0}},
		{{0, 1}, {-1, 2}, {0, -1}, {-1, 0}},
		{{0, 0}, {1, -1}, {0, 2}, {1, 1}}
	};

	/*const int Z_ROTATION[4][4][3];
	const int O_ROTATION[4][4][3];
	const int L_ROTATION[4][4][3];
	const int J_ROTATION[4][4][3];*/

	public:
		Grid(int x, int y);
		void draw();
		void resize(int x, int y);
		Mino* add(enum color c, int x, int y);
		void addTetromino(enum piece p);
		bool move(int x, int y);
		void hardDrop();
		void rotate(int direction);
		void rotateMove(const int LUT[4][4][3], int direction, int i, int x, int y);
};