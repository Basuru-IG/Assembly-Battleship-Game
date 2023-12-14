#include <iostream>
using namespace std;

const int ROWS = 7;
const int COLS = 7;

void displayBoard(int board[][COLS]) {
    cout << "Current Board:" << endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValidPosition(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

bool isOverlap(int board[][COLS], int rowBow, int colBow, int rowStern, int colStern) {
    for (int i = rowBow; i <= rowStern; ++i) {
        for (int j = colBow; j <= colStern; ++j) {
            if (board[i][j] == 1) {
                return true; 
            }
        }
    }
    return false; 
}
bool areAllShipsDestroyed(int board[][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == 1) {
                return false; 
            }
        }
    }
    return true; 
}
void setupShips(int board[][COLS], int player) {

    cout << "Player " << player << ", enter ship locations (rowBow colBow rowStern colStern):" << endl;
    for (int i = 0; i < 1; ++i) {
        int rowBow, colBow, rowStern, colStern;
        bool validInput = false;

        while (!validInput) {
            cin >> rowBow >> colBow >> rowStern >> colStern;

            if (!isValidPosition(rowBow, colBow) || !isValidPosition(rowStern, colStern)) {
                cout << "Invalid position. Please enter valid coordinates within the board." << endl;
            } else if (isOverlap(board, rowBow, colBow, rowStern, colStern)) {
                cout << "Ships cannot overlap. Please enter new coordinates." << endl;
            } else {
                validInput = true;
            }
        }

        for (int r = rowBow; r <= rowStern; ++r) {
            for (int c = colBow; c <= colStern; ++c) {
                board[r][c] = 1; 
            }
        }
        displayBoard(board); 
    }
}

int main() {
    int player1Board[ROWS][COLS] = {0}; 
    int player2Board[ROWS][COLS] = {0};

    setupShips(player1Board, 1);

    setupShips(player2Board , 2);

    int player1Hits = 0, player1Misses = 0;
    int player2Hits = 0, player2Misses = 0;

    int currentPlayer = 1; 
    bool gameOver = false;

    while (!gameOver) {
        int row, col;
        cout << "Player " << currentPlayer << ", enter coordinates to attack (row col): ";
        cin >> row >> col;

        if (!isValidPosition(row, col)) {
            cout << "Invalid coordinates. Please enter valid coordinates within the board." << endl;
            continue;
        }

        int *opponentBoard;
        int *currentPlayerHits;
        int *currentPlayerMisses;

        if (currentPlayer == 1) {
            opponentBoard = &player2Board[0][0];
            currentPlayerHits = &player1Hits;
            currentPlayerMisses = &player1Misses;
        } else {
            opponentBoard = &player1Board[0][0];
            currentPlayerHits = &player2Hits;
            currentPlayerMisses = &player2Misses;
        }

        int index = row * COLS + col; 
        if (opponentBoard[index] == 1) {
            cout << "HIT!" << endl;
            opponentBoard[index] = 0;
            (*currentPlayerHits)++;
        } else {
            cout << "MISS!" << endl;
            (*currentPlayerMisses)++;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        if (areAllShipsDestroyed(player2Board)) {
            gameOver = true;
            cout << "Game Over! Player 1 wins!" << endl;
        } else if (areAllShipsDestroyed(player1Board)) {
            gameOver = true;
            cout << "Game Over! Player 2 wins!" << endl;
        }
    }


    return 0;
}
