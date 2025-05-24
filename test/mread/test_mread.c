//
// Created by evalentin on 23/05/25.
//

#include <stdlib.h>s
#include "cmatrix.h"

int main() {
    FILE *input_file = fopen("mread_input.txt", "r");
    if (!input_file) {
        fprintf(stderr, "Error opening input file\n");
        exit(1);
    }
    return 0;
}
