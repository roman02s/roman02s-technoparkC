// Copyright 2022 Sim Roman

#include <stdio.h>
#include <stdlib.h>

ssize_t gen_matrix(const char * path) {
    FILE *file = fopen(path, "w");

    if (file == NULL) {
        return -1;
    }
    size_t rows = 10000;
    size_t cols = 5000;

    fprintf(file, "%zu %zu\n", rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            double t = rand() % 100 - 50 + 0.03 * (i % 10) - 0.01;
            fprintf(file, "%5.2lf", t);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
    fclose(file);
    return 0;
}
