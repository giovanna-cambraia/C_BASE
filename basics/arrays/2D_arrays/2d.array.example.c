#include <stdio.h>

int main() {
    int nums [3] [2] = {{1, 2}, {3, 4}, {5, 6}};

    printf("%d", nums[1][1]);

    return 0;
}

// ? A 2D array is just an array of arrays — think of it as a grid or table, with rows and columns:

// nums[3][2] means: 3 rows, 2 columns each. Visually:

// Row 0: [1, 2]
// Row 1: [3, 4]
// Row 2: [5, 6]

// ? Indexing: nums[row][col]

// The first bracket picks the row, the second picks the column within that row. So nums[1][1] means: "go to row 1, then column 1 within that row." Row 1 is [3, 4] 
// (remember, indexing starts at 0, so row 1 is the second row) — and within that row, column 1 (also the second item) is 4.

// So printf("%d", nums[1][1]) prints 4.