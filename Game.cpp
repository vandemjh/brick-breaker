/*
Jack Vandemeulebroecke

Hey why are you looking at the source code, get outta here before you get
confused too.
*/

#include "Brick.cpp"
#include "Group.cpp"
#include <GL/glut.h>
#include <iostream>

using namespace std;
bool debug = false;

float lightColor[] = {1.0, 1.0, 1.0, 0.0};  /* Color diffuse light. */
float lightLocation[] = {0.0, 0.0, -5.0, 0.5}; //Light location
float camera[] = {0.0, 0.0, 10.0};
float center[] = {0.0, 0.0, 0.0};

Group bricks(5);

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  bricks.draw();
  glutSwapBuffers();
}

void init() {
  // glEnable(GL_AUTO_NORMAL);

  // bricks.push(new Brick());
  bricks.push(new Brick(2, 2, 0, .2));
  bricks.push(new Brick(1, 1, 0, .2));
  bricks.push(new Brick(0, 0, 0, .2));
  bricks.push(new Brick(-1, -1, 0, .2));
  bricks.push(new Brick(-2, -2, 0, .2));
  // bricks.push(new Brick(1, 1, 1, .2));
  // bricks.push(new Brick(1, 2, 0, .1));
  // bricks.push(new Brick(0, 1, 0, .2));
  bricks.print();

  // Lighting
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT0, GL_POSITION, lightLocation);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective(
      // field of view (degrees)
      50.0,
      // aspect ratio
      1.0,
      // near
      1.0,
      // far
      10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(camera[0], camera[1], camera[2],
            center[0], center[1], center[2],
            0.0, 1.0, 0.0); // up is in positive Y direction

  /* Adjust cube position to be asthetic angle. */
  // glTranslatef(0.0, 0.0, -1.0);
  // glRotatef(60, 1.0, 0.0, 0.0);
  // glRotatef(-20, 0.0, 0.0, 1.0);
}

void keyboard(unsigned char c, int x, int y) {
  if (debug)
    cout << "key pressed: " << c << "\nx is " << x << "\ny is " << y << "\n";
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
  init();
  glutMainLoop();
  return 0;
}
