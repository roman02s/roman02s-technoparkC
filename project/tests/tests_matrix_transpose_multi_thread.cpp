// Copyright 2022 Sim Roman


#include <gtest/gtest.h>
#include <cstring>
#include <fstream>

extern "C" {
#include "matrix.h"
}


TEST(MATRIX_MULTI_THREAD_TEST, INVALID_CREATE_MATRIX) {
    EXPECT_EQ(create_matrix(0, 0), nullptr);
}

TEST(MATRIX_MULTI_THREAD_TEST, INVALID_CREATE_MATRIX_FROM_FILE) {
    EXPECT_EQ(create_matrix_from_file(nullptr), nullptr);
}

TEST(MATRIX_MULTI_THREAD_TEST, INVALID_CREATE_MATRIX_FROM_FILE_2) {
    std::ofstream out_stream;
    out_stream.open("_test.txt", std::ios_base::out);
    out_stream << "2 3\n1 2 3\n2 3asd 4";
    out_stream.close();

    EXPECT_EQ(create_matrix_from_file("_test.txt"), nullptr);
}

TEST(MATRIX_MULTI_THREAD_TEST, VALID_CREATE_MATRIX_FROM_FILE) {
    std::ofstream out_stream;
    out_stream.open("_test.txt", std::ios_base::out);
    out_stream << "2 3\n1 2 3\n2 3 4";
    out_stream.close();

    matrix_t *M = create_matrix_from_file("_test.txt");

    EXPECT_EQ(M->row, 2);
    EXPECT_EQ(M->col, 3);
    for(size_t i = 0; i < M->row;i++) {
        for(size_t j = 0;j < M->col;j++) {
            EXPECT_EQ(M->data[i][j], i + j + 1);
        }
    }
    free_matrix(M);
    remove("_test.txt");
}

TEST(MATRIX_MULTI_THREAD_TEST, INVALID_TRANSPOSE_MATRIX_1) {
    EXPECT_EQ(transp(nullptr), nullptr);
}

TEST(MATRIX_MULTI_THREAD_TEST, INVALID_TRANSPOSE_MATRIX_2) {
    matrix_t *m = (matrix_t *)malloc(sizeof(matrix_t));
    m->col = 0;
    m->row = 0;
    EXPECT_EQ(transp(m), nullptr);
    free(m);
}


TEST(MATRIX_MULTI_THREAD_TEST, VALID_TRANSPOSE_MATRIX) {
    size_t rows;
    size_t cols;
    rows = 3;
    cols = 4;

    matrix_t *m = create_matrix(rows, cols);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            m->data[i][j] = i + j + 1;
        }
    }

    matrix_t *transp_m = transp(m);

    for (size_t i = 0 ; i < transp_m->row; i++) {
        for (size_t j = 0; j < transp_m->col; j++) {
            EXPECT_EQ(transp_m->data[i][j], i + j + 1);
        }
    }

    free_matrix(m);
    free_matrix(transp_m);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
