#include <iostream>
using namespace std;

// colors
const int DEFAULT_BG = 40;
const int PLAYER1_BG = 46; 
const int PLAYER2_BG = 42; 
const int RED_TEXT = 31;
const int DEFAULT_TEXT = 37;

const char OPERATIONS[] = {'+', '-', '*', '/'};

struct Cell {
    char operation;
    int value;
    bool isVisited; 
    int bgColor;    
};

struct Player {
    int x, y; 
    int score;
};

// global variables
int rows = 0, cols = 0;
Player p1, p2;



void setColor(int bgColor, int textColor = DEFAULT_TEXT) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor | textColor);
#else
    cout << "\033[" << bgColor << ";" << textColor << "m";
#endif
}

void resetColor() {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
#else
    cout << "\033[0m";
#endif
}

Cell** initializeBoard(int rows, int cols) {
    Cell** board = new Cell*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new Cell[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int opIndex = rand() % 4;
            board[i][j].operation = OPERATIONS[opIndex];
            board[i][j].value = rand() % (10 + abs(rows / 2 - i) + abs(cols / 2 - j));
            board[i][j].isVisited = false;
            board[i][j].bgColor = DEFAULT_BG;
        }
    }

    // initial player positions
    board[p1.x][p1.y].isVisited = true;
    board[p1.x][p1.y].bgColor = PLAYER1_BG;

    board[p2.x][p2.y].isVisited = true;
    board[p2.x][p2.y].bgColor = PLAYER2_BG;
    return board;
}

void printCellValue(const Cell& cell) {
    if (cell.value >= 10 || cell.value <= -10) {
        cout << " " << cell.operation << " " << cell.value << " ";
    } else {
        cout << "  " << cell.operation << cell.value << "  ";
    }
}

void displayBoard(Cell** board, int rows, int cols) {
    for (int j = 0; j < cols; ++j) {
        cout << "+------";
    }
    cout << "+" << endl;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "|";

            if (p1.x == i && p1.y == j) {
                setColor(PLAYER1_BG, RED_TEXT);
                cout << "  P1  ";
            }
            else if (p2.x == i && p2.y == j) {
                setColor(PLAYER2_BG, RED_TEXT);
                cout << "  P2  ";
            }
            else if (board[i][j].isVisited) {
                setColor(board[i][j].bgColor, DEFAULT_TEXT);
                printCellValue(board[i][j]);
            }
            else {
                setColor(DEFAULT_BG, DEFAULT_TEXT);
                printCellValue(board[i][j]);
            }

            resetColor();
        }
        cout << "|" << endl;

        for (int j = 0; j < cols; ++j) {
            cout << "+------";
        }
        cout << "+" << endl;
    }
}


int main() {
    cout << "Enter the number of rows and columns: ";
    cin >> rows >> cols;

    // player one
    p1.x = 0;
    p1.y = 0;
    p1.score = 0;

    // player two
    p2.x = rows - 1;
    p2.y = cols - 1;
    p2.score = 0;
    
    Cell** board = initializeBoard(rows, cols);
    displayBoard(board, rows, cols);
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
    }
    delete[] board;

    return 0;
}