// Copyright 2022 Sim Roman

#ifndef HW2_C_MATRIX_H
#define HW2_C_MATRIX_H

#include <stdio.h>

typedef struct Matrix {
    size_t row;
    size_t col;
    double** data;
} matrix_t;



matrix_t * create_matrix_from_file(const char*);
matrix_t * create_matrix(size_t, size_t);
matrix_t * fill_matrix(matrix_t *, double **);
ssize_t free_matrix(matrix_t *);

matrix_t * transp(matrix_t *);


#endif //HW2_C_MATRIX_H
