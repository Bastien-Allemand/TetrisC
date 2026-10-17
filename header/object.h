#pragma once
#include <stdbool.h>

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
    bool set;
}shape;