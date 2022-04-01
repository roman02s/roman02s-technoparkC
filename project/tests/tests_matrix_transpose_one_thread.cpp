// Copyright 2022 Sim Roman


#include <gtest/gtest.h>
#include <cstring>
#include <fstream>

extern "C" {
#include "matrix.h"
}


TEST(MATRIX_ONE_THREAD_TEST, INVALID_CREATE_MATRIX) {
    EXPECT_EQ(create_matrix(0, 0), nullptr);
}


TEST(MATRIX_ONE_THREAD_TEST, VALID_CREATE_MATRIX) {
    matrix_t *M = create_matrix(2, 2);
    EXPECT_EQ(M->row, 2);
    EXPECT_EQ(M->col, 2);
    free_matrix(M);
}

TEST(MATRIX_ONE_THREAD_TEST, INVALID_CREATE_MATRIX_FROM_FILE) {
    EXPECT_EQ(create_matrix_from_file(nullptr), nullptr);
}

TEST(MATRIX_ONE_THREAD_TEST, INVALID_CREATE_MATRIX_FROM_FILE_2) {
    std::ofstream out_stream;
    out_stream.open("_test.txt", std::ios_base::out);
    out_stream << "2 3\n1 2 3\n2 3asd 4";
    out_stream.close();
    EXPECT_EQ(create_matrix_from_file("_test.txt"), nullptr);
}

TEST(MATRIX_ONE_THREAD_TEST, VALID_CREATE_MATRIX_FROM_FILE) {
    std::ofstream out_stream;
    out_stream.open("_test.txt", std::ios_base::out);
    out_stream << "2 3\n1 2 3\n2 3 4";
    out_stream.close();
    matrix_t *M = create_matrix_from_file("_test.txt");
    EXPECT_EQ(M->row, 2);
    EXPECT_EQ(M->col, 3);
    for(int i = 0; i < M->row;i++)
        for(int j = 0;j < M->col;j++)
            EXPECT_EQ(M->data[i][j], i + j + 1);
    free_matrix(M);
    remove("_test.txt");
}

TEST(MATRIX_ONE_THREAD_TEST, VALID_FILL_MATRIX) {
    int rows;
    int cols;
    rows = 2;
    cols = 2;
    double **test_data;
    test_data = new double *[rows];
    for (int i = 0; i < rows; i++) {
        test_data[i] = new double[cols];
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            test_data[i][j] = i + j + 1;
    matrix_t *M = create_matrix(rows, cols);
    M = fill_matrix(M, test_data);

    EXPECT_EQ(M->col, cols);
    EXPECT_EQ(M->row, rows);
    for(int i = 0; i < M->row;i++)
        for(int j = 0;j < M->col;j++)
            EXPECT_EQ(M->data[i][j], i + j + 1);

    free_matrix(M);
    for (int i = 0; i < rows;i++) {
        delete[] test_data[i];
    }
    delete []test_data;
}

TEST(MATRIX_ONE_THREAD_TEST, TRANSPOSE_MATRIX) {
    int rows;
    int cols;
    rows = 3;
    cols = 4;

    double **test_data_a;
    {
        test_data_a = new double *[rows];
        for (int i = 0; i < rows; i++) {
            test_data_a[i] = new double[cols];
        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                test_data_a[i][j] = i + j + 1;
    }
    matrix_t *m = create_matrix(rows, cols);
    m = fill_matrix(m, test_data_a);

    matrix_t *transp_m = transp(m);

    double **test_data_b;
    {
        test_data_b = new double *[cols];
        for (int i = 0; i < cols; i++) {
            test_data_b[i] = new double[rows];
        }
        for (int i = 0; i < cols; i++)
            for (int j = 0; j < rows; j++)
                test_data_b[i][j] = i + j + 1;
    }
    matrix_t *m_test = create_matrix(cols, rows);
    m_test = fill_matrix(m_test, test_data_b);

    EXPECT_EQ(transp_m->row, m_test->row);
    EXPECT_EQ(transp_m->col, m_test->col);
    for (int i = 0 ; i < transp_m->row; i++)
        for (int j = 0; j < transp_m->col; j++)
            EXPECT_EQ(transp_m->data[i][j], m_test->data[i][j]);

    {
        for (int i = 0; i < rows;i++) {
            delete[] test_data_a[i];
        }
        delete []test_data_a;
    }

    {
        for (int i = 0; i < cols;i++) {
            delete[] test_data_b[i];
        }
        delete []test_data_b;
    }

    free_matrix(m);
    free_matrix(transp_m);
    free_matrix(m_test);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
