#ifndef TETRIS_SHAPE_CREATION_H
#define TETRIS_SHAPE_CREATION_H

#include "object.h"

square* createSquare(int x, int y);

shape* createLShape();
shape* createRLShape();
shape* createSShape();
shape* createRSShape();
shape* createIShape();
shape* createSquareShape();
shape* createTShape();

shape* createShape(TYPE type);

#endif