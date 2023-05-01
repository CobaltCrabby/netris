#include "UITetramino.h"
#include <iostream>

UITetramino::UITetramino(enum piece shape, int o, float rat, float size, float centerX, float topY, float sp) {
	order = o;
	spread = sp;
	type = shape;

	switch (shape) {
		case I:
			minos[0] = new UIMino(centerX - 2 * size, topY - spread * o + size / 2, size, light_blue, rat);
			minos[1] = new UIMino(centerX - 1 * size, topY - spread * o + size / 2, size, light_blue, rat);
			minos[2] = new UIMino(centerX - 0 * size, topY - spread * o + size / 2, size, light_blue, rat);
			minos[3] = new UIMino(centerX + 1 * size, topY - spread * o + size / 2, size, light_blue, rat);
			break;
		case O:
			minos[0] = new UIMino(centerX - 1 * size, topY - spread * o + 0 * size, size, yellow, rat);
			minos[1] = new UIMino(centerX - 0 * size, topY - spread * o + 0 * size, size, yellow, rat);
			minos[2] = new UIMino(centerX - 1 * size, topY - spread * o + 1 * size, size, yellow, rat);
			minos[3] = new UIMino(centerX - 0 * size, topY - spread * o + 1 * size, size, yellow, rat);
			break;
		case T:
			minos[0] = new UIMino(centerX - 1 / 2.0f * size, topY - spread * o + 1 * size, size, purple, rat);
			minos[1] = new UIMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, purple, rat);
			minos[2] = new UIMino(centerX - 3 / 2.0f * size, topY - spread * o + 0 * size, size, purple, rat);
			minos[3] = new UIMino(centerX + 1 / 2.0f * size, topY - spread * o + 0 * size, size, purple, rat);
			break;
		case S:
			minos[0] = new UIMino(centerX - 1 / 2.0f * size, topY - spread * o + 1 * size, size, green, rat);
			minos[1] = new UIMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, green, rat);
			minos[2] = new UIMino(centerX - 3 / 2.0f * size, topY - spread * o + 0 * size, size, green, rat);
			minos[3] = new UIMino(centerX + 1 / 2.0f * size, topY - spread * o + 1 * size, size, green, rat);
			break;
		case Z:
			minos[0] = new UIMino(centerX - 1 / 2.0f * size, topY - spread * o + 1 * size, size, red, rat);
			minos[1] = new UIMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, red, rat);
			minos[2] = new UIMino(centerX - 3 / 2.0f * size, topY - spread * o + 1 * size, size, red, rat);
			minos[3] = new UIMino(centerX + 1 / 2.0f * size, topY - spread * o + 0 * size, size, red, rat);
			break;
		case L:
			minos[0] = new UIMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, orange, rat);
			minos[1] = new UIMino(centerX - 3 / 2.0f * size, topY - spread * o + 0 * size, size, orange, rat);
			minos[2] = new UIMino(centerX + 1 / 2.0f * size, topY - spread * o + 0 * size, size, orange, rat);
			minos[3] = new UIMino(centerX + 1 / 2.0f * size, topY - spread * o + 1 * size, size, orange, rat);
			break;
		case J:
			minos[0] = new UIMino(centerX - 1 / 2.0f * size, topY - spread * o + 0 * size, size, dark_blue, rat);
			minos[1] = new UIMino(centerX - 3 / 2.0f * size, topY - spread * o + 0 * size, size, dark_blue, rat);
			minos[2] = new UIMino(centerX + 1 / 2.0f * size, topY - spread * o + 0 * size, size, dark_blue, rat);
			minos[3] = new UIMino(centerX - 3 / 2.0f * size, topY - spread * o + 1 * size, size, dark_blue, rat);
			break;
	}
}

UITetramino::~UITetramino() {
	for (int i = 0; i < 4; i++) {
		delete minos[i];
	}
}

void UITetramino::draw() {
	for (int i = 0; i < 4; i++) {
		minos[i]->draw();
	}
}

void UITetramino::resize(float ratio) {
	for (int i = 0; i < 4; i++) {
		minos[i]->resize(ratio);
	}
}

void UITetramino::moveUp() {
	for (int i = 0; i < 4; i++) {
		minos[i]->changeY(spread);
	}
}

void UITetramino::hold(float ratio, float x, float y) {
	for (int i = 0; i < 4; i++) {
		minos[i]->move(x, y);
		minos[i]->resize(ratio);
	}
}

enum piece UITetramino::getType() {
	return type;
}