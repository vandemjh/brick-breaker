// IFINDEF "Brick.cpp"
#ifndef GROUP
#define GROUP
#include "Brick.cpp"

#include <iostream>
using namespace std;

class Group {
public:
  int size;
  Brick **array;
  Group(int size);
  void push(Brick b);
  void push(Brick *b);

  Brick* pop();
  void draw();
  void print();

private:
  int count;
};

Group::Group(int size) {
  this->size = size;
  count = 0;
  // array = new Brick[size] instantiates all the bricks!
  // array[size] = {0};
  array = new Brick*[size];
  // for (int i=0; i < size; i++)
  // &array[i] = NULL;
  // array = array;
}
void Group::push(Brick b) { *array[count++] = b; }
void Group::push(Brick *b) { *array[count++] = *b; }
Brick* Group::pop() { return array[count--]; }

// Draws all elements of the Group
void Group::draw() {
  for (int i = 0; i < size; i++) {
    if (&array[i] != NULL)
      try {
        array[i]->draw();
      } catch (...) {
      }
  }
}

void Group::print() {
  std::cout << "--- Group ---\n"
            << "count: " << count << "\n";
  for (int i = 0; i < size; i++) {
    if (&array[i] != NULL)
      try {
        std::cout << i << " - " << typeid(*array[i]).name()
                  << "\nsize: " << array[i]->size << "\n"; // << "\tposition: ";
      } catch (...) {
      }
  }
  std::cout << "--- ---\n";
}
#endif
