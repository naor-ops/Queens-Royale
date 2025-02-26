/******************
Name: Naor Goral
Course: Harvard CS50
*******************/

#define _CRT_SECURE_NO_WARNINGS

/* 
grid for 8*8
A A B B C C D D
A A B B C C D D
E E F F G G H H
E E F F G G H H
I I J J K K L L
I I J J K K L L
M M N N O O P P
M M N N O O P P

grid for 10*10
A A B B C C D D E E
F F G G H H I I J J
K K L L M M N N O O
P P Q Q R R S S T T
U U V V W W X X Y Y
Z Z a a b b c c d d
e e f f g g h h i i
j j k k l l m m n n
o o p p q q r r s s
t t u u v v w w x x
*/

#include <stdio.h>

#define SIZE 20
#define GRID_SIZE 30
#define N 10

int isSafe(int board[N][N], int row, int col, int leftDiagonal[N], int rightDiagonal[N], int colCheck[N]);
int solveQueensBattle(int board[N][N], int row, int leftDiagonal[N], int rightDiagonal[N], int colCheck[N]);
void printBoard(int board[N][N]);

// Recursive
void PlaceQueensRecursive(int size, char chars[][SIZE], int queens[][SIZE]);
int column_check_recursive(int r, int col, int queens[][SIZE]);
int safe_check_recursive(int row, int col, char chars[][SIZE], int queens[][SIZE], int size, int occupied_region[]);
int solve_recursive(int row, int col, char chars[][SIZE], int queens[][SIZE], int size, int occupied_region[]);


int main()
{
    char ch = ' ';
    printf("R for Recursive only other char for both: ");
    scanf("%c", &ch);
    if (ch == 'R')
    {
        int size = 0;
        printf("Please enter the board dimensions:\n");
        scanf("%d", &size);

        printf("Please enter a %d*%d puzzle board:\n", size, size);
        char chars[SIZE][SIZE];
        int queens[SIZE][SIZE];

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                scanf(" %c", &chars[i][j]);
                queens[i][j] = 0;
            }
        }

        PlaceQueensRecursive(size, chars, queens);
    }
    else
    {
        int board[N][N] = { 0 };
        int colCheck[N] = { 0 };
        int leftDiagonal[2 * N - 1] = { 0 };
        int rightDiagonal[2 * N - 1] = { 0 };

        if (solveQueensBattle(board, 0, leftDiagonal, rightDiagonal, colCheck)) {
            printf("Solution to Queens Battle:\n");
            printBoard(board);
        }
        else {
            printf("No solution found.\n");
        }
    }
}


int isSafe(int board[N][N], int row, int col, int leftDiagonal[N], int rightDiagonal[N], int colCheck[N]) {
    // Check if the column is already occupied
    if (colCheck[col]) return 0;
    // Check if the left diagonal is already occupied
    if (leftDiagonal[row - col + N - 1]) return 0;
    // Check if the right diagonal is already occupied
    if (rightDiagonal[row + col]) return 0;
    return 1;  // The position is safe
}


// Function to solve the N-Queens problem using backtracking
int solveQueensBattle(int board[N][N], int row, int leftDiagonal[N], int rightDiagonal[N], int colCheck[N]) {
    if (row == N) {
        return 1;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, leftDiagonal, rightDiagonal, colCheck)) {
            board[row][col] = 1;
            colCheck[col] = 1;
            leftDiagonal[row - col + N - 1] = 1;
            rightDiagonal[row + col] = 1;

            if (solveQueensBattle(board, row + 1, leftDiagonal, rightDiagonal, colCheck)) {
                return 1;
            }

            board[row][col] = 0;
            colCheck[col] = 0;
            leftDiagonal[row - col + N - 1] = 0;
            rightDiagonal[row + col] = 0;
        }
    }

    return 0;  // No solution found
}


// Function to print the solution board
void printBoard(int board[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            if (board[i][j] == 1)
            {
                printf("X ");
            }
            else
            {
                printf("* ");
            }
        }
        printf("\n");
    }
}


void PlaceQueensRecursive(int size, char chars[][SIZE], int queens[][SIZE])
{
    int occupied_region[256] = { 0 };

    if (solve_recursive(0, 0, chars, queens, size, occupied_region))
    {
        printf("Solution:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (queens[i][j])
                {
                    printf("X ");
                }
                else
                {
                    printf("* ");
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("This puzzle cannot be solved.\n");
    }
}


int column_check_recursive(int row, int col, int queens[][SIZE])
{
    if (row < 0) return 1;
    if (queens[row][col]) return 0;
    return column_check_recursive(row - 1, col, queens);
}


int safe_check_recursive(int row, int col, char chars[][SIZE], int queens[][SIZE], int size, int occupied_region[])
{

    if (!column_check_recursive(row - 1, col, queens)) return 0;


    if (row > 0) {
        if (col > 0 && queens[row - 1][col - 1])
        {
            return 0;
        }
        if (col < size - 1 && queens[row - 1][col + 1])
        {
            return 0;
        }
    }


    if (occupied_region[(unsigned char)chars[row][col]])
    {
        return 0;
    }

    return 1;
}


int solve_recursive(int row, int col, char chars[][SIZE], int queens[][SIZE], int size, int occupied_region[])
{

    if (row >= size)
    {
        return 1;
    }


    if (col >= size)
    {
        return 0;
    }


    if (safe_check_recursive(row, col, chars, queens, size, occupied_region))
    {
        queens[row][col] = 1;
        occupied_region[(unsigned char)chars[row][col]] = 1;


        if (solve_recursive(row + 1, 0, chars, queens, size, occupied_region))
        {
            return 1;
        }


        queens[row][col] = 0;
        occupied_region[(unsigned char)chars[row][col]] = 0;
    }


    return solve_recursive(row, col + 1, chars, queens, size, occupied_region);
}
