//
// Created by evalentin on 30/05/25.
//

#include "cmatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUMBER_OF_TESTS 3
#define EPSILON 1e-6

/**
 * @brief Compares a dense matrix with matrix data from a file.
 *
 * This function reads matrix dimensions and entries from an input file, constructs
 * a local representation of the matrix, and compares each element against the
 * provided dense matrix. The function exits with an error if:
 * - The dimensions of the matrix and file data do not match.
 * - Any matrix element differs by more than a defined EPSILON tolerance.
 *
 * Input file format:
    @code
    <num_rows> <num_cols>
    <row_index> <col_index> <value>
    <row_index> <col_index> <value>
    ...
    @endcode
 *
 * @param matrix The dense matrix structure to compare against.
 *               It is assumed that matrix.head points to a valid two-dimensional array.
 * @param input_file The input FILE pointer opened for reading.
 *                   Must contain matrix dimensions and entries in the specified format.
 *
 */
void compare(dense_matrix matrix, FILE *input_file) {
    int num_rows, num_cols;
    int row, col, i, j;
    double value;

    if (fscanf(input_file, "%d%d%*[^\n]", &num_rows, &num_cols) != 2) {
        fprintf(stderr, "Error reading input file metadata. \n");
        exit(1);
    }


    if (matrix.num_rows != num_rows || matrix.num_cols != num_cols) {
        fprintf(stderr, "Matrix dimensions does not match: matrix has %d x %d, file has %d x %d.\n",
                matrix.num_rows, matrix.num_cols, num_rows, num_cols);
        exit(1);
    }

    double file_matrix[num_rows][num_cols];

    // necessarily painful
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            file_matrix[i][j] = 0.0f;
        }
    }

    while (fscanf(input_file, "%d%d%lf", &row, &col, &value) == 3) {
        file_matrix[row][col] = value;
    }

    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            if (fabs(matrix.head[i][j] - file_matrix[i][j]) > EPSILON) {
                fprintf(stderr, "Value mismatch at (%d, %d): matrix=%lf, file=%lf\n",
                        i, j, matrix.head[i][j], file_matrix[i][j]);
                exit(1);
            }
        }
    }
}

int main() {
    int i;
    char filename[] = "dense_mread_input_#.txt"; // # char -> 18
    FILE *input_file = NULL;

    for (i = 0; i < NUMBER_OF_TESTS; i++) {
        filename[18] = i + '0';
        input_file = fopen(filename, "r");

        if (!input_file) {
            fprintf(stderr, "Error opening input file\n");
            exit(1);
        }

        dense_matrix matrix = cmatrix_dense_from_file(input_file);

        rewind(input_file);
        compare(matrix, input_file);

        fclose(input_file);
        input_file = NULL;

        cmatrix_dense_merase(&matrix);
    }
    return 0;
}
