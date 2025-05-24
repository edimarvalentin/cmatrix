//
// Created by evalentin on 22/05/25.
//

#ifndef CMATRIX_H
#define CMATRIX_H

#define MAX_SIZE 50
#define IS_FULL(ptr) (!(ptr))

#include <stdio.h>


typedef enum { head, entry } tagfield;

typedef struct matrix_node *matrix_pointer;

typedef struct entry_node {
    int row;
    int col;
    double value;
} entry_node;

typedef struct matrix_node {
    matrix_pointer down; // head: links to a column list; entry: next nonzero term in column
    matrix_pointer right; // head: links to a row list; entry: next nonzero term in row
    tagfield tag;

    union {
        matrix_pointer next;
        entry_node entry;
    } u;
} matrix_node;


// LINKED LIST OPERATIONS
matrix_pointer cmatrix_new(int row, int col, int value);

matrix_pointer cmatrix_mread(FILE *fptr);

void cmatrix_merase(matrix_pointer node);

void cmatrix_mwrite(matrix_pointer node);

// MATRIX OPERATIONS


#endif //CMATRIX_H
