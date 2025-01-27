#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
@brief Draws the solution board with the queens placed as X

@param board: The board to be drawn
@param N: The size of the board

@return
*/
void drawBoard(int** board, int N){ 
    int i,j,k;
    for(i=0;i<N;i++){
        for(k=0;k<N;k++) printf("----");
        printf("\n|");
        for(j=0;j<N;j++){
            if(!board[i][j])
                printf("   |");
            else
                printf(" X |");
        }
        printf("\n");
    }
    for(k=0;k<N;k++) printf("----");
    printf("\n\n");
}

/*
@brief Initializes a blank board of size N

@param N: The size of the board

@return The initialized board
*/
int** initializeBoard(int N){
    int i, **board = (int**) calloc(N, sizeof(int*));
    for(i=0;i<N;i++)
        board[i] = (int*) calloc(N, sizeof(int));
    return board;
}

/*
@brief Frees the memory allocated for the board to avoid memory leaks

@param board: The board to be freed
@param N: The size of the board

@return
*/
void freeBoard(int **board, int N){
    int i;
    for(i=0;i<N;i++)
        free(board[i]);
    free(board);
}

/*
@brief Checks if the board is valid for the brute force algorithm, finds a queen and checks the row, column and diagonals of the queen to find if there is a conflict

@param board: The board to be checked
@param N: The size of the board

@return 1 if the board is valid, 0 otherwise
*/
int validBoardBruteForce(int **board, int N){
    int i,j;
    for(i=0; i<N; i++)
        for(j=0; j<N; j++){
            if(board[i][j]){
                int k,l;
                for(k=0; k<N; k++)
                    if(k!=i && board[k][j])
                        return 0;
                for(k=0; k<N; k++)
                    if(k!=j && board[i][k])
                        return 0;
                for(k=i, l=j; k>=0 && l>=0; k--, l--)
                    if(k!=i && l!=j && board[k][l])
                        return 0;
                for(k=i, l=j; k<N && l<N; k++, l++)
                    if(k!=i && l!=j && board[k][l])
                        return 0;
                for(k=i, l=j; k>=0 && l<N; k--, l++)
                    if(k!=i && l!=j && board[k][l])
                        return 0;
                for(k=i, l=j; k<N && l>=0; k++, l--)
                    if(k!=i && l!=j && board[k][l])
                        return 0;
            }
        }
    return 1;
}

/*
@brief Checks if the board is valid for Optimal_1 algorithm, knows that there is only one queen per row so checks the diagonals and the column of every queen with the queens below it

@param N: The size of the board
@param queenColumns: The columns of the queens

@return 1 if the board is valid, 0 otherwise
*/
int validBoardRowByRow(int N, int *queenColumns){
    int i, j;
    for(i=0; i<N-1; i++)
        for(j=i+1; j<N; j++)
            if((queenColumns[i] == queenColumns[j]) || ( (j-i) == abs(queenColumns[i] - queenColumns[j]) ) )
                return 0;
        
    return 1;
}


/*
@brief Checks if the board is valid for Optimal_2 algorithm, knows that there is only one queen per row and per column, so checks the diagonals of the queens with the queens below it

@param N: The size of the board
@param queenColumns: The columns of the queens

@return 1 if the board is valid, 0 otherwise
*/
int validBoard(int N, int *queenColumns){
    int i,j;
    for(i=0; i<N; i++)
        for(j=i+1; j<N; j++)
            if((j-i) == abs(queenColumns[i] - queenColumns[j]))
                return 0;
    return 1;
}

/*
@brief Checks if the column has a queen already. Used in the Optimal_2 algorithm

@param queenColumns: The columns of the queens
@param column: The column to be checked
@param queenNumber: The number of queens placed so far

@return 1 if the column has a queen, 0 otherwise
*/
int columnHasQueen(int *queenColumns, int column, int queenNumber){
    int i;
    for(i=0; i<queenNumber; i++)
        if(queenColumns[i] == column)
            return 1;
    return 0;
}

/*
@brief Checks if a queen is to be placed in a square, would it have a conflict with the queens already placed. Used in the backtracking algorithm

@param queenColumns: The columns of the queens
@param column: The column to be checked
@param queenNumber: The number of queens placed so far

@return 1 if the queen has a conflict, 0 otherwise
*/
int queenHasConflict(int *queenColumns, int column, int queenNumber){
    int i;
    for(i=0; i<queenNumber; i++)
        if((queenColumns[i] == column) || ( (queenNumber-i) == abs(queenColumns[i] - column) ) )
            return 1;
    return 0;
}

/*
@brief Places the queens on the board using brute force, tries all possible combinations of placing the queens

@param board: The board to place the queens on
@param N: The size of the board and the number of queens to be placed
@param queenNumber: The number of queens placed so far
@param startingPosition: The position to start placing the next queen

@return
*/
void placeQueenBruteForce(int **board, int N, int queenNumber, int startingPosition){
    if(queenNumber == N){
        if(validBoardBruteForce(board, N))
            drawBoard(board, N);
        return;
    }
    int row, column, i;
    for(i=startingPosition; i < N*N; i++){
        row = i / N;
        column = i % N;
        board[row][column] = 1;
        placeQueenBruteForce(board, N, queenNumber+1, i+1);
        board[row][column] = 0;
    }
}

/*
@brief Places the queens on the board using the Optimal_1 algorithm, places the queens row by row and checks if the board is valid if N amount of queens are placed

@param board: The board to place the queens on
@param N: The size of the board and the number of queens to be placed
@param queenColumns: The columns of the queens
@param queenNumber: The number of queens placed so far

@return
*/
void placeQueenRowByRow(int **board, int N, int *queenColumns, int queenNumber){
    if(queenNumber == N){
        if(validBoardRowByRow(N, queenColumns))
            drawBoard(board, N);
        return;
    }
        
    int column;
    for(column = 0; column<N; column++){
        board[queenNumber][column] = 1;
        queenColumns[queenNumber] = column;
        placeQueenRowByRow(board, N, queenColumns, queenNumber+1);
        board[queenNumber][column] = 0;
    }
}

/*
@brief Places the queens on the board using the Optimal_2 algorithm, places the queens row by row and one per column, checks if the board is valid if N amount of queens are placed

@param board: The board to place the queens on
@param N: The size of the board and the number of queens to be placed
@param queenColumns: The columns of the queens
@param queenNumber: The number of queens placed so far

@return
*/
void placeQueenRowAndColumn(int **board, int N, int *queenColumns, int queenNumber){
    if(queenNumber == N){
        if(validBoard(N, queenColumns))
            drawBoard(board, N);
        return;
    }
    int column;
    for(column = 0; column<N; column++){
        if(!columnHasQueen(queenColumns, column, queenNumber)){
            board[queenNumber][column] = 1;
            queenColumns[queenNumber] = column;
            placeQueenRowAndColumn(board, N, queenColumns, queenNumber+1);
            board[queenNumber][column] = 0;
        }
    }
}

/*
@brief Places the queens on the board using the backtracking algorithm, places the queens row by row and checks if a queen is going to have conflict with others before placing it, avoiding going after a solution that is not valid

@param board: The board to place the queens on
@param N: The size of the board and the number of queens to be placed
@param queenColumns: The columns of the queens
@param queenNumber: The number of queens placed so far

@return
*/
void placeQueenBacktracking(int **board, int N, int *queenColumns, int queenNumber){
    if(queenNumber == N){
        drawBoard(board, N);
        return;
    }
    int column;
    for(column = 0; column<N; column++){
        if(!queenHasConflict(queenColumns, column, queenNumber)){
            board[queenNumber][column] = 1;
            queenColumns[queenNumber] = column;
            placeQueenBacktracking(board, N, queenColumns, queenNumber+1);
            board[queenNumber][column] = 0;
        }
    }
}

/*
@brief Kickstarts the brute force algorithm and measures the time taken to solve the problem

@param N: The size of the board

@return The time taken to solve the problem
*/
double bruteForce(int N){
    int **board = initializeBoard(N);
    clock_t start, end;
    printf("Brute Force Solutions found:\n\n");
    start = clock();
    placeQueenBruteForce(board, N, 0, 0);
    end = clock();
    freeBoard(board, N);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

/*
@brief Kickstarts the Optimal_1 algorithm and measures the time taken to solve the problem

@param N: The size of the board

@return The time taken to solve the problem
*/
double optimized_1(int N){
    int **board = initializeBoard(N), *queenColumns = (int*) malloc(N * sizeof(int));
    clock_t start, end;
    printf("Optimized_1 Solutions found:\n\n");
    start = clock();
    placeQueenRowByRow(board, N, queenColumns, 0);
    end = clock();
    freeBoard(board, N);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

/*
@brief Kickstarts the Optimal_2 algorithm and measures the time taken to solve the problem

@param N: The size of the board

@return The time taken to solve the problem
*/
double optimized_2(int N){
    int **board = initializeBoard(N), *queenColumns = (int*) malloc(N * sizeof(int));
    clock_t start, end;
    printf("Optimized_2 Solutions found:\n\n");
    start = clock();
    placeQueenRowAndColumn(board, N, queenColumns, 0);
    end = clock();
    freeBoard(board, N);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

/*
@brief Kickstarts the backtracking algorithm and measures the time taken to solve the problem

@param N: The size of the board

@return The time taken to solve the problem
*/
double backtracking(int N){
    int **board = initializeBoard(N), *queenColumns = (int*) malloc(N * sizeof(int));
    clock_t start, end;
    printf("Backtracking Solutions found:\n\n");
    start = clock();
    placeQueenBacktracking(board, N, queenColumns, 0);
    end = clock();
    freeBoard(board, N);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int main(){
    int N = -1, choice=0;
    double bruteForceTime, optimized1Time, optimized2Time, backtrackingTime;
    printf("Welcome to the N-Queens Problem Solver\n");
    printf("Please enter the value of N: ");
    scanf("%d", &N);
    while(N < 0){
    	printf("Please give a valid input for N: ");
    	scanf("%d", &N);
	}
    do{
        printf("Please select which approach you'd like to use:\n");
        printf("1. Brute Force\n");
        printf("2. Optimized_1 \n");
        printf("3. Optimized_2\n");
        printf("4. Backtracking\n");
        printf("5. All of the above\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 0:
                break;
            case 1:
                bruteForceTime = bruteForce(N);
                printf("The time taken: %.7f\n", bruteForceTime);
                break;
            case 2:
                optimized1Time = optimized_1(N);
                printf("The time taken: %.7f\n", optimized1Time);
                break;
            case 3:
                optimized2Time = optimized_2(N);
                printf("The time taken: %.7f\n", optimized2Time);
                break;
            case 4:
                backtrackingTime = backtracking(N);
                printf("The time taken: %.7f\n", backtrackingTime);
                break;
            case 5:
                bruteForceTime = bruteForce(N);
                optimized1Time = optimized_1(N);
                optimized2Time = optimized_2(N);
                backtrackingTime = backtracking(N);
                printf("Brute Force: %.7f\n", bruteForceTime);
                printf("Optimized_1: %.7f\n", optimized1Time);
                printf("Optimized_2: %.7f\n", optimized2Time);
                printf("Backtracking: %.7f\n", backtrackingTime);
                break;
            default:
                printf("Invalid choice, please try again:\n\n");
                break;
        }
    } while(!choice);
    printf("\nShutting down...");
    return 0;
}