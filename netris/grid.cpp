#include "grid.h"
#include "line.h"
#include "mino.h"
#include "enum.h"

Grid::Grid(int x, int y) {
    sizeX = x;
    sizeY = y;

    minoGrid = new Mino**[x];
    gridLines = new Line*[x + y + 2];

    for (int i = 0; i < x; i++) {
        minoGrid[i] = new Mino*[y];
        for (int j = 0; j < y; j++) {
            minoGrid[i][j] = nullptr;
        }
    }

    for (int i = 0; i < x + 1; i++) {
        gridLines[i] = new Line((-x / (2.0f / 0.07f)) + 0.07f * i, (y / (2.0f / 0.07f)), (-x / (2.0f / 0.07f)) + 0.07f * i, (-y / (2.0f / 0.07f)));
    }

    for (int i = 0; i < y + 1; i++) {
        gridLines[x + 1 + i] = new Line((-x / (2.0f / 0.07f)), (-y / (2.0f / 0.07f)) + 0.07f * i, (x / (2.0f / 0.07f)), (-y / (2.0f / 0.07f)) + 0.07f * i);
    }
}

void Grid::draw() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (minoGrid[i][j] != nullptr) {
                minoGrid[i][j]->draw();
            }
        }
    }

    for (int i = 0; i < sizeX + sizeY + 2; i++) {
        gridLines[i]->draw();
    }
}
 
void Grid::resize(int x, int y) {
    ratio = ((float) x) / y;
    for (int i = 0; i < sizeX + 1; i++) {
        gridLines[i]->resize(((-sizeX / (2.0f / 0.07f)) + 0.07f * i) / ratio, (sizeY / (2.0f / 0.07f)), ((-sizeX / (2.0f / 0.07f)) + 0.07f * i) / ratio, (-sizeY / (2.0f / 0.07f)));
    }

    for (int i = 0; i < sizeY + 1; i++) {
        gridLines[sizeX + 1 + i]->resize((-sizeX / (2.0f / 0.07f)) / ratio, (-sizeY / (2.0f / 0.07f)) + 0.07f * i, (sizeX / (2.0f / 0.07f)) / ratio, (-sizeY / (2.0f / 0.07f)) + 0.07f * i);
    }

    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (minoGrid[i][j] != nullptr) {
                minoGrid[i][j]->resize(ratio);
            }
        }
    }
}

Mino* Grid::add(enum color c, int x, int y) {
    Mino* mino = new Mino(x, y, c, sizeX, sizeY);
    minoGrid[x][y] = mino;
    return mino;
}

void Grid::addTetromino(enum piece p) {
    currentPiece = new Tetromino(p);
    currentPiece->addMinos(minoGrid, sizeX, sizeY);
}

bool Grid::move(int x, int y) {
    if (!currentPiece) return false;

    for (int i = 0; i < 4; i++) {
        int ox = currentPiece->getMinos()[i]->getX();
        int oy = currentPiece->getMinos()[i]->getY();
        int nx = ox + x;
        int ny = oy + y;

        //dont move out of board
        if (nx < 0 || nx >= sizeX || ny < 0 || ny >= sizeY) return false;

        //dont move into other pieces
        bool isPieceMino = false;
        for (int j = 0; j < 4; j++) {
            int px = currentPiece->getMinos()[j]->getX();
            int py = currentPiece->getMinos()[j]->getY();
            if (!isPieceMino && nx == px && ny == py) isPieceMino = true;
        }
        if (minoGrid[nx][ny] != nullptr && !isPieceMino) {
            if (y==-1)
                currentPiece = nullptr;
            return false;
        }
    }
    
    if (x == -1 || y == -1) {
        for (int i = 0; i < 4; i++) {
            int ox = currentPiece->getMinos()[i]->getX();
            int oy = currentPiece->getMinos()[i]->getY();
            int nx = ox + x;
            int ny = oy + y;

            minoGrid[nx][ny] = minoGrid[ox][oy];
            minoGrid[ox][oy] = nullptr;
            minoGrid[nx][ny]->move(x, y, ratio);
        }
    }
    else {
        for (int i = 3; i >= 0; i--) {
            int ox = currentPiece->getMinos()[i]->getX();
            int oy = currentPiece->getMinos()[i]->getY();
            int nx = ox + x;
            int ny = oy + y;

            minoGrid[nx][ny] = minoGrid[ox][oy];
            minoGrid[ox][oy] = nullptr;
            minoGrid[nx][ny]->move(x, y, ratio);
        }
    }
    return true;
}

void Grid::hardDrop() {
    while (move(0, -1));
}