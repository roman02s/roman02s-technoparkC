// Copyright 2022 Sim Roman

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "gen_matrix.h"

#define MATRIX_FILE "test_matrix.txt"

int main() {
    if (gen_matrix(MATRIX_FILE) != 0) {
        return -1;
    }
    matrix_t * big_matrix = create_matrix_from_file(MATRIX_FILE);
    matrix_t * big_matrix_transpose;
    time_t time_start = time(NULL);
    big_matrix_transpose = transp(big_matrix);
    time_t time_end = time(NULL);
    double result_time_in_seconds = difftime(time_end, time_start);
    printf("Multi thread algorithm execution time: %lf sec.\n", result_time_in_seconds);
    free_matrix(big_matrix);
    free_matrix(big_matrix_transpose);
    return 0;
}