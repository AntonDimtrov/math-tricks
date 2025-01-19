#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

// colors
const int DEFAULT_BG = 0; // black BG
const int PLAYER1_BG = 1; // blue BG
const int PLAYER2_BG = 2; // green BG
const int RED_TEXT = 6;   // red text
const int DEFAULT_TEXT = 7; // white text

const char OPERATIONS[] = { '+', '-', '*', '/' };

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
    int colorAttribute = (bgColor << 4) | textColor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorAttribute);
}

void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT);
}

void clearConsole() {
    system("cls");
}

Cell** initializeBoard() {
    Cell** board = new Cell * [rows];
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
    board[0][0].value = 1;
    board[0][0].operation = '*';
    board[rows-1][cols-1].value = 1;
    board[rows-1][cols-1].operation = '*';
    

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
    }
    else {
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
    return x >= 0 && x < rows&& y >= 0 && y < cols && !board[x][y].isVisited;
}

bool hasValidMoves(Cell** board, int x, int y) {
    int dx[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1 };
    for (int i = 0; i < 8; ++i) {
        if (isValidMove(board, x + dx[i], y + dy[i])) {
            return true;
        }
    }
    return false;
}

int updateScore(int score, char operation, int value) {
    switch (operation) {
    case '+': return score + value;
    case '-': return score - value;
    case '*': return score * value;
    case '/': return (value != 0) ? score / value : score;
    default: return score;
    }
}

void saveGame(const string& filename, Cell** board) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for saving!" << endl;
        return;
    }

    // save turn
    outFile << currentPlayer << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int state;
            if (p1.x == i && p1.y == j) {
                state = 1; // player 1
            }
            else if (p2.x == i && p2.y == j) {
                state = 2; // player 2
            }
            else if (board[i][j].bgColor == PLAYER1_BG) {
                state = -1; // visited by player 1
            }
            else if (board[i][j].bgColor == PLAYER2_BG) {
                state = -2; // visited by player 2
            }
            else {
                state = 0; // unvisited cell
            }
            outFile << state << " ";
        }
        outFile << "\n";
    }

    outFile.close();
}



void loadGame(const string& filename, Cell** board) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file for loading!" << endl;
        return;
    }

    // load turn
    inFile >> currentPlayer;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int state;
            inFile >> state;
            if (state == 1) {
                board[i][j].isVisited = true;
                p1.x = i;
                p1.y = j;
                board[i][j].bgColor = PLAYER1_BG;
            }
            else if (state == 2) {
                board[i][j].isVisited = true;
                p2.x = i;
                p2.y = j;
                board[i][j].bgColor = PLAYER2_BG;
            }
            else if (state == -1) {
                board[i][j].isVisited = true;
                board[i][j].bgColor = PLAYER1_BG;
            }
            else if (state == -2) {
                board[i][j].isVisited = true;
                board[i][j].bgColor = PLAYER2_BG;
            }
            else {
                board[i][j].isVisited = false;
                board[i][j].bgColor = DEFAULT_BG;
            }
        }
    }


    inFile.close();
}

    

void makeMove(Cell**& board, Player& p) {
    cout << "Player " << currentPlayer << "'s turn. Enter move: (u, d, r, l, ur, ul, dr, dl): ";
    while (true) {
        string direction;
        cin >> direction;

        if (direction == "save") {
            saveGame("savegame.txt", board);
            cout << "Game saved!" << endl;
            Player& playerInTurn = currentPlayer == 1 ? p1 : p2;
            makeMove(board, playerInTurn);
            return;
        }
        else if (direction == "load") {
            loadGame("savegame.txt", board);
            clearConsole();
            displayBoard(board);
            cout << "Game loaded!" << endl;
            Player& playerInTurn = currentPlayer == 1 ? p1 : p2;
            makeMove(board, playerInTurn);
            return;
        }

        // movement logic
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
            p.score = updateScore(p.score, board[nx][ny].operation, board[nx][ny].value);
            board[nx][ny].isVisited = true;
            board[nx][ny].bgColor = currentPlayer == 1 ? PLAYER1_BG : PLAYER2_BG;
            switchPlayer();
            break;
        }
        else {
            cout << "Invalid move! Try again: ";
        }
    }
}


void playGame(Cell** board) {
    while (true) {
        clearConsole();
        displayBoard(board);
        Player& p = currentPlayer == 1 ? p1 : p2;

        if (!hasValidMoves(board, p.x, p.y)) {
            cout << "No valid moves for Player " << currentPlayer << "! Game Over!" << endl;
            cout << "Player 1 Score: " << p1.score << ", Player 2 Score: " << p2.score << endl;
            cout << (p1.score > p2.score ? "Player 1 Wins!" : p1.score < p2.score ? "Player 2 Wins!" : "It's a Tie!") << endl;
            break;
        }

        makeMove(board, p);
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