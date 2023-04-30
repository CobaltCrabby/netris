#pragma once
#include "queueMino.h"

class QueueTetramino {
	QueueMino* minos[4];
	int order;

	public:
		QueueTetramino(enum piece shape, int order, float ratio);
		~QueueTetramino();
		void draw();
		void resize(float ratio);
		void moveUp();
};