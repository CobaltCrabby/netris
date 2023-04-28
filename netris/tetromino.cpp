#include "tetromino.h"
#include "enum.h"

Tetromino::Tetromino(enum piece shape) {
	type = shape;
	rotation = 0;
	for (int i = 0; i < 4; i++) {
		minos[i] = nullptr;
	}
}

void Tetromino::addMinos(Mino*** minoGrid, int gx, int gy) {
	switch (type) {
		case Z:
			minos[0] = addToGrid(minoGrid, red, 3, 19, gx, gy);
			minos[1] = addToGrid(minoGrid, red, 4, 18, gx, gy);
			minos[2] = addToGrid(minoGrid, red, 4, 19, gx, gy);
			minos[3] = addToGrid(minoGrid, red, 5, 18, gx, gy);
			break;
		case S:
			minos[0] = addToGrid(minoGrid, green, 3, 18, gx, gy);
			minos[1] = addToGrid(minoGrid, green, 4, 18, gx, gy);
			minos[2] = addToGrid(minoGrid, green, 4, 19, gx, gy);
			minos[3] = addToGrid(minoGrid, green, 5, 19, gx, gy);
			break;
		case T:
			minos[0] = addToGrid(minoGrid, purple, 3, 18, gx, gy);
			minos[1] = addToGrid(minoGrid, purple, 4, 19, gx, gy);
			minos[2] = addToGrid(minoGrid, purple, 4, 18, gx, gy);
			minos[3] = addToGrid(minoGrid, purple, 5, 18, gx, gy);
			break;
		case O:
			minos[0] = addToGrid(minoGrid, yellow, 4, 18, gx, gy);
			minos[1] = addToGrid(minoGrid, yellow, 4, 19, gx, gy);
			minos[2] = addToGrid(minoGrid, yellow, 5, 18, gx, gy);
			minos[3] = addToGrid(minoGrid, yellow, 5, 19, gx, gy); 
			break;
		case I:
			minos[0] = addToGrid(minoGrid, light_blue, 3, 18, gx, gy);
			minos[1] = addToGrid(minoGrid, light_blue, 4, 18, gx, gy);
			minos[2] = addToGrid(minoGrid, light_blue, 5, 18, gx, gy);
			minos[3] = addToGrid(minoGrid, light_blue, 6, 18, gx, gy);
			break;
		case L:
			minos[0] = addToGrid(minoGrid, orange, 3, 18, gx, gy);
			minos[1] = addToGrid(minoGrid, orange, 4, 18, gx, gy);
			minos[2] = addToGrid(minoGrid, orange, 5, 18, gx, gy);
			minos[3] = addToGrid(minoGrid, orange, 5, 19, gx, gy);
			break;
		case J:
			minos[0] = addToGrid(minoGrid, dark_blue, 3, 18, gx, gy);
			minos[1] = addToGrid(minoGrid, dark_blue, 3, 19, gx, gy);
			minos[2] = addToGrid(minoGrid, dark_blue, 4, 18, gx, gy);
			minos[3] = addToGrid(minoGrid, dark_blue, 5, 18, gx, gy);
			break;
	}
}

Mino* Tetromino::addToGrid(Mino*** minoGrid, enum color c, int x, int y, int gx, int gy) {
    Mino* mino = new Mino(x, y, c, gx, gy);
    minoGrid[x][y] = mino;
    return mino;
}

Mino** Tetromino::getMinos() {
	return minos;
}