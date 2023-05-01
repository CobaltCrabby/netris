#pragma once
#include "mino.h"

class OutlineMino : private Mino {
	public:
		void drawInit();
		OutlineMino(int _x, int _y, enum color _c, int gx, int gy);
		int getX();
		int getY();
		void draw();
		void move();
		void resize(float ratio);
		void changePosition(int _x, int _y);
};
