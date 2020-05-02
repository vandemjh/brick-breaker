/*
Jack Vandemeulebroecke

Hey why are you looking at the source code, get outta here before you get
confused too.
*/

#include "Brick.cpp"
#include "Group.cpp"
#include "Paddle.cpp"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

float visibleHeight(float depth);
float visibleDepth(float depth);

/* --- Environment variables --- */
float lightColor[] = {1.0, 1.0, 1.0, 0.0};      // White light
float lightLocation[] = {0.0, 0.0, -10.0, 0.5}; // Light location
float camera[] = {0.0, 0.0, 10.0};
float center[] = {0.0, 0.0, 0.0};

/* --- CONSTANTS --- */
const bool DEBUG = true;
const float BRICK_SIZE = .2;
const float ASPECT_RATIO = 1.0;
const float FIELD_OF_VIEW = 90.0; // FOV in degrees
const float PADDLE_SIZE = 0.2;

Paddle paddle(PADDLE_SIZE);
Group bounds(10000);

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bounds.draw();
	paddle.draw();
	//glutSolidSphere(2, 10, 10);
	glutSwapBuffers();
	glutPostRedisplay();
}

void init() {
	// This first part draws the boundary of the game
	int visW = (int)visibleDepth(0);
	int visD = (int)visibleHeight(0);
	for (int x = -visW; x <= visW; x++)
		for (int y = -visD; y <= visD; y++)
			if (x == -visW || x == visW || y == -visD || y == visD)
				for (int z = -3; z < 3; z++)
					bounds.push(new Brick(x, y, z, BRICK_SIZE));

	/* --- Glut settings ---*/
	// Lighting
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightLocation);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// Use depth buffering for hidden surface elimination.
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	gluPerspective(
	    FIELD_OF_VIEW,
	    ASPECT_RATIO,
	    // near
	    1.0,
	    // far
	    20.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(camera[0], camera[1], camera[2], center[0], center[1], center[2], 0.0, 1.0,
		  0.0); // up is in positive Y direction
}

void keyboard(unsigned char c, int x, int y) {
	if (DEBUG)
		cout << "key pressed: " << std::to_string(c) << "\nx is " << x << "\ny is " << y << "\n";
	if (DEBUG)
		cout << paddle.toString();
	if (c == 'a')
		paddle.move(0.1, 0.0);
	if (c == 'd')
		paddle.move(-0.1, 0.0);
	if (c == 's')
		paddle.move(0.0, -0.1);
	if (c == 'w')
		paddle.move(0.0, 0.1);
	if (c == 27)
		exit(0);
	if (c == 'p')
		init();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Brick Breaker");
	glutReshapeWindow(500, 500);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	if (DEBUG)
		cout << "Visible depth at z=0: " << visibleDepth(0) << endl;
	if (DEBUG)
		cout << "Visible depth at z=1: " << visibleDepth(1) << endl;
	if (DEBUG)
		cout << "Visible depth at z=5: " << visibleDepth(5) << endl;
	if (DEBUG)
		cout << "Visible depth at z=10: " << visibleDepth(10) << endl;

	init();
	glutMainLoop();
	return 0;
}

// Used to get bounds of any view
float visibleHeight(float depth) {
	const float cameraOffset = camera[2];
	if (cameraOffset == depth)
		return 0;
	if (depth < cameraOffset)
		depth -= cameraOffset;
	else
		depth += cameraOffset;
	const float vFOV = (FIELD_OF_VIEW * M_PI) / 180;
	// return 2 * tan(vFOV / 2) * abs(depth);
	return tan(vFOV / 2) * abs(depth);
}
float visibleDepth(float depth) {
	const float height = visibleHeight(depth);
	return height * ASPECT_RATIO;
}
