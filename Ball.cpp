#ifndef BALL
#define BALL
#include "Brick.cpp"
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

class Ball : public Brick {
      public:
	float speed;
	bool forwardMomentum;
	bool rightMomentum;
	bool upMomentum;
	float material[4] = {0.9, 0.0, 0.0, 0.0};
	void draw();
	void update();
	Ball(float size, float speed);
};

Ball::Ball(float size, float speed) : Brick(0, 0, 0, size) {
	forwardMomentum = false;
	rightMomentum = false;
	upMomentum = true;
	this->speed = speed;
	this->size = size;
}

void Ball::draw() {
	update();
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++) {
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
void Ball::update() {
	x += speed * (rightMomentum ? -1 : 1);
	if (x < -8 || x > 8)
		rightMomentum = !rightMomentum;
	y += speed * (upMomentum ? -1 : 1);
	// y < -8 ||
	if (y > 8)
		upMomentum = !upMomentum;
	z += speed * (forwardMomentum ? -1 : 1);
	if (z < -2 || z > 2)
		forwardMomentum = !forwardMomentum;
	vertices[0][0] = vertices[1][0] = vertices[2][0] = vertices[3][0] = x - size;
	vertices[4][0] = vertices[5][0] = vertices[6][0] = vertices[7][0] = x + size;
	vertices[0][1] = vertices[1][1] = vertices[4][1] = vertices[5][1] = y - size;
	vertices[2][1] = vertices[3][1] = vertices[6][1] = vertices[7][1] = y + size;
	vertices[1][2] = vertices[2][2] = vertices[5][2] = vertices[6][2] = z - size;
	vertices[0][2] = vertices[3][2] = vertices[4][2] = vertices[7][2] = z + size;
}

#endif
