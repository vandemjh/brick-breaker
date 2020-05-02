/*
Jack Vandemeulebroecke

Hey why are you looking at the source code, get outta here before you get
confused too.
*/

#include "Ball.cpp"
#include "Brick.cpp"
#include "Group.cpp"
#include "Paddle.cpp"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

/* --- Utility Functions --- */
float visibleHeight(float depth);
float visibleWidth(float depth);

/* --- Environment variables --- */
float lightColor[] = {1.0, 1.0, 1.0, 0.0};      // White light
float lightLocation[] = {0.0, 0.0, -10.0, 0.5}; // Light location
float camera[] = {0.0, 0.0, 10.0};
float center[] = {0.0, 0.0, 0.0};

/* --- Constants --- */
const bool DEBUG = true;
const float BRICK_SIZE = .2;
const float WALL_SIZE = .25;
const float ASPECT_RATIO = 1.0;
const float FIELD_OF_VIEW = 90.0; // FOV in degrees
const float PADDLE_SPEED = 0.1;
const float PADDLE_SIZE = 0.2;
const float BALL_SPEED = 0.05;
const float BALL_SIZE = 0.2;
const float LOSE_LINE = -10.0;
float GRAY[4] = {0.8, 0.8, 0.8, 0.0};
float BLUE[4] = {0.0, 0.8, 0.8, 0.0};

/* --- Game variables  --- */
int visibleWidthAtZero;
int visibleHeightAtZero;
int score = 0;

/* --- Initiate --- */
Paddle paddle(PADDLE_SIZE, PADDLE_SPEED);
Ball ball(BALL_SIZE, BALL_SPEED);
Group bounds(1000);
Group bricks(10000);

/* --- Draw the scene --- */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bounds.draw();
	paddle.draw();
	bricks.draw();
	ball.draw();
	if (bricks.collision(ball))
		score++;
	if (paddle.collision(ball)) {
		ball.rightMomentum = ball.x < paddle.x;
		ball.forwardMomentum = ball.z < paddle.z;
		ball.upMomentum = !ball.upMomentum;
	}
	if (ball.y < LOSE_LINE) {
		cout << "Loser!" << endl
		     << "Score: " << score << endl;
		exit(0);
	}
	// cout << ball.collision(0,0,0,1) << endl;

	glutSwapBuffers();
	glutPostRedisplay();
}

void init() {
	// This first part draws the boundary of the game
	visibleWidthAtZero = (int)visibleWidth(0);
	visibleHeightAtZero = (int)visibleHeight(0);
	for (int x = -visibleWidthAtZero; x <= visibleWidthAtZero; x++)
		for (int y = -visibleHeightAtZero; y <= visibleHeightAtZero; y++)
			for (int z = -3; z < 3; z++)
				if ((x == -visibleWidthAtZero || x == visibleWidthAtZero || y == -visibleHeightAtZero || y == visibleHeightAtZero) && y != -visibleWidthAtZero)
					bounds.push(new Brick(x, y, z, WALL_SIZE, GRAY));
				else if (
				    x >= -visibleWidthAtZero + 5 && x <= visibleWidthAtZero - 5 && y >= -visibleHeightAtZero + 5 && y <= visibleHeightAtZero - 5 && z >= -1 && z <= 1 && y > 0)
					bricks.push(new Brick(x, y, z, BRICK_SIZE, BLUE));

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
		paddle.move(true, false, false, false);
	else if (c == 'd')
		paddle.move(false, true, false, false);
	else if (c == 'w')
		paddle.move(false, false, true, false);
	else if (c == 's')
		paddle.move(false, false, false, true);
	else if (c == 27)
		exit(0);
	else if (c == 'p')
		init();
	else
		paddle.move(false, false, false, false);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Brick Breaker");
	glutReshapeWindow(500, 500);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	if (DEBUG)
		cout << "Visible depth at z=0: " << visibleWidth(0) << endl;
	if (DEBUG)
		cout << "Visible depth at z=1: " << visibleWidth(1) << endl;
	if (DEBUG)
		cout << "Visible depth at z=5: " << visibleWidth(5) << endl;
	if (DEBUG)
		cout << "Visible depth at z=10: " << visibleWidth(10) << endl;

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
float visibleWidth(float depth) {
	const float height = visibleHeight(depth);
	return height * ASPECT_RATIO;
}
