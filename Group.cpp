// IFINDEF "Brick.cpp"
#ifndef GROUP
#define GROUP
#include "Brick.cpp"
using namespace std;

class Group {
public:
  int size;
  Brick *array;
  Group(int size);
  void push(Brick b);
  void push(Brick *b);

  Brick pop();
  void draw();

private:
  int count;
};

Group::Group(int size) {
  this->size = size;
  count = 0;
  array = new Brick[size];
}
void Group::push(Brick b) { array[count++] = b; }
void Group::push(Brick *b) { array[count++] = *b; }
Brick Group::pop() { return array[count--]; }

// Draws all elements of the Group
void Group::draw() {
  for (int i = 0; i < size; i++) {
    try {
      array[i].draw();
    } catch (...) {
    }
  }
}
#endif
