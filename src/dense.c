//
// Created by evalentin on 28/05/25.
//

#include "dense.h"
#include <stdlib.h>

/**
 * @brief Constructs a dense matrix from a file input.
 *
 * Reads matrix dimensions and non-zero entries from the provided file pointer.
 * Allocates memory for a two-dimensional array of doubles, initializes
 * entries, and populates them with the specified values.
 *
 * Input file format:
    @code
    <num_rows> <num_cols>
    <row_index> <col_index> <value>
    <row_index> <col_index> <value>
    ...
    @endcode
 *
 * @param fptr FILE pointer to the input file, assumed to be opened for reading.
 * Expects matrix size and terms in the specified format.
 *
 * @return dense_matrix The constructed dense matrix structure containing:
 *                      - Number of rows and columns.
 *                      - A pointer to the allocated two-dimensional array.
 *
 */
dense_matrix cmatrix_dense(FILE *fptr) {
    int num_rows, nums_cols;
    int row, col;
    double value;

    if (fscanf(fptr, "%d%d%*[^\n]", &num_rows, &nums_cols) != 2) {
        fprintf(stderr, "Error reading file: Invalid input format. \n");
        exit(1);
    }

    double **rows = (double **) malloc(sizeof(double *) * num_rows);
    if (rows == NULL) {
        fprintf(stderr, "Dense Matrix allocation failed: Memory is full\n");
        exit(1);
    }

    int k;
    for (k = 0; k < num_rows; k++) {
        rows[k] = (double *) malloc(sizeof(double) * nums_cols);
        if (rows[k] == NULL) {
            fprintf(stderr, "Dense Matrix allocation failed: No memory for row %d.\n", k);
            // free previously allocated rows
            int m;
            for (m = 0; m < k; m++) {
                free(rows[m]);
            }
            free(rows);
            exit(1);
        }
    }


    while (fscanf(fptr, "%d%d%lf", &row, &col, &value) == 3) {
        rows[row][col] = value;
    }

    dense_matrix a;
    a.num_rows = num_rows;
    a.num_cols = nums_cols;
    a.head = rows;

    return a;
}

/**
 * @brief Prints the dense matrix in a readable format.
 *
 * This function prints the dimensions of the provided
 * dense matrix, followed by a formatted list of each element’s row index, column index,
 * and value.
 *
 * @param matrix The dense matrix structure to print.
 *
 */
void cmatrix_dense_mwrite(dense_matrix matrix) {
    int i, j;
    printf(" \n num_rows = %d, num_cols  = %d \n", matrix.num_rows, matrix.num_cols);
    printf(" The matrix by row, column and value: \n\n");
    printf("\n%5s %5s %10s\n", "Row", "Col", "Value");

    for (i = 0; i < matrix.num_rows; i++) {
        for (j = 0; j < matrix.num_cols; j++) {
            printf("%5d%5d%10.4f \n", i, j, matrix.head[i][j]);
        }
    }
}

/**
 * @brief Deallocates all memory associated with a dense matrix.
 *
 * Frees the memory allocated for the dense matrix's two-dimensional array, including all rows.
 * After deallocation, the matrix's head pointer is set to NULL to prevent dangling
 * references.
 *
 * @param matrix The dense matrix structure whose memory is to be freed.
 *                       It is assumed that matrix.head points to dynamically allocated
 *                       memory and that matrix.num_rows specifies the correct number of rows.
 *
 */
void cmatrix_dense_merase(dense_matrix *matrix) {
    int i;
    for (i = 0; i < matrix->num_rows; i++) {
        free(matrix->head[i]);
    }
    free(matrix->head);
    matrix->head = NULL;
}
