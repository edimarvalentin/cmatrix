//
// Created by evalentin on 01/09/2025.
//
#include <stdlib.h>

#include "dense.h"
#include "sparse.h"


dense_matrix cmatrix_add(dense_matrix a, dense_matrix b)
{
    if (a.num_rows != b.num_rows)
    {
        fprintf(stderr, "The rows of A and B are not equal\n");
        exit(1);
    }
    if (a.num_cols != b.num_cols)
    {
        fprintf(stderr, "The columns of A and B are not equal.\n");
    }

    // They are equal. Allocate memory for a new dense_matrix. O(n) space complexity

    // Add matrices, element wise. O(n) time complexity

    int i;
    for (i = 0; i < a.num_rows; i++)
    {
        int j;
        for (j = 0; j < b.num_cols; j++)
        {

        }
    }
}