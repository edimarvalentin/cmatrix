//
// Created by evalentin on 30/05/25.
//

#include "cmatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUMBER_OF_TESTS 3
#define EPSILON 1e-6

int main() {
    int i;
    char filename[] = "dense_mread_input_#.txt"; // # char -> 18

    for (i = 0; i < NUMBER_OF_TESTS; i++) {
        filename[18] = i + '0';
        FILE *input_file = fopen(filename, "r");

        if (!input_file) {
            fprintf(stderr, "Error opening input file\n");
            exit(1);
        }

        dense_matrix matrix = cmatrix_dense(input_file);
        cmatrix_dense_mwrite(matrix);
    }
    return 0;
}
