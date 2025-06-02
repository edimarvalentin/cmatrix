//
// Created by evalentin on 30/05/25.
//

#ifndef DENSE_H
#define DENSE_H
#include <stdio.h>

typedef struct {
    double **head;
    int num_rows;
    int num_cols;
} dense_matrix;

dense_matrix cmatrix_dense(FILE *fptr);

void cmatrix_dense_mwrite(dense_matrix matrix);

void cmatrix_dense_merase(dense_matrix *matrix);
#endif //DENSE_H
