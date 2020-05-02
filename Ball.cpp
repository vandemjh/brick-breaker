#ifndef BALL
#define BALL
#include "Brick.cpp"
#include <GL/glut.h>

using namespace std;

class Ball : public Brick {
      public:
      float speed;
   	bool forwardMomentum;
   	bool backwardMomentum;
   	bool leftMomentum;
   	bool rightMomentum;
   	bool upMomentum;
   	bool downMomentum;
	float material[4] = {0.9, 0.0, 0.0, 0.0};
	void draw();
	void update();
	Ball(float size, float speed);
};


Ball::Ball(float size, float speed) : Brick(0, 0, 0, size) {
   	forwardMomentum = true;
   	backwardMomentum = false;
   	leftMomentum = true;
   	rightMomentum = false;
   	upMomentum = true;
   	downMomentum = false;
	speed = speed;
	size = size;
}

void Ball::draw() {
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
void Ball::update() {
	if (leftMomentum && x > -7) x -= speed;
	if (rightMomentum && x < 7) x += speed;
	if (upMomentum && y > -2) y -= speed;
	if (downMomentum && y < 2) y += speed;
	if (forwardMomentum && z > -7) z += speed;
	if (backwardMomentum && z < 7) z -= speed;
}

#endif
