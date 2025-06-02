# 📚 CTest Suite for `cmatrix_dense(FILE *fptr)`

This directory contains a test suits for verifying the functionality of `cmatrix_dense_mread`, a function that reads
matrix data from a file and construct a two-dimensional array matrix representation.

---

## 🧪 Test Overview

- **Function Under Test:** `cmatrix_dense_mread(FILE *fptr)`
- **Test Executable:** `test_dense_mread`
- **Test Framework:** [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html)
- **Test Files:** Located in `test/dense_mread`, named `mread_input_0.txt`, `mread_input_1.txt`, and so on as necessary.
  These files have to be copied to the build directory by specifying it in `CMakeLists.txt`. Otherwise, the executable
  won't find them.

---

## 📝 Input File Format

Each `mread_input_*.txt` file must follow this format:

```
<num_rows> <num_cols>
<row_index> <col_index> <value>
<row_index> <col_index> <value>
...
```

### Where:

- `<num_rows>`: Number of rows in the matrix (Integer)
- `<num_cols>`: Number of columns in the matrix (Integer)
- Each entry consists of:
    - `<row_index>`: The row index (0-based, Integer)
    - `<col_index`: The column index (0-based, Integer)
    - `value`: The non-zero value at the given position (Double)

### For example:

```
3 3
0 1 5.0
2 2 -2.01 0 7.5

```

This represents a 3x3 matrix with 3 non-zero terms:
$\begin{bmatrix}0 &5.0 &0\\ 7.5 &0 &0 \\ 0 &0 &-2.0 \end{bmatrix}$
---

## 🔍 Test Details

- **Matrix Dimensions Check**: Ensures the number of rows and columns in the matrix math the header in the input file.
- **Non-Zero Entry Validation**: Verifies that the corresponding entry exists in the matrix and that the value matches.
- **Floating-Point Tolerance**: Uses EPSILON (eg. 1e-6) to allows for minor floating-point differences when comparing.

---

## ⚠️ Notes

- The number of input files set by the `NUMBER_OF_TESTS` macro in `test_mread.c`. Update this if you add more files.
- This test, as written, can only handle up to 10 files (`mread_input_0.txt` to `mread_input_9.txt`). This will be
  addressed in the future as we need to cover more cases.
