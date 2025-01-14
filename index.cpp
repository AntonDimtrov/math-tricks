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
int currentPlayer = 1;


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

Cell** initializeBoard() {
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

void switchPlayer() {
    currentPlayer = currentPlayer == 1 ? 2 : 1;
}

void displayBoard(Cell** board) {
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

bool isValidMove(Cell** board, int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols && !board[x][y].isVisited;
}

bool hasValidMoves(Cell** board, int x, int y) {
    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
    for (int i = 0; i < 8; ++i) {
        if (isValidMove(board, x + dx[i], y + dy[i])) {
            return true;
        }
    }
    return false;
}


void makeMove(Cell** board, Player& p, string direction) {

    
    int dx = 0, dy = 0;
        if (direction == "u") dx = -1;
        else if (direction == "d") dx = 1;
        else if (direction == "r") dy = 1;
        else if (direction == "l") dy = -1;
        else if (direction == "ur") dx = -1, dy = 1;
        else if (direction == "ul") dx = -1, dy = -1;
        else if (direction == "dr") dx = 1, dy = 1;
        else if (direction == "dl") dx = 1, dy = -1;

        int nx = p.x + dx;
        int ny = p.y + dy;

        if (isValidMove(board, nx, ny)) {
            p.x = nx;
            p.y = ny;
            // update score
            board[nx][ny].isVisited = true;
            board[nx][ny].bgColor = currentPlayer == 1 ? PLAYER1_BG : PLAYER2_BG;
            switchPlayer();
        } else {
            cout << "Invalid move!" << endl;
        }
}

void playGame(Cell** board) {
    while (true) {
        displayBoard(board);
        Player& p = currentPlayer==1 ? p1 : p2;

        if (!hasValidMoves(board,p.x, p.y)) {
            cout << "No valid moves for Player " << currentPlayer << "! Game Over!" << endl;
            cout << "Player 1 Score: " << p1.score << ", Player 2 Score: " << p2.score << endl;
            cout << (p1.score > p2.score ? "Player 1 Wins!" : p1.score < p2.score ? "Player 2 Wins!" : "It's a Tie!") << endl;
            
        }

        string direction;
        cout << "Player " << currentPlayer << "'s turn. Enter move: (u, d, r, l, ur, ul, dr, dl): ";
        cin >> direction;

       makeMove(board, p, direction);
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
    
    Cell** board = initializeBoard();
    
    playGame(board);
    
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
    }
    delete[] board;

    return 0;
}