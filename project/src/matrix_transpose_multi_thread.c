// Copyright 2022 Sim Roman


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include "matrix.h"

matrix_t* create_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0)
        return NULL;
    matrix_t* M = malloc(sizeof(matrix_t));
    if (M == NULL)
        return NULL;
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
    if (path_file == NULL)
        return NULL;
    FILE* fmatrix = fopen(path_file, "a+");
    if (fmatrix == NULL)
        return NULL;
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
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (fscanf(fmatrix, "%lf", &M->data[i][j]) != 1) {
                fclose(fmatrix);
                free_matrix(M);
                return NULL;
            }
    fclose(fmatrix);
    return M;
}


ssize_t free_matrix(matrix_t* matrix) {
    for (size_t i = 0; i < matrix->row; i++)
        free(matrix->data[i]);
    free(matrix->data);
    free(matrix);
    return 0;
}


matrix_t* transp(matrix_t* matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    double *shared_memory = mmap(NULL, matrix->col * matrix->row * sizeof(double), PROT_READ | PROT_WRITE,
                 MAP_SHARED | MAP_ANONYMOUS, 0, 0);

    if (shared_memory == MAP_FAILED) {
        return NULL;
    }

    int status;

    size_t process_count = sysconf(_SC_NPROCESSORS_ONLN) % matrix->col;
    size_t part_size = matrix->col / process_count;
    pid_t *pids = (pid_t *)malloc(sizeof(pid_t) * process_count);
    if (pids == NULL) {
        return NULL;
    }

    matrix_t* new_matrix = create_matrix(matrix->col, matrix->row);
    if (new_matrix == NULL) {
        free(pids);
        return NULL;
    }

    for (size_t i = 0; i < process_count; i++) {
        pids[i] = fork();
        if (pids[i] > 0) {
            continue;
        }

        if (i == process_count - 1) {
            for (size_t j = i * part_size; j < matrix->col; j++) {
                for (size_t k = 0; k < matrix->row; k++) {
                    shared_memory[j * matrix->col + k] = matrix->data[k][j];
                }
            }
        } else {
            for (size_t j = i * part_size; j < (i + 1) * part_size; j++) {
                for (size_t k = 0; k < matrix->row; k++) {
                    shared_memory[j * matrix->col + k] = matrix->data[k][j];
                }
            }
        }
        if (shared_memory == NULL) {
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }

    for (size_t i = 0; i < process_count; i++) {
        if (waitpid(pids[i], &status, 0) != pids[i]) {
            free_matrix(new_matrix);
            free(pids);
            return NULL;
        }
    }

    for (size_t i = 0; i < matrix->col; i++) {
        for (size_t j = 0; j < matrix->row; j++) {
            new_matrix->data[i][j] = shared_memory[i * matrix->col + j];
        }
    }
    free(pids);
    return new_matrix;
}
