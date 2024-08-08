#include <stdio.h>
#include <stdlib.h>

// Function prototypes --> names are enough to understand function, aur docx nhi chahiye
//add unit tests later?
void inputMatrix(int **arr, int rows, int cols);
void outputMatrix(int **arr, int rows, int cols);
int checkSparseMatrix(int **arr, int rows, int cols);
void RowTriplet(int **arr, int rows, int cols, int **triplet, int nonZeroes);
void displayTriplet(int **triplet, int nonZeroes);
void addTriplets(int **tripletA, int **tripletB);
void subtractTriplets(int **tripletA, int **tripletB);
void multiplyTriplets(int **tripletA, int **tripletB);

int main() {
    int rowsA, colsA, rowsB, colsB;

    printf("Input Number of Rows of Matrix A: \n");
    scanf("%d", &rowsA);
    printf("Input Number of Columns of Matrix A: \n");
    scanf("%d", &colsA);

    printf("Input Number of Rows of Matrix B: \n");
    scanf("%d", &rowsB);
    printf("Input Number of Columns of Matrix B: \n");
    scanf("%d", &colsB);

    // Allocate memory for matrices A and B
    int **arrA = (int **)malloc(rowsA * sizeof(int *));
    int **arrB = (int **)malloc(rowsB * sizeof(int *));
    for (int i = 0; i < rowsA; i++) {
        arrA[i] = (int *)malloc(colsA * sizeof(int));
    }
    for (int i = 0; i < rowsB; i++) {
        arrB[i] = (int *)malloc(colsB * sizeof(int));
    }

    // Input matrices A and B
    inputMatrix(arrA, rowsA, colsA);
    inputMatrix(arrB, rowsB, colsB);

    // Check if matrices A and B are sparse
    int nonZeroesA = checkSparseMatrix(arrA, rowsA, colsA);
    int nonZeroesB = checkSparseMatrix(arrB, rowsB, colsB);

    if (nonZeroesA == 0) {
        printf("Matrix A is not sparse.\n");
        return 1;
    }

    if (nonZeroesB == 0) {
        printf("Matrix B is not sparse.\n");
        return 1;
    }

    // Allocate memory for triplet representation of matrices A and B
    int **tripletA = (int **)malloc((nonZeroesA + 1) * sizeof(int *)); //double pointer for int elements pointers
    int **tripletB = (int **)malloc((nonZeroesB + 1) * sizeof(int *));
    for (int i = 0; i <= nonZeroesA; i++) {
        tripletA[i] = (int *)malloc(3 * sizeof(int));
    }
    for (int i = 0; i <= nonZeroesB; i++) {
        tripletB[i] = (int *)malloc(3 * sizeof(int));
    }

    // Convert matrices to triplet representation
    RowTriplet(arrA, rowsA, colsA, tripletA, nonZeroesA);
    RowTriplet(arrB, rowsB, colsB, tripletB, nonZeroesB);

    // Display triplet representation of matrices
    printf("Triplet representation of Matrix A:\n");
    displayTriplet(tripletA, nonZeroesA);

    printf("Triplet representation of Matrix B:\n");
    displayTriplet(tripletB, nonZeroesB);

    // Add, subtract, and multiply triplets
    addTriplets(tripletA, tripletB);
    subtractTriplets(tripletA, tripletB);
    multiplyTriplets(tripletA, tripletB);

    // Free allocated memory
    for (int i = 0; i < rowsA; i++) {
        free(arrA[i]);
    }
    for (int i = 0; i < rowsB; i++) {
        free(arrB[i]);
    }
    for (int i = 0; i <= nonZeroesA; i++) {
        free(tripletA[i]);
    }
    for (int i = 0; i <= nonZeroesB; i++) {
        free(tripletB[i]);
    }
    free(arrA);
    free(arrB);
    free(tripletA);
    free(tripletB);

    return 0;
}

void inputMatrix(int **arr, int rows, int cols) {
    //takes the matrices as input from the user
    printf("Enter your elements sequentially: \n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

void outputMatrix(int **arr, int rows, int cols) {
    //displays the matrices
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int checkSparseMatrix(int **arr, int rows, int cols) {
    //sparse hai ki nhi dekh lega ye
    int countZeroes = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] == 0) countZeroes++;
        }
    }
    if (countZeroes < (rows * cols) - countZeroes) {
        return 0;
    }
    return (rows * cols) - countZeroes;
}

void RowTriplet(int **arr, int rows, int cols, int **triplet, int nonZeroes) {
    //coverts matrices to triplet form if sparse waala function is nonzero in main()
    triplet[0][0] = rows;
    triplet[0][1] = cols;
    triplet[0][2] = nonZeroes;//meta data to convert triplet to sparse if needed 

    int k = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] != 0) {
                triplet[k][0] = i;
                triplet[k][1] = j;
                triplet[k][2] = arr[i][j];
                k++;
            }
        }
    }
}

void displayTriplet(int **triplet, int nonZeroes) {
    //simple enough to guess this function's purpose lol.
    for (int i = 0; i <= nonZeroes; i++) {
        printf("%d %d %d\n", triplet[i][0], triplet[i][1], triplet[i][2]);
    }
}

void addTriplets(int **tripletA, int **tripletB) {
    int rowsA = tripletA[0][0];
    int colsA = tripletA[0][1];
    int nonZeroesA = tripletA[0][2];

    int rowsB = tripletB[0][0];
    int colsB = tripletB[0][1];
    int nonZeroesB = tripletB[0][2];

    //step 1: check karo ki same dimension ke hai bhi ki nhi, meta data clutching it again for us fr.
    if (rowsA != rowsB || colsA != colsB) {
        printf("Matrices dimensions do not match for addition.\n");
        return;
    }

    int **result = (int **)malloc((nonZeroesA + nonZeroesB + 1) * sizeof(int *));//size of result should be addition of both for worst case where saare unique hai
    for (int i = 0; i <= nonZeroesA + nonZeroesB; i++) {
        result[i] = (int *)malloc(3 * sizeof(int));
    }

    result[0][0] = rowsA;
    result[0][1] = colsA;
    int k = 1;

    int i = 1, j = 1;
    while (i <= nonZeroesA && j <= nonZeroesB) 
    {
        if (tripletA[i][0] < tripletB[j][0] || (tripletA[i][0] == tripletB[j][0] && tripletA[i][1] < tripletB[j][1])) {
            //less than or (equal then chk column kam hai kya tripA ka)
            result[k][0] = tripletA[i][0];
            result[k][1] = tripletA[i][1];
            result[k][2] = tripletA[i][2];
            i++;
            // basically this condition handles case if the row and column indices of the current element in tripletA 
            //are less than those in tripletB, add the element from tripletA to the result.
        } else if (tripletA[i][0] > tripletB[j][0] || (tripletA[i][0] == tripletB[j][0] && tripletA[i][1] > tripletB[j][1])) {
            result[k][0] = tripletB[j][0];
            result[k][1] = tripletB[j][1];
            result[k][2] = tripletB[j][2];
            j++;
            //tripB ka chota hua position (indices) [i][j] phela aata ho
            //i.e. if tripA is bigger toh add tripB as its index is smaller
            //and hence phele aana chahiye
        } else {
            result[k][0] = tripletA[i][0];
            result[k][1] = tripletA[i][1];
            result[k][2] = tripletA[i][2] + tripletB[j][2];
            i++;
            j++;
            //this case handles if both are same indices par occuring then For sure add hoga
        }
        k++;
    }

    while (i <= nonZeroesA) 
    {
        result[k][0] = tripletA[i][0];
        result[k][1] = tripletA[i][1];
        result[k][2] = tripletA[i][2];
        i++;
        k++;
        //handles baaki kucha tripA ke elements if they are still there
    }

    while (j <= nonZeroesB) 
    {
        result[k][0] = tripletB[j][0];
        result[k][1] = tripletB[j][1];
        result[k][2] = tripletB[j][2];
        j++;
        k++;
        //handles baaki kucha tripB ke elements if they are still there
        //i.e. copies remaining elements.
    }

    result[0][2] = k - 1; //meta data for number of tripRes elements

    printf("Resultant Triplet after Addition:\n");
    displayTriplet(result, k - 1);

    for (int i = 0; i <= nonZeroesA + nonZeroesB; i++) {
        free(result[i]);
    }
    free(result);
}

void subtractTriplets(int **tripletA, int **tripletB) {
    int rowsA = tripletA[0][0];
    int colsA = tripletA[0][1];
    int nonZeroesA = tripletA[0][2];

    int rowsB = tripletB[0][0];
    int colsB = tripletB[0][1];
    int nonZeroesB = tripletB[0][2];

    if (rowsA != rowsB || colsA != colsB) {
        printf("Matrices dimensions do not match for subtraction.\n");
        return;
    }

    int **result = (int **)malloc((nonZeroesA + nonZeroesB + 1) * sizeof(int *));
    for (int i = 0; i <= nonZeroesA + nonZeroesB; i++) {
        result[i] = (int *)malloc(3 * sizeof(int));
    }

    result[0][0] = rowsA;
    result[0][1] = colsA;
    int k = 1;

    int i = 1, j = 1;
    while (i <= nonZeroesA && j <= nonZeroesB) {
        if (tripletA[i][0] < tripletB[j][0] || (tripletA[i][0] == tripletB[j][0] && tripletA[i][1] < tripletB[j][1])) {
            result[k][0] = tripletA[i][0];
            result[k][1] = tripletA[i][1];
            result[k][2] = tripletA[i][2];
            i++;
            //same logic as addition
        } else if (tripletA[i][0] > tripletB[j][0] || (tripletA[i][0] == tripletB[j][0] && tripletA[i][1] > tripletB[j][1])) {
            result[k][0] = tripletB[j][0];
            result[k][1] = tripletB[j][1];
            result[k][2] = -tripletB[j][2];
            //negation used above since if element is present in B but not in A
            //it means ki sparse mei 0 - b waala element hoga na, toh uske liye - use kiya.
            j++;
        } else {
            result[k][0] = tripletA[i][0];
            result[k][1] = tripletA[i][1];
            result[k][2] = tripletA[i][2] - tripletB[j][2];
            i++;
            j++;
            //same as addition.
        }
        k++;
    }

    while (i <= nonZeroesA) {
        result[k][0] = tripletA[i][0];
        result[k][1] = tripletA[i][1];
        result[k][2] = tripletA[i][2];
        i++;
        k++;
        //copy remaining elements
    }

    while (j <= nonZeroesB) {
        result[k][0] = tripletB[j][0];
        result[k][1] = tripletB[j][1];
        result[k][2] = -tripletB[j][2];
        j++;
        k++;
        //copy remaining elements
    }

    result[0][2] = k - 1;

    printf("Resultant Triplet after Subtraction:\n");
    displayTriplet(result, k - 1);

    for (int i = 0; i <= nonZeroesA + nonZeroesB; i++) {
        free(result[i]);
    }
    free(result);
}

void multiplyTriplets(int **tripletA, int **tripletB) {
    int rowsA = tripletA[0][0];
    int colsA = tripletA[0][1];
    int nonZeroesA = tripletA[0][2];

    int rowsB = tripletB[0][0];
    int colsB = tripletB[0][1];
    int nonZeroesB = tripletB[0][2];

    if (colsA != rowsB) {
        printf("Matrices dimensions do not match for multiplication.\n");
        return;
    }

    int **result = (int **)malloc((nonZeroesA * nonZeroesB + 1) * sizeof(int *));
    for (int i = 0; i <= nonZeroesA * nonZeroesB; i++) {
        result[i] = (int *)malloc(3 * sizeof(int));
    }

    result[0][0] = rowsA;
    result[0][1] = colsB;
    int k = 1;

    //logic lifted from the net, dry run karke ek baar dekho.
    for (int i = 1; i <= nonZeroesA; i++) {
        for (int j = 1; j <= nonZeroesB; j++) {
            if (tripletA[i][1] == tripletB[j][0]) {
                result[k][0] = tripletA[i][0];
                result[k][1] = tripletB[j][1];
                result[k][2] = tripletA[i][2] * tripletB[j][2];
                k++;
            }
        }
    }
    //terate through the non-zero elements in tripletA and tripletB:
    //For each element in tripletA, find all matching elements in tripletB --> cotd, 
    //where the column index of tripletA matches the row index of tripletB.
    //Multiply these elements and add the product to the result triplet.

    result[0][2] = k - 1;

    printf("Resultant Triplet after Multiplication:\n");
    displayTriplet(result, k - 1);

    for (int i = 0; i <= nonZeroesA * nonZeroesB; i++) {
        free(result[i]);
    }
    free(result);
}