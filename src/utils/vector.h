#pragma once

typedef struct _Vector {
    int size;
    int *values;
} *Vector;

Vector vct_init(int, int*);

void vct_add(Vector, Vector, Vector);

