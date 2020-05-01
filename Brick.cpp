#include <GL/glut.h>
#ifndef BRICK
#define BRICK

// your declarations (and certain types of definitions) here

using namespace std;

class Brick {
public:
  GLfloat n[6][3] = {/* Normals for the 6 faces of a cube. */
                     {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
                     {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}};
  GLint faces[6][4] = {/* Vertex indices for the 6 faces of a cube. */
                       {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
                       {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}};
  GLfloat v[8][3]; /* Will be filled in with X,Y,Z vertexes. */

  void draw() {
    for (int i = 0; i < 6; i++) {
      glBegin(GL_QUADS);
      glNormal3fv(&n[i][0]); // 3 - dimensions, f - floats, v - vertex
      glVertex3fv(&v[faces[i][0]][0]);
      glVertex3fv(&v[faces[i][1]][0]);
      glVertex3fv(&v[faces[i][2]][0]);
      glVertex3fv(&v[faces[i][3]][0]);
      glEnd();
    }
  }

  void init() {
    /* Setup cube vertex data. */
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
  }
};
#endif
