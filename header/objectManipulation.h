#ifndef TETRIS_OBJECT_MANIPULATION_H
#define TETRIS_OBJECT_MANIPULATION_H

#include "object.h"
#include <stdbool.h>
#include "grid.h"

//true left,false right
void rotation(bool dir, shape* current_shape);
void moveDown(shape* current_shape);
void moveLeft(shape* current_shape);
void moveRight(shape* current_shape);
void fusion(shape* shape1, shape* shape2);
bool hitbottom(shape* current_shape, grid* board);

#endif
