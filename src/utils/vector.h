#pragma once

typedef struct _Vector {
    int size;
    int *values;
} *Vector;

Vector vct_init(int, int*);

Vector vct_zeros(int);

Vector vct_ones(int);

void vct_add(Vector, Vector, Vector);

void vct_subt(Vector, Vector, Vector);

void vct_scale(Vector, double);

double vct_norm(Vector);

