#include "Collision.h"

bool Collision::checkCollision(const Box& box1, const Box& box2) {
	// Collision detection
	return (box1.rect.x < box2.rect.x + box2.rect.w &&
		box1.rect.x + box1.rect.w > box2.rect.x &&
		box1.rect.y < box2.rect.y + box2.rect.h &&
		box1.rect.y + box1.rect.h > box2.rect.y);
}

bool Collision::checkCollision(const Circle& circle1, const Circle& circle2) {
	// Collision detection
	return (circle1.rect.x < circle2.rect.x + circle2.rect.w &&
		circle1.rect.x + circle1.rect.w > circle2.rect.x &&
		circle1.rect.y < circle2.rect.y + circle2.rect.h &&
		circle1.rect.y + circle1.rect.h > circle2.rect.y);
}