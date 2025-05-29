//
// Created by evalentin on 22/05/25.
//

#include "cmatrix.h"
#include <stdlib.h>


sparse_node head_node[MAX_SIZE];

sparse_node new_node(void) {
    sparse_node temp;
    temp = (sparse_node) malloc(sizeof(matrix_node));
    if (IS_FULL(temp)) {
        fprintf(stderr, "Matrix allocation failed: Memory is full\n");
        exit(1);
    }
    return temp;
}

sparse_node cmatrix_mread(FILE *fptr) {
    int num_rows, num_cols, num_terms, num_heads, i;
    int row, col, current_row;
    double value;
    sparse_node temp, last, node;


    if (fscanf(fptr, "%d%d%d%*[^\n]", &num_rows, &num_cols, &num_terms) != 3) {
        fprintf(stderr, "Error reading file: Invalid input format.\n");
        exit(1);
    }

    num_heads = (num_cols > num_rows) ? num_cols : num_rows;

    node = new_node();
    node->tag = entry;
    node->u.entry.row = num_rows;
    node->u.entry.col = num_cols;

    if (!num_heads) node->right = node;
    else {
        for (i = 0; i < num_heads; i++) {
            temp = new_node();
            head_node[i] = temp;
            head_node[i]->tag = head;
            head_node[i]->right = temp;
            head_node[i]->u.next = temp;
        }

        current_row = 0;
        last = head_node[0];

        for (i = 0; i < num_terms; i++) {
            if (fscanf(fptr, "%d%d%lf", &row, &col, &value) != 3) {
                fprintf(stderr, "Error reading file: Invalid input format.\n");
                exit(1);
            }

            if (row > current_row) {
                last->right = head_node[current_row];
                current_row = row;
                last = head_node[row];
            }

            temp = new_node();
            temp->tag = entry;
            temp->u.entry.row = row;
            temp->u.entry.col = col;
            temp->u.entry.value = value;

            last->right = temp;
            last = temp;

            head_node[col]->u.next->down = temp;
            head_node[col]->u.next = temp;
        }

        last->right = head_node[current_row];

        for (i = 0; i < num_cols; i++)
            head_node[i]->u.next->down = head_node[i];

        for (i = 0; i < num_heads - 1; i++)
            head_node[i]->u.next = head_node[i + 1];

        head_node[num_heads - 1]->u.next = node;
        node->right = head_node[0];
    }
    return node;
}

void cmatrix_mwrite(const sparse_node node) {
    int i;
    sparse_node temp, head = node->right;
    printf(" \n num_rows = %d, num_cols  = %d \n", node->u.entry.row, node->u.entry.col);
    printf(" The matrix by row, column and value: \n\n");
    printf("\n%5s %5s %10s\n", "Row", "Col", "Value");
    for (i = 0; i < node->u.entry.row; i++) {
        for (temp = head->right; temp != head; temp = temp->right)
            printf("%5d%5d%10.4f \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
        head = head->u.next;
    }
}

void cmatrix_merase(sparse_node *node) {
    sparse_node x, y, head = (*node)->right;
    int i;

    for (i = 0; i < (*node)->u.entry.row; i++) {
        y = head->right;
        while (y != head) {
            x = y;
            y = y->right;
            free(x);
        }
        x = head;
        head = head->u.next;
        free(x);
    }
    y = head;
    while (y != *node) {
        x = y;
        y = y->u.next;
        free(x);
    }
    free(*node);
    *node = NULL;
}
