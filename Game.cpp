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

GLfloat light_diffuse[] = {1.0, 1.0, 0.5, 1.0};  /* Color diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; /* Infinite light location. */

Group bricks(2);

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  bricks.draw();
  glutSwapBuffers();
}

void init() {
  // glEnable(GL_AUTO_NORMAL);

  // bricks.push(new Brick());
  bricks.push(new Brick(0, 0, 0, .2));
  bricks.print();

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective(
      // field of view (degrees)
      40.0,
      // aspect ratio
      1.0,
      // near
      1.0,
      // far
      10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0, /* eye is at (0,0,5) */
            0.0, 0.0, 0.0, /* center is at (0,0,0) */
            0.0, 1.0, 0.); /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(-20, 0.0, 0.0, 1.0);
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

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
}
