#ifndef PADDLE
#define PADDLE
#include "Ball.cpp"
#include "Brick.cpp"
#include <GL/glut.h>

using namespace std;

class Paddle : public Brick {
      public:
	float speed;
	bool leftMomentum;
	bool rightMomentum;
	bool forwardMomentum;
	bool backwardMomentum;
	float zSize;
	float xSize;
	float material[4] = {0.0, 0.0, 0.9, 0.0};
	void move(bool left, bool right, bool up, bool down);
	void draw();
	void update();
	Paddle(float size, float speed);
	bool collision(float x, float y, float z, float size);
	bool collision(Ball ball);
};

Paddle::Paddle(float size, float speed) : Brick(0, -8, 0, size) {
	this->speed = speed;
	// Elongate in the x direction
	for (int i = 0; i < 4; i++)
		size += size;
	zSize = size / 2;
	xSize = size;
}

void Paddle::move(bool left, bool right, bool up, bool down) {
	leftMomentum = false;
	rightMomentum = false;
	forwardMomentum = false;
	backwardMomentum = false;
	if (left)
		leftMomentum = true;
	if (right)
		rightMomentum = true;
	if (up)
		forwardMomentum = true;
	if (down)
		backwardMomentum = true;
}

void Paddle::draw() {
	update();
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++) {
		// glColor3f(1.0, 1.0, 0.0);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
		// Adapted from example in man pages
		glNormal3fv(&normals[i][0]); // 3 - dimensions, f - floats, v - vertices
		glVertex3fv(&vertices[faces[i][0]][0]);
		glVertex3fv(&vertices[faces[i][1]][0]);
		glVertex3fv(&vertices[faces[i][2]][0]);
		glVertex3fv(&vertices[faces[i][3]][0]);
	}
	glEnd();
}

//Updates the vertices matrix
void Paddle::update() {
	if (leftMomentum && x > -7)
		x -= speed;
	if (rightMomentum && x < 7)
		x += speed;
	if (forwardMomentum && z > -2)
		z -= speed;
	if (backwardMomentum && z < 2)
		z += speed;
	vertices[0][0] = vertices[1][0] = vertices[2][0] = vertices[3][0] = x - xSize;
	vertices[4][0] = vertices[5][0] = vertices[6][0] = vertices[7][0] = x + xSize;
	vertices[0][2] = vertices[3][2] = vertices[4][2] = vertices[7][2] = z + zSize;
	vertices[1][2] = vertices[2][2] = vertices[5][2] = vertices[6][2] = z - zSize;
}

// Override the collision method because paddle is rectangular
bool Paddle::collision(float x, float y, float z, float size) {
	return this->x + this->xSize > x - size &&
	       this->x - this->xSize < x + size &&
	       this->y + this->size > y - size &&
	       this->y - this->size < y + size &&
	       this->z + this->zSize > z - size &&
	       this->z - this->zSize < z + size;
}
bool Paddle::collision(Ball ball) { return collision(ball.x, ball.y, ball.z, ball.size); }

#endif
