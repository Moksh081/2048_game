#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int SIZE = 4;
int board[SIZE][SIZE];

// Function to initialize the game board
void initializeBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = 0;
        }
    }
    
    // Add two initial tiles with value 2
    srand(time(0)); //sets the seed for random no. generator 
    //if not call srand so rand() no. of times when we call generate same random no.
    int initialTiles = 2;
    while (initialTiles > 0) {
        int randRow = rand() % SIZE;
        int randCol = rand() % SIZE;
        if (board[randRow][randCol] == 0) {
            board[randRow][randCol] = 2;
            initialTiles--;
        }
    }
}

// Function to print the game board
void printBoard() {
    cout << "-----------------------------" << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                cout << "|    ";
            } else {
                cout << "| " << board[i][j] << "  ";
            }
        }
        cout << "|" << endl;
        cout << "-----------------------------" << endl;
    }
}

// Function to check if there are any moves left
bool canMove() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                return true;
            }
            if (j > 0 && board[i][j] == board[i][j - 1]) {
                return true;
            }
            if (i > 0 && board[i][j] == board[i - 1][j]) {
                return true;
            }
        }
    }
    return false;
}

// Function to perform a move in the specified direction
void move(int dir) {
    int deltaRow = 0, deltaCol = 0;
    
    // Set deltaRow and deltaCol based on the direction
    switch (dir) {
        case 0: // Up
            deltaRow = -1;
            break;
        case 1: // Right
            deltaCol = 1;
            break;
        case 2: // Down
            deltaRow = 1;
            break;
        case 3: // Left
            deltaCol = -1;
            break;
    }
    
    // Move tiles
    bool moved = false;
    do {
        moved = false;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                int currentRow = i + deltaRow;
                int currentCol = j + deltaCol;
                
                if (board[i][j] != 0) {
                    while (currentRow >= 0 && currentRow < SIZE && currentCol >= 0 && currentCol < SIZE) {
                        if (board[currentRow][currentCol] == 0) {
                            // Move tile to an empty cell
                            board[currentRow][currentCol] = board[i][j];
                            board[i][j] = 0;
                            i = currentRow;
                            j = currentCol;
                            moved = true;
                        } else if (board[currentRow][currentCol] == board[i][j]) {
                            // Merge tiles
                            board[currentRow][currentCol] *= 2;
                            board[i][j] = 0;
                            moved = true;
                            break;
                        } else {
                            break;
                        }
                        currentRow += deltaRow;
                        currentCol += deltaCol;
                    }
                }
            }
        }
    } while (moved);
    
    // Add a new tile (2 or 4) after each move
    int randRow, randCol;
    do {
        randRow = rand() % SIZE;
        randCol = rand() % SIZE;
    } while (board[randRow][randCol] != 0);
    board[randRow][randCol] = (rand() % 2 + 1) * 2; // Either 2 or 4
}

int main() {
    char input;
    bool gameover = false;
    
    initializeBoard();
    
    cout << "Welcome to 2048!" << endl;
    cout << "Instructions:" << endl;
    cout << "Use 'W' (up), 'A' (left), 'S' (down), 'D' (right) to move the tiles." << endl;
    cout << "Press 'Q' to quit the game." << endl;
    cout << endl;
    
    printBoard();
    
    while (!gameover) {
        cin >> input;
        switch (input) {
            case 'w':
            case 'W':
                move(0); // Up
                break;
            case 'd':
            case 'D':
                move(1); // Right
                break;
            case 's':
            case 'S':
                move(2); // Down
                break;
            case 'a':
            case 'A':
                move(3); // Left
                break;
            case 'q':
            case 'Q':
                gameover = true;
                cout << "Quitting the game..." << endl;
                break;
            default:
                cout << "Invalid input! Use W, A, S, D to move or Q to quit." << endl;
                break;
        }
        
        if (!gameover) {
            printBoard();
            if (!canMove()) {
                cout << "Game over! No more moves left." << endl;
                gameover = true;
            }
        }
    }
    
    return 0;
}

