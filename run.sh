# Jack Vandemeulebroecke
# Tell the compiler to use OpenGL and GLUT
rm brick-breaker
g++ Game.cpp -o brick-breaker.out -lGL -lGLU -lglut
./brick-breaker
