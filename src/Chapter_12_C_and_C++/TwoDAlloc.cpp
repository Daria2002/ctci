#include <iostream>

/**
 * Every row points to some memory block in the memory 
 * where elements for that row are stored.
 */
int** my2DAlloc(int rows, int cols) {
    int** rowptr;
    int i;
    rowptr = (int**) malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        rowptr[i] = (int*) malloc(cols * sizeof(int));
    }
    return rowptr;
}

/**
 * first rows number of elements contains pointer to the 
 * contiguous block of memory where elements from that row are
 * stored.
 */
int** my2DAlloc2(int rows, int cols) {
    int i;
    // header contains row number of pointers to row block
    int header = rows * sizeof(int*);
    // data (row * cols) is placed after header
    int data = rows * cols * sizeof(int);
    // rowptr consists of header and data
    int** rowptr = (int**) malloc(header + data);
    if(rowptr == NULL) return NULL;
    // buffer starts when data starts
    int * buf = (int*) (rowptr + rows);
    for(int i = 0; i < rows; i++) {
        // ini header, i.e. i = 0, stores in the header memory address 
        // where data for row = 0 starts
        rowptr[i] = buf + i * cols;
    }
    return rowptr;
}

void my2DDealloc(int*** rowptr, int rows) {
    for(int i = 0; i < rows; i++) {
        free(rowptr[i]);
    }
    free(rowptr);
}

/**
 * Write a function in C called my2DAlloe which allocates a two-dimensional array. 
 * Minimize the number of calls to malloc and make sure that the memory is accessible 
 * by the notation arr[i][j]. 
 */
int main() {
    std::cout << "We use pointers to create array, so for 2d array\n"
                 "(array of arrays) we can use double pointers. The\n"
                 "idea is to create 1d array of pointers, and for each\n"
                 "array index we create a new 1d array.\n";
    const int rows = 2;
    const int cols = 3;
    int** matrix = my2DAlloc(rows, cols);
    int** matrix2 = my2DAlloc2(rows, cols);
    matrix[0][2] = 4;
    matrix2[0][2] = 4;
    std::cout << "matrix[0][2] = " << matrix[0][2] << '\n';
    std::cout << "matrix2[0][2] = " << matrix2[0][2] << '\n';
    my2DDealloc(&matrix, rows);
    my2DDealloc(&matrix2, rows);
}
