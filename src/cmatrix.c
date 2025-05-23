//
// Created by evalentin on 22/05/25.
//

#include "../include/cmatrix.h"

#include <stdio.h>
#include <stdlib.h>

matrix_pointer head_node[MAX_SIZE];

matrix_pointer new_node(void) {
    matrix_pointer temp;
    temp = (matrix_pointer) malloc(sizeof(matrix_node));
    if (IS_FULL(temp)) {
        fprintf(stderr, "Matrix allocation failed: Memory is full\n");
        exit(1);
    }
    return temp;
}

matrix_pointer cmatrix_mread(void) {
    int num_rows, num_cols, num_terms, num_heads, i;
    int row, col, current_row;
    double value;
    matrix_pointer temp, last, node;

    printf("Enter number the number of rows, columns, and number of nonzero terms: ");
    scanf("%d%d%d", &num_rows, &num_cols, &num_terms);

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
            printf("Enter row, column, and nonzero term: ");
            scanf("%d%d%lf", &row, &col, &value);
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

void cmatrix_mwrite(const matrix_pointer node) {
    int i;
    matrix_pointer temp, head = node->right;
    printf(" \n num_rows = %d, num_cols  = %d \n", node->u.entry.row, node->u.entry.col);
    printf(" The matrix by row, column and value: \n\n");
    printf("\n%5s %5s %10s\n", "Row", "Col", "Value");
    for (i = 0; i < node->u.entry.row; i++) {
        for (temp = head->right; temp != head; temp = temp->right)
            printf("%5d%5d%10.4f \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
        head = head->u.next;
    }
}
