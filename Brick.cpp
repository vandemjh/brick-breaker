#ifndef BRICK
#define BRICK
#include <GL/glut.h>

using namespace std;

class Brick {
public:
  GLfloat normals[6][3] = {/* Normals for the 6 faces of a cube. */
                           {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
                           {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}};
  GLint faces[6][4] = {/* Vertex indices for the 6 faces of a cube. */
                       {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
                       {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}};
  GLfloat vertex[8][3]; /* Will be filled in with X,Y,Z vertexes. */
  float size;
  void draw();

  Brick();
  Brick(float size);
  Brick(float x, float y, float z, float size);
  // void init(int x, int y, int z);
};

// Constructor delegation
Brick::Brick() : Brick(1) {}
Brick::Brick(float size) : Brick(0, 0, 0, size) {}

Brick::Brick(float x, float y, float z, float size) {
  this->size = size;
  vertex[0][0] = vertex[1][0] = vertex[2][0] = vertex[3][0] = x - size; //+ -1
  vertex[4][0] = vertex[5][0] = vertex[6][0] = vertex[7][0] = y + size; // + 1
  vertex[0][1] = vertex[1][1] = vertex[4][1] = vertex[5][1] = z - size; //+ -1
  vertex[2][1] = vertex[3][1] = vertex[6][1] = vertex[7][1] = x + size; // + 1
  vertex[0][2] = vertex[3][2] = vertex[4][2] = vertex[7][2] = y + size; //+ 1
  vertex[1][2] = vertex[2][2] = vertex[5][2] = vertex[6][2] = z - size; // + -1
}
void Brick::draw() {
  for (int i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&normals[i][0]); // 3 - dimensions, f - floats, v - vertex
    glVertex3fv(&vertex[faces[i][0]][0]);
    glVertex3fv(&vertex[faces[i][1]][0]);
    glVertex3fv(&vertex[faces[i][2]][0]);
    glVertex3fv(&vertex[faces[i][3]][0]);
    glEnd();
  }
}

// void Brick::init(int x, int y, int z) {}
#endif
