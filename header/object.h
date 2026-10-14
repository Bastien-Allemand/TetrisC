#ifndef TETRIS_OBJECT_H
#define TETRIS_OBJECT_H

typedef struct square
{
    int x;
    int y;
} square;

typedef enum 
{
    LSHAPE,
    RLSHAPE,
    SSHAPE,
    RSSHAPE,
    ISHAPE,
    SQUARE,
    TSHAPE,
    GROUP

}TYPE;

typedef struct
{
    int count;
    square* form;
    TYPE type;
}shape;

#endif
