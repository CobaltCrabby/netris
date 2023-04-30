#include "queueTetramino.h"
#include <iostream>

QueueTetramino::QueueTetramino(enum piece shape, int o, float rat) {
	order = o;

	//draw values 
	float size = 0.06f;
	float centerX = 0.7f;
	float topY = 0.65f;
	float spread = 0.2f;

	switch (shape) {
		case I:
			minos[0] = new QueueMino(centerX - 2 * size, topY - spread * o + size / 2, size, light_blue, rat);
			minos[1] = new QueueMino(centerX - 1 * size, topY - spread * o + size / 2, size, light_blue, rat);
			minos[2] = new QueueMino(centerX - 0 * size, topY - spread * o + size / 2, size, light_blue, rat);
			minos[3] = new QueueMino(centerX + 1 * size, topY - spread * o + size / 2, size, light_blue, rat);
			break;
		case O:
			minos[0] = new QueueMino(centerX - 1 * size, topY - spread * o + 0 * size, size, yellow, rat);
			minos[1] = new QueueMino(centerX - 0 * size, topY - spread * o + 0 * size, size, yellow, rat);
			minos[2] = new QueueMino(centerX - 1 * size, topY - spread * o + 1 * size, size, yellow, rat);
			minos[3] = new QueueMino(centerX - 0 * size, topY - spread * o + 1 * size, size, yellow, rat);
			break;
		case T:
			minos[0] = new QueueMino(centerX - 1 / 2.0f * size, topY - spread * o + 1 * size, size, purple, rat);
			minos[1] = new QueueMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, purple, rat);
			minos[2] = new QueueMino(centerX - 3 / 2.0f * size, topY - spread * o + 0 * size, size, purple, rat);
			minos[3] = new QueueMino(centerX + 1 / 2.0f * size, topY - spread * o + 0 * size, size, purple, rat);
			break;
		case S:
			minos[0] = new QueueMino(centerX - 1 / 2.0f * size, topY - spread * o + 1 * size, size, green, rat);
			minos[1] = new QueueMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, green, rat);
			minos[2] = new QueueMino(centerX - 3 / 2.0f * size, topY - spread * o + 0 * size, size, green, rat);
			minos[3] = new QueueMino(centerX + 1 / 2.0f * size, topY - spread * o + 1 * size, size, green, rat);
			break;
		case Z:
			minos[0] = new QueueMino(centerX - 1 / 2.0f * size, topY - spread * o + 1 * size, size, red, rat);
			minos[1] = new QueueMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, red, rat);
			minos[2] = new QueueMino(centerX - 3 / 2.0f * size, topY - spread * o + 1 * size, size, red, rat);
			minos[3] = new QueueMino(centerX + 1 / 2.0f * size, topY - spread * o + 0 * size, size, red, rat);
			break;
		case L:
			minos[0] = new QueueMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, orange, rat);
			minos[1] = new QueueMino(centerX - 3 / 2.0f * size, topY - spread * o + 0 * size, size, orange, rat);
			minos[2] = new QueueMino(centerX + 1 / 2.0f * size, topY - spread * o + 0 * size, size, orange, rat);
			minos[3] = new QueueMino(centerX + 1 / 2.0f * size, topY - spread * o + 1 * size, size, orange, rat);
			break;
		case J:
			minos[0] = new QueueMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, dark_blue, rat);
			minos[1] = new QueueMino(centerX - 3 / 2.0f * size, topY - spread * o + 0 * size, size, dark_blue, rat);
			minos[2] = new QueueMino(centerX + 1 / 2.0f * size, topY - spread * o + 0 * size, size, dark_blue, rat);
			minos[3] = new QueueMino(centerX - 3 / 2.0f * size, topY - spread * o + 1 * size, size, dark_blue, rat);
			break;
	}
}

QueueTetramino::~QueueTetramino() {
	for (int i = 0; i < 4; i++) {
		delete minos[i];
	}
}

void QueueTetramino::draw() {
	for (int i = 0; i < 4; i++) {
		minos[i]->draw();
	}
}

void QueueTetramino::resize(float ratio) {
	for (int i = 0; i < 4; i++) {
		minos[i]->resize(ratio);
	}
}

void QueueTetramino::moveUp() {
	for (int i = 0; i < 4; i++) {
		minos[i]->changeY(0.2f);
	}
}