//
// Created by evalentin on 1/17/26.
//

#include "cmatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-12

/**
 * @brief Compares two dense matrices to make sure they're equal in dimension and elements.
 * @param a Dense Matrix
 * @param b Dense Matrix
 */
void compare(dense_matrix a, dense_matrix b){
    int num_rows, num_cols;
    int row, col;

    if (a.num_rows != b.num_rows || a.num_cols != b.num_cols){
        fprintf(stderr,"Matrix dimensions do not match: left operand has %d x %d, right operand has %d x %d.\n",
            a.num_rows, a.num_cols, b.num_rows, b.num_cols);
        exit(1);
    }

    num_rows = a.num_rows;
    num_cols = a.num_cols;

    for (row = 0; row < num_rows; row++){
        for (col = 0; col < num_cols; col++){
            if (fabs(a.head[row][col] - b.head[row][col]) > EPSILON){
                fprintf(stderr, "Matrices are not equal at (%d, %d): Expected value was %lf, got %lf\n",
                    row, col, a.head[row][col], b.head[row][col]);
                exit(1);
            }
        }
    }
}



int main(){
    dense_matrix a = cmatrix_dense_from_dim(2, 2);
    dense_matrix b = cmatrix_dense_from_dim(2, 2);
    dense_matrix c = cmatrix_dense_from_dim(2, 2);
    dense_matrix expected = cmatrix_dense_from_dim(2, 2);

    // TEST 1
    a.head[0][0] = 10; a.head[0][1] = 4;
    a.head[1][0] = 4; a.head[1][1] = 8;

    b.head[0][0] = 14; b.head[0][1] = 5;
    b.head[1][0] = 7; b.head[1][1] = 4;

    expected.head[0][0] = 24; expected.head[0][1] = 9;
    expected.head[1][0] = 11; expected.head[1][1] = 12;

    c = cmatrix_add(a, b);

    compare(expected, c);

    cmatrix_dense_merase(&c);

    // TEST 2
    a.head[0][0] = -67; a.head[0][1] = 243;
    a.head[1][0] = 15; a.head[1][1] = 24;

    b.head[0][0] = 69; b.head[0][1] = 245;
    b.head[1][0] = 53; b.head[1][1] = -87;

    c = cmatrix_add(a, b);

    expected.head[0][0] = 2; expected.head[0][1] = 488;
    expected.head[1][0] = 68; expected.head[1][1] = -63;

    compare(expected, c);

    cmatrix_dense_merase(&c);

    return 0;
}