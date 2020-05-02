// IFINDEF "Brick.cpp"
#ifndef GROUP
#define GROUP
#include "Ball.cpp"
#include "Brick.cpp"

#include <array>
#include <functional>
#include <iostream>

using namespace std;

class Group {
      public:
	// bool find(std::function<void(bool)> f);
	int size;

	Brick **children;
	Group(int size);
	void push(Brick b);
	void push(Brick *b);

	bool collision(Ball *ball);
	Brick *pop();
	void draw();
	void print();
	bool isEmpty();
	~Group();

      private:
	int count;
};

Group::Group(int size) {
	this->size = size;
	count = 0;
	// children = new Brick[size] instantiates all the bricks!
	// children = (Brick**) malloc(size);
	children = new Brick *[size];
	// for (int i = 0; i < size; i++)
	// children[i] = new Brick();
}

void Group::push(Brick b) {
	push(&b);
}
void Group::push(Brick *b) {
	if (count >= size) {
		cout << "Group size reached";
		return;
	}
	// if (count >= size / 2) {
	// Brick **temp = new Brick *[size * 2];
	// //(Brick **)malloc(count * 2);
	// for (int i = 0; i < count; i++)
	// *temp[i] = *children[i];
	// free(children);
	// children = new Brick *[size * 2];
	// for (int i = 0; i < count; i++)
	// *children[i] = *temp[i];
	// children = temp;
	// this->size = size * 2;
	// }
	delete (children[count]);
	children[count++] = b;
}

Brick *Group::pop() { return children[count--]; }

// Draws all elements of the Group
void Group::draw() {
	for (int i = 0; i < size; i++) {
		if (children[i] != NULL)
			try {
				children[i]->draw();
			} catch (...) {
			}
	}
}

void Group::print() {
	std::cout << "--- Group "
		  << "count: " << count << " size: " << size << "---\n";
	for (int i = 0; i < size; i++) {
		if (children[i] != NULL)
			try {
				std::cout << i << " - " << children[i]->toString();
			} catch (...) {
			}
	}
	std::cout << "---\n";
}

float distance(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrt(pow(x2 - x1, 2) +
		    pow(y2 - y1, 2) +
		    pow(z2 - z1, 2));
}

float distance(Brick b1, Brick b2) { return distance(b1.x, b1.y, b1.z, b2.x, b2.y, b2.z); }
float distance(float x1, float y1, float z1, Brick b2) { return distance(x1, y1, z1, b2.x, b2.y, b2.z); }

bool Group::collision(Ball *ball) {
	for (int i = 0; i < this->count; i++) {
		if (
		    children[i]->collision(*ball)) {
			// Calculates which face is being collided with
			float centerDistance = distance(*children[i], *ball);
			float xStartDistance = distance(children[i]->xStart, children[i]->y, children[i]->z, *ball);
			float xEndDistance = distance(children[i]->xEnd, children[i]->y, children[i]->z, *ball);
			float yStartDistance = distance(children[i]->x, children[i]->yStart, children[i]->z, *ball);
			float yEndDistance = distance(children[i]->x, children[i]->yEnd, children[i]->z, *ball);
			float zStartDistance = distance(children[i]->x, children[i]->y, children[i]->zStart, *ball);
			float zEndDistance = distance(children[i]->x, children[i]->y, children[i]->zEnd, *ball);

			if (
			    xStartDistance < centerDistance ||
			    xEndDistance < centerDistance)
				ball->rightMomentum = !ball->rightMomentum;
			if (
			    yStartDistance < centerDistance ||
			    yEndDistance < centerDistance)
				ball->upMomentum = !ball->upMomentum;
			if (
			    zStartDistance < centerDistance ||
			    zEndDistance < centerDistance)
				ball->forwardMomentum = !ball->forwardMomentum;

			// ball.upMomentum = !ball.upMomentum;
			children[i]->destroyed = true;
			children[i]->size = 0;
			children[i]->x = -100;
			children[i]->y = -100;
			children[i]->z = -100;
			return true;
		}
	}
	return false;
}

bool Group::isEmpty() {
	for (int i = 0; i < size; i++) {
		if (children[i]->id != -1 && !children[i]->destroyed)
			return false;
	}
	return true;
}

// bool Group::find(std::function<void(bool)> f) {
// return f(0);
// }

Group::~Group() {
	delete (children);
}

#endif
