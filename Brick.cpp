#ifndef BRICK
#define BRICK
#include <GL/glut.h>
#include <string>

using namespace std;

static int brickCount = 0;
class Brick {
public:
  float normals[6][3] = {/* Normals for the 6 faces of a cube. */
                           {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
                           {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}};
  int faces[6][4] = {/* Vertex indices for the 6 faces of a cube. */
                       {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
                       {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}};
  float vertex[8][3];
  float size;
  int id;
  float x;
  float y;
  float z;

  void draw();
  string toString();
  void init(float x, float y, float z, float size);

  Brick();
  Brick(float size);
  Brick(float x, float y, float z, float size);
};

Brick::Brick() { id = -1; }
// Constructor delegation
Brick::Brick(float size) : Brick(0, 0, 0, size) {}

Brick::Brick(float x, float y, float z, float size) { init(x, y, z, size); }

void Brick::init(float x, float y, float z, float size) {
  this->id = brickCount++;
  this->x = x;
  this->y = y;
  this->z = z;

  this->size = size;
  vertex[0][0] = vertex[1][0] = vertex[2][0] = vertex[3][0] = x - (size + size) ; //+ -1
  vertex[4][0] = vertex[5][0] = vertex[6][0] = vertex[7][0] = x + (size + size) ; // + 1
  vertex[0][1] = vertex[1][1] = vertex[4][1] = vertex[5][1] = y - (size + size) ; //+ -1
  vertex[2][1] = vertex[3][1] = vertex[6][1] = vertex[7][1] = y + (size + size) ; // + 1
  vertex[0][2] = vertex[3][2] = vertex[4][2] = vertex[7][2] = z + (size + size) ; //+ 1
  vertex[1][2] = vertex[2][2] = vertex[5][2] = vertex[6][2] = z - (size + size) ; // + -1
}

void Brick::draw() {
  if (id == -1)
    return;
  for (int i = 0; i < 6; i++) {
  // Adapted from example in man pages
    glBegin(GL_QUADS);
    glNormal3fv(&normals[i][0]); // 3 - dimensions, f - floats, v - vertex
    glVertex3fv(&vertex[faces[i][0]][0]);
    glVertex3fv(&vertex[faces[i][1]][0]);
    glVertex3fv(&vertex[faces[i][2]][0]);
    glVertex3fv(&vertex[faces[i][3]][0]);
    glEnd();
  }
}

string Brick::toString() {
  if (id == -1)
    return "undefined\n";
  return "\tid: " + std::to_string(this->id) + "\n\tsize: " + std::to_string(this->size) + "\n" +
         "\tposition: (" + std::to_string(x) + ", " + std::to_string(y) + ", " +
         std::to_string(z) + ")\n";
}

#endif
