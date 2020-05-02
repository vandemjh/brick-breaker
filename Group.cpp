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

	bool collision(Ball ball);
	Brick *pop();
	void draw();
	void print();
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

bool Group::collision(Ball ball) {
	for (int i = 0; i < this->count; i++) {
		if (
		    children[i]->collision(ball)) {
		    ball.upMomentum = !ball.upMomentum;
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

// bool Group::find(std::function<void(bool)> f) {
// return f(0);
// }

Group::~Group() {
	delete (children);
}

#endif
