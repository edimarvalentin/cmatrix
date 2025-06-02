//
// Created by evalentin on 22/05/25.
//

#include "sparse.h"
#include <stdlib.h>


sparse_node head_node[MAX_SIZE];

/**
 * @brief  Creates a new node for a sparse matrix data structure.
 *
 * Calls on malloc to find and allocate memory for a node that should be appended or
 * inserted unto a linked list of sparse matrix nodes.
 * @return sparse_node - A new node allocated in memory.
 */
sparse_node new_node(void) {
    sparse_node temp;
    temp = (sparse_node) malloc(sizeof(matrix_node));
    if (IS_FULL(temp)) {
        fprintf(stderr, "Sparse Matrix allocation failed: Memory is full\n");
        exit(1);
    }
    return temp;
}

/**
 * @brief Construct a sparse matrix from a file input.
 *
 * Reads matrix dimensions and non-zero entries from the provided file pointer
 * and constructs a sparse matrix using linked lists.
 * Input file format:
    @code
    <num_rows> <num_cols> <num_non_zero_terms>
    <row_index> <col_index> <value>
    <row_index> <col_index> <value>
    ...
    @endcode

 * @param fptr FILE pointer to the input file, assumed to be opened for reading.
 * Expects matrix size and terms in the specified format.
 * @return sparse_node - The head node of the constructed sparse matrix.
 *
 */
sparse_node cmatrix_sparse(FILE *fptr) {
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

/**
 * @brief Prints the sparse matrix in a readable format.
 *
 * This function traverses the sparse matrix starting from the provided
 * node, expected to be the header node of the matrix, and
 * prints the matrix's dimensions, followed by
 * the row, column, and value of each non-zero entry.
 *
 * @param node The header node of the sparse matrix.
 *             The node is expected to contain matrix dimensions and
 *             cross-linked entries representing non-zero values.
 *
 */
void cmatrix_sparse_mwrite(const sparse_node node) {
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

/**
 * @brief Deallocates all memory associated with a sparse matrix.
 *
 * This function frees the memory allocated for a sparse matrix,
 * including all row and column header nodes and entry nodes.
 * After deallocation, the provided pointer is set to NULL to
 * prevent dangling pointers.
 *
 * @param node A pointer to the header node of the sparse matrix.
 *                     After execution, the pointer is set to NULL.
 *
 */
void cmatrix_sparse_merase(sparse_node *node) {
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
