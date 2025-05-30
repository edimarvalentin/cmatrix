//
// Created by evalentin on 30/05/25.
//

#ifndef SPARSE_H
#define SPARSE_H
#define MAX_SIZE 50
#define IS_FULL(ptr) (!(ptr))

#include <stdio.h>


typedef enum { head, entry } tagfield;

typedef struct matrix_node *sparse_node;

typedef struct entry_node {
    int row;
    int col;
    double value;
} entry_node;

typedef struct matrix_node {
    sparse_node down; // head: links to a column list; entry: next nonzero term in column
    sparse_node right; // head: links to a row list; entry: next nonzero term in row
    tagfield tag;

    union {
        sparse_node next;
        entry_node entry;
    } u;
} matrix_node;


// LINKED LIST OPERATIONS
sparse_node cmatrix_new(int row, int col, int value);

sparse_node cmatrix_sparse(FILE *fptr);

void cmatrix_merase(sparse_node *node);

void cmatrix_sparse_mwrite(sparse_node node);
#endif //SPARSE_H
