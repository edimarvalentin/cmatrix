//
// Created by evalentin on 23/05/25.
//


#include "cmatrix.h"
#define NUMBER_OF_TESTS 3

void compare(matrix_pointer matrix, FILE *input_file) {
    int num_rows, num_cols, num_terms;
    int row, col, i, j;
    double value;

    // Read dimensions from file
    if (fscanf(input_file, "%d%d%d%*[^\n]", &num_rows, &num_cols, &num_terms) != 3) {
        fprintf(stderr, "Error reading input file header.\n");
        exit(1);
    }

    if (matrix->u.entry.row != num_rows || matrix->u.entry.col != num_cols) {
        fprintf(stderr, "Matrix dimensions mismatch.\n");
        exit(1);
    }

    matrix_pointer head = matrix->right;
    matrix_pointer temp;

    // Read all entries into memory
    fscanf(input_file, "%d%d%d%*[^\n]", &num_rows, &num_cols, &num_terms); // Read header
    struct {
        int row, col;
        double value;
    } entries[num_terms];

    for (j = 0; j < num_terms; j++) {
        if (fscanf(input_file, "%d%d%lf", &entries[j].row, &entries[j].col, &entries[j].value) != 3) {
            fprintf(stderr, "Error reading entry from file.\n");
            exit(1);
        }
    }

    for (i = 0; i < matrix->u.entry.row; i++) {
        for (temp = head->right; temp != head; temp = temp->right) {
            int found = 0;
            for (j = 0; j < num_terms; j++) {
                if (entries[j].row == temp->u.entry.row && entries[j].col == temp->u.entry.col) {
                    if (entries[j].value != temp->u.entry.value) {
                        fprintf(stderr, "Value mismatch at (%d,%d): matrix=%lf, file=%lf\n",
                                entries[j].row, entries[j].col, temp->u.entry.value, entries[j].value);
                        exit(1);
                    }
                    found = 1;
                    break;
                }
            }

            if (!found) {
                fprintf(stderr, "Entry (%d,%d) not found in file.\n", temp->u.entry.row, temp->u.entry.col);
                exit(1);
            }
        }
        head = head->u.next;
    }
}


int main() {
    int i;
    char filename[] = "mread_input_#.txt"; // # -> char 12

    for (i = 0; i < NUMBER_OF_TESTS; i++) {
        filename[12] = i + '0';
        FILE *input_file = fopen(filename, "r");

        if (!input_file) {
            fprintf(stderr, "Error opening input file\n");
            exit(1);
        }

        matrix_pointer matrix = cmatrix_mread(input_file);
        rewind(input_file);
        compare(matrix, input_file);
        cmatrix_merase(&matrix);
    }


    return 0;
}
