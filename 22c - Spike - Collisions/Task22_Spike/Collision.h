#pragma once
#include "Box.h"
#include "Circle.h"
#include <SDL.h>

class Collision {
public:
	static bool checkCollision(const Box& box1, const Box& box2);

	static bool checkCollision(const Circle& circle1, const Circle& circle2);
};

