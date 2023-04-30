#include "grid.h"
#include "line.h"
#include "mino.h"
#include "enum.h"

#include <iostream>
#include <queue>
using namespace std;

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

    srand((unsigned) time(NULL));
    enum piece order[7] {I, O, T, S, Z, L, J};
    random_shuffle(&order[0], &order[7]);
    for (int i = 1; i < 7; i++) {
        pieceQueue.push_back(order[i]);
        if (i < 6) {
            pieceQueuePieces[i - 1] = new QueueTetramino(order[i], i - 1, ratio);
        }
    }
    addTetromino(order[0]);
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

    for (int i = 0; i < 5; i++) {
        pieceQueuePieces[i]->draw();
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

    for (int i = 0; i < 5; i++) {
        pieceQueuePieces[i]->resize(ratio);
    }
}

Mino* Grid::add(enum color c, int x, int y) {
    Mino* mino = new Mino(x, y, c, sizeX, sizeY);
    minoGrid[x][y] = mino;
    return mino;
}

void Grid::addTetromino(enum piece p) {
    currentPiece = new Tetramino(p);
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
        if (minoGrid[nx][ny] != nullptr && !isPieceMino) return false;
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

    for (int i = 0; i < pieceQueue.size(); i++) {
        std::cout << pieceQueue[i] << " ";
    }
    std::cout << endl;

    addTetromino(pieceQueue.front());
    pieceQueue.pop_front();

    if (pieceQueue.size() == 5) {
        srand((unsigned)time(NULL)); 
        enum piece order[7]{I, O, T, S, Z, L, J};
        random_shuffle(&order[0], &order[7]);
        for (int i = 0; i < 7; i++) {
            pieceQueue.push_back(order[i]);
        }
    }

    delete pieceQueuePieces[0];

    for (int i = 0; i < 4; i++) {
        pieceQueuePieces[i] = pieceQueuePieces[i + 1];
        pieceQueuePieces[i]->moveUp();
        pieceQueuePieces[i]->resize(ratio);
    }

    pieceQueuePieces[4] = new QueueTetramino(pieceQueue[4], 4, ratio);
}

//1 = cw, -1 = ccw, 2 = 180
void Grid::rotate(int direction) {
    const int(*array)[4][2] = S_ROTATION;
    int offsetX = 0;
    int offsetY = 0;
    bool cont;

    switch (currentPiece->getType()) {
        case I:
            array = I_ROTATION;
            break;
        case Z:
            array = Z_ROTATION;
            break;
        case S:
            array = S_ROTATION;
            break;
        case O:
            array = O_ROTATION;
            break;
        case L:
            array = L_ROTATION;
            break;
        case J:
            array = J_ROTATION;
            break;
        case T:
            array = T_ROTATION;
            break;
    }

    for (int k = 0; k < 5; k++) {
        cont = false;

        //get correct kick table
        const int(*kickTable)[5][2] = NON_I_KICK_TABLE;
        if (direction == -1) currentPiece->setRotation(-1);
        if (currentPiece->getType() == I) kickTable = I_KICK_TABLE;

        int lol = currentPiece->getRotation() * 2;
        if (direction == -1) lol++;

        offsetX = kickTable[lol][k][0];
        offsetY = kickTable[lol][k][1];

        if (direction == -1) currentPiece->setRotation(1);

        //test every block
        for (int i = 0; i < 4; i++) {
            if (direction == -1) currentPiece->setRotation(-1);
            int nx = currentPiece->getMinos()[i]->getX() + array[currentPiece->getRotation()][i][0] * direction + offsetX;
            int ny = currentPiece->getMinos()[i]->getY() + array[currentPiece->getRotation()][i][1] * direction + offsetY;
            if (direction == -1) currentPiece->setRotation(1);

            //dont move out of board
            if (nx < 0 || nx >= sizeX || ny < 0 || ny >= sizeY) {
                std::cout << nx << " " << ny << endl;
                cont = true;
                break;
            }

            //dont move into other pieces
            bool isPieceMino = false;
            for (int j = 0; j < 4; j++) {
                int px = currentPiece->getMinos()[j]->getX();
                int py = currentPiece->getMinos()[j]->getY();
                if (!isPieceMino && nx == px && ny == py) isPieceMino = true;
            }

            if (minoGrid[nx][ny] != nullptr && !isPieceMino) {
                cont = true;
                break;
            }
        }

        if (!cont) break;
    }

    if (cont) return;

    int newPositions[4][2];
    if (direction == -1) currentPiece->setRotation(direction);

    //calculate new positions and set them
    for (int i = 0; i < 4; i++) {
        int ox = currentPiece->getMinos()[i]->getX();
        int oy = currentPiece->getMinos()[i]->getY();
        int nx = ox + array[currentPiece->getRotation()][i][0] * direction + offsetX;
        int ny = oy + array[currentPiece->getRotation()][i][1] * direction + offsetY;

        std::cout << "moving " << ox << ", " << oy << " to " << nx << ", " << ny << " with offsets " << offsetX << ", " << offsetY << endl;
        newPositions[i][0] = nx;
        newPositions[i][1] = ny;

        minoGrid[ox][oy] = nullptr;
        currentPiece->getMinos()[i]->move(array[currentPiece->getRotation()][i][0] * direction + offsetX, array[currentPiece->getRotation()][i][1] * direction + offsetY, ratio);
    }

    for (int i = 0; i < 4; i++) {
        minoGrid[newPositions[i][0]][newPositions[i][1]] = currentPiece->getMinos()[i];
    }
    
    if (direction == 1) currentPiece->setRotation(direction);
    std::cout << endl;
}