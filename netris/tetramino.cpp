#include "tetramino.h"
#include "enum.h"
#include "outlineMino.h"

Tetramino::Tetramino(enum piece shape) {
	type = shape;
	rotation = 0;
	for (int i = 0; i < 4; i++) {
		minos[i] = nullptr;
	}
}

void Tetramino::addMinos(Mino*** minoGrid, int gx, int gy) {
	switch (type) {
		case Z:
			minos[0] = addToGrid(minoGrid, red, 3, 19, gx, gy, 0);
			minos[1] = addToGrid(minoGrid, red, 4, 18, gx, gy, 1);
			minos[2] = addToGrid(minoGrid, red, 4, 19, gx, gy, 2);
			minos[3] = addToGrid(minoGrid, red, 5, 18, gx, gy, 3);
			break;
		case S:
			minos[0] = addToGrid(minoGrid, green, 3, 18, gx, gy, 0);
			minos[1] = addToGrid(minoGrid, green, 4, 18, gx, gy, 1);
			minos[2] = addToGrid(minoGrid, green, 4, 19, gx, gy, 2);
			minos[3] = addToGrid(minoGrid, green, 5, 19, gx, gy, 3);
			break;
		case T:
			minos[0] = addToGrid(minoGrid, purple, 3, 18, gx, gy, 0);
			minos[1] = addToGrid(minoGrid, purple, 4, 18, gx, gy, 1);
			minos[2] = addToGrid(minoGrid, purple, 4, 19, gx, gy, 2);
			minos[3] = addToGrid(minoGrid, purple, 5, 18, gx, gy, 3);
			break;
		case O:
			minos[0] = addToGrid(minoGrid, yellow, 4, 18, gx, gy, 0);
			minos[1] = addToGrid(minoGrid, yellow, 4, 19, gx, gy, 1);
			minos[2] = addToGrid(minoGrid, yellow, 5, 18, gx, gy, 2);
			minos[3] = addToGrid(minoGrid, yellow, 5, 19, gx, gy, 3); 
			break;
		case I:
			minos[0] = addToGrid(minoGrid, light_blue, 3, 18, gx, gy, 0);
			minos[1] = addToGrid(minoGrid, light_blue, 4, 18, gx, gy, 1);
			minos[2] = addToGrid(minoGrid, light_blue, 5, 18, gx, gy, 2);
			minos[3] = addToGrid(minoGrid, light_blue, 6, 18, gx, gy, 3);
			break;
		case L:
			minos[0] = addToGrid(minoGrid, orange, 3, 18, gx, gy, 0);
			minos[1] = addToGrid(minoGrid, orange, 4, 18, gx, gy, 1);
			minos[2] = addToGrid(minoGrid, orange, 5, 18, gx, gy, 2);
			minos[3] = addToGrid(minoGrid, orange, 5, 19, gx, gy, 3);
			break;
		case J:
			minos[0] = addToGrid(minoGrid, dark_blue, 3, 18, gx, gy, 0);
			minos[1] = addToGrid(minoGrid, dark_blue, 3, 19, gx, gy, 1);
			minos[2] = addToGrid(minoGrid, dark_blue, 4, 18, gx, gy, 2);
			minos[3] = addToGrid(minoGrid, dark_blue, 5, 18, gx, gy, 3);
			break;
	}
}

Mino* Tetramino::addToGrid(Mino*** minoGrid, enum color c, int x, int y, int gx, int gy, int i) {
    Mino* mino = new Mino(x, y, c, gx, gy);
	outlineMinos[i] = new OutlineMino(x, y, c, gx, gy);
    minoGrid[x][y] = mino;
    return mino;
}

Mino** Tetramino::getMinos() {
	return minos;
}

OutlineMino** Tetramino::getOutlineMinos() {
	return outlineMinos;
}

void Tetramino::updateOutline(int sizeX, int sizeY, Mino*** minoGrid, float ratio) {
	for (int i = 0; i < 4; i++) {
		outlineMinos[i]->changePosition(minos[i]->getX(), minos[i]->getY());
		outlineMinos[i]->resize(ratio);
	}

	bool canLower = true;
	while (canLower) {
		for (int i = 0; i < 4; i++) {
			int ox = outlineMinos[i]->getX();
			int oy = outlineMinos[i]->getY();
			int nx = ox;
			int ny = oy - 1;

			//dont move out of board
			if (ny < 0) {
				canLower = false;
				break;
			}

			//dont move into other pieces
			bool isPieceMino = false;
			for (int j = 0; j < 4; j++) {
				int px = minos[j]->getX();
				int py = minos[j]->getY();
				if (!isPieceMino && nx == px && ny == py) isPieceMino = true;
			}
			if (minoGrid[nx][ny] != nullptr && !isPieceMino) {
				canLower = false;
				break;
			}
		}

		if (!canLower) break;

		for (int i = 0; i < 4; i++) {
			int ox = outlineMinos[i]->getX();
			int oy = outlineMinos[i]->getY();

			outlineMinos[i]->move();
			outlineMinos[i]->resize(ratio);
		}
	}
}

enum piece Tetramino::getType() {
	return type;
}

int Tetramino::getRotation() {
	return rotation;
}

void Tetramino::setRotation(int mino) {
	rotation += mino + 4;
	rotation %= 4;
}

UITetramino* Tetramino::convertToUI(float x, float y, float ratio, float size) {
	return new UITetramino(type, 0, ratio, size, x, y, 0);
}