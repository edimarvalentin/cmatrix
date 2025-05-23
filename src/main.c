#include <stdio.h>
#include "../include/cmatrix.h"
int main(void) {
    printf("Hello, World!\n");
    matrix_pointer matrix = cmatrix_mread();
    cmatrix_mwrite(matrix);
    return 0;
}