# Jack Vandemeulebroecke
# Makefiles are too hard to write
# Tell the compiler to use OpenGL and GLUT
g++ Game.cpp -o brick-breaker.out -lGL -lGLU -lglut
./brick-breaker.out
