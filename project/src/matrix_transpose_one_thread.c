// Copyright 2022 Sim Roman

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

matrix_t* create_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }
    matrix_t* M = malloc(sizeof(matrix_t));
    if (M == NULL) {
        return NULL;
    }
    M->row = rows;
    M->col = cols;
    M->data = calloc(rows, sizeof(double *));
    if (M->data == NULL) {
        free(M);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        M->data[i] = calloc(cols, sizeof(double));
        if (M->data[i] == NULL) {
            free_matrix(M);
            return NULL;
        }
    }
    return M;
}


matrix_t* create_matrix_from_file(const char* path_file) {
    if (path_file == NULL) {
        return NULL;
    }
    FILE* fmatrix = fopen(path_file, "a+");
    if (fmatrix == NULL) {
        return NULL;
    }
    size_t rows;
    size_t cols;
    if (fscanf(fmatrix, "%zu%zu", &rows, &cols) != 2) {
        fclose(fmatrix);
        return NULL;
    }
    matrix_t* M = create_matrix(rows, cols);
    if (M == NULL) {
        fclose(fmatrix);
        return NULL;
    }
    M->row = rows;
    M->col = cols;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (fscanf(fmatrix, "%lf", &M->data[i][j]) != 1) {
                fclose(fmatrix);
                free_matrix(M);
                return NULL;
            }
        }
    }
    fclose(fmatrix);
    return M;
}

matrix_t* fill_matrix(matrix_t * matrix, double **source_array) {
    for (size_t i = 0; i < matrix->row; i++) {
        for (size_t j = 0; j < matrix->col; j++) {
            matrix->data[i][j] = source_array[i][j];
        }
    }
    return matrix;
}


ssize_t free_matrix(matrix_t* matrix) {
    if (matrix == NULL) {
        return 1;
    }
    for (size_t i = 0; i < matrix->row; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
    return 0;
}


matrix_t* transp(matrix_t* matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    matrix_t* new_matrix = create_matrix(matrix->col, matrix->row);
    if (new_matrix == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->row; i++) {
        for (size_t j = 0; j < matrix->col; j++) {
            new_matrix->data[j][i] = matrix->data[i][j];
        }
    }
    return new_matrix;
}
