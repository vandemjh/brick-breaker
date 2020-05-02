#ifndef BRICK
#define BRICK
#include <GL/glut.h>
#include <math.h>
#include <string>

using namespace std;

static int brickCount = 0;
class Brick {
      public:
	float material[4] = {0.8, 0.8, 0.8, 0.0};
	float normals[6][3] = { // Normals for all faces
	    {-1.0, 0.0, 0.0},
	    {0.0, 1.0, 0.0},
	    {1.0, 0.0, 0.0},
	    {0.0, -1.0, 0.0},
	    {0.0, 0.0, 1.0},
	    {0.0, 0.0, -1.0}};
	int faces[6][4] = { //Vertex indices for the 6 faces of a cube.
	    {0, 1, 2, 3},
	    {3, 2, 6, 7},
	    {7, 6, 5, 4},
	    {4, 5, 1, 0},
	    {5, 6, 2, 1},
	    {7, 4, 0, 3}};
	float vertices[8][3];
	float size;
	int id;
	float x;
	float y;
	float z;

	void draw();
	string toString();
	void init(float x, float y, float z, float size);

	Brick();
	~Brick();
	Brick(float size);
	Brick(float x, float y, float z, float size);
};

Brick::Brick() { id = -1; }
// Constructor delegation
Brick::Brick(float size) : Brick(0, 0, 0, size) {}

Brick::Brick(float x, float y, float z, float size) { init(x, y, z, size); }
Brick::~Brick() {
	// Only need to free if 'alloc'd
	// free(normals);
	// free(faces);
	// free(vertices);
}

void Brick::init(float x, float y, float z, float size) {
	this->id = brickCount++;
	this->x = x;
	this->y = y;
	this->z = z;

	size += size;
	this->size = size;
	vertices[0][0] = vertices[1][0] = vertices[2][0] = vertices[3][0] = x - size;
	vertices[4][0] = vertices[5][0] = vertices[6][0] = vertices[7][0] = x + size;
	vertices[0][1] = vertices[1][1] = vertices[4][1] = vertices[5][1] = y - size;
	vertices[2][1] = vertices[3][1] = vertices[6][1] = vertices[7][1] = y + size;
	vertices[1][2] = vertices[2][2] = vertices[5][2] = vertices[6][2] = z - size;
	vertices[0][2] = vertices[3][2] = vertices[4][2] = vertices[7][2] = z + size;
}

void Brick::draw() {
	if (id == -1)
		return;
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

string Brick::toString() {
	if (id == -1)
		return "undefined\n";
	return "\tid: " +
	       std::to_string(this->id) +
	       "\n\tsize: " +
	       std::to_string(this->size) +
	       "\n" +
	       "\tposition: (" +
	       std::to_string((x)) + //round
	       ", " + std::to_string((y)) + //round
	       ", " +
	       std::to_string((z)) + //round
	       ")\n";
}

#endif
