//
// Created by evalentin on 23/05/25.
//


#include "cmatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER_OF_TESTS 3
#define EPSILON 1e-6


void compare(sparse_node matrix, FILE *input_file) {
    int num_rows, num_cols, num_terms;
    int row, col;
    double value;

    // Get metadata from the first line
    if (fscanf(input_file, "%d%d%d%*[^\n]", &num_rows, &num_cols, &num_terms) != 3) {
        fprintf(stderr, "Error reading input file metadata.\n");
        exit(1);
    }

    if (matrix->u.entry.row != num_rows || matrix->u.entry.col != num_cols) {
        fprintf(stderr, "Matrix dimensions does not match: matrix has %d x %d, file has %d x %d.\n",
                matrix->u.entry.row, matrix->u.entry.col, num_rows, num_cols);
        exit(1);
    }

    // For each entry, look it up in the matrix
    int i;
    for (i = 0; i < num_terms; i++) {
        if (fscanf(input_file, "%d%d%lf", &row, &col, &value) != 3) {
            fprintf(stderr, "Error reading entry from input file.\n");
            exit(1);
        }

        // Locate head node for this row
        sparse_node head = matrix->right;
        int r;
        for (r = 0; r < row; r++)
            head = head->u.next;

        int found = 0;
        sparse_node temp;

        for (temp = head->right; temp != head; temp = temp->right) {
            if (temp->u.entry.col == col) {
                // We'll talk about comparing doubles
                if (fabs(temp->u.entry.value - value) > EPSILON) {
                    fprintf(stderr, "Value mismatch at (%d,%d): matrix=%lf, file=%lf\n",
                            row, col, temp->u.entry.value, value);
                    exit(1);
                }
                found = 1;
                break;
            }
        }

        if (!found) {
            fprintf(stderr, "Entry (%d,%d) not found in matrix.\n", row, col);
            exit(1);
        }
    }
}


int main() {
    int i;
    char filename[] = "sparse_mread_input_#.txt"; // # -> char 19

    for (i = 0; i < NUMBER_OF_TESTS; i++) {
        filename[19] = i + '0';
        FILE *input_file = fopen(filename, "r");

        if (!input_file) {
            fprintf(stderr, "Error opening input file\n");
            exit(1);
        }

        sparse_node matrix = cmatrix_sparse(input_file);
        rewind(input_file);
        compare(matrix, input_file);
        fclose(input_file);
        cmatrix_sparse_merase(&matrix);
    }


    return 0;
}
