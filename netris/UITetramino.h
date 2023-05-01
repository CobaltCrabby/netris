#pragma once
#include "UIMino.h"

class UITetramino {
	UIMino* minos[4];
	int order;
	float spread;
	enum piece type;

	public:
		UITetramino(enum piece shape, int o, float rat, float size, float centerX, float topY, float spread);
		~UITetramino();
		void draw();
		void resize(float ratio);
		void moveUp();
		void hold(float ratio, float x, float y);
		enum piece getType();
};