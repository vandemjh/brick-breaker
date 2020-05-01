// IFINDEF "Brick.cpp"
#ifndef GROUP
#define GROUP
#include "Brick.cpp"
using namespace std;

class Group {
public:
  Brick *array;
  Group(int size);
  void push(Brick b);

  Brick pop();

private:
  int count;
};

Group::Group(int size) {
  count = 0;
  array = new Brick[size];
}
void Group::push(Brick b) { array[count++] = b; }
Brick Group::pop() { return array[count--]; }
#endif
