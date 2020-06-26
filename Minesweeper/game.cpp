#include <game.h>
#include <iostream>

using namespace std;

// Function responsible for getting user info on board size
void tGame::check_boardsize() {
        int rows, cols;
        do {
                cout << "Enter a board height: (10-30) " << endl;
                cin >> rows;
        } while (rows < 10 || rows > 30);
        do {
                cout << "Enter a board width: (10-30) " << endl;
                cin >> cols;
        } while (cols < 10 || cols > 30);
        // Adjusts the row size
        b->t.resize(rows);
        // Adjusts the column size
        for(int ii = 0; ii < rows; ii++) {
            b->t[ii].resize(cols);
        }

        b->rowl = rows;
        b->coll = cols;
}

// Function responsible for getting user info on difficulty
void tGame::check_difficulty() {
        char difficulty;
        do {
                cout << "Easy (E or e): ~12% Bombs" << endl;
                cout << "Medium (M or m): ~16% Bombs" << endl;
                cout << "Hard (H or h): ~18% Bombs" << endl;
                cout << "Enter a difficulty: " << endl;
                cin >> difficulty;
        } while (difficulty != 'E' && difficulty != 'e' && difficulty != 'M' && difficulty != 'm' && difficulty != 'H' && difficulty != 'h');
        // Calculates the number of bombs in the board given difficuty and board size
        if(difficulty == 'e' || difficulty == 'E') {
                b->bombs = (b->rowl * b->coll) * .12;
        }
        else if(difficulty == 'm' || difficulty == 'M') {
                b->bombs = (b->rowl * b->coll) * .16;
        }
        else {
                b->bombs = (b->rowl * b->coll) * .18;
        }
}

// Checks if the user would like to play another game
int tGame::play_again() {
        char response;
        do {
                cout << "Do you want to play again? (y/n) " << endl;
                cin >> response;
        } while (response != 'Y' && response != 'y' && response != 'N' && response != 'n');
        if (response == 'Y' || response == 'y') {
                return 1;
        }
        else {
                return 0;
        }
}

// Checks if user is trying to perform actions on a tile that has already had things done to it
int tGame::checktile(int r, int c, char i) {
        // Cant uncover a flagged tile
        if ((i == 'u' || i == 'U') && b->t[r-1][c-1].flag == 1) {
                return 1;
        }
        // Cant flag a shown tile
        if ((i == 'p' || i == 'P') && b->t[r-1][c-1].show == 1) {
                return 1;
        }
        // Cant uncover an already shown tile
        if ((i == 'u' || i == 'U') && b->t[r-1][c-1].show == 1) {
                return 1;
        }
        // Cant flag an already flagged tile
        if ((i == 'p' || i == 'P') && b->t[r-1][c-1].flag == 1) {
                return 1;
        }
        // Cant remove a flag if there is not flag
        if ((i == 'r' || i == 'R') && b->t[r-1][c-1].flag == 0) {
                return 1;
        }
        // If none of those things were done then move is acceptable
        else {
                return 0;
        }
}

// Function responsible for getting info on users move
void tGame::asktile(int& r, int& c, char& i) {
        do {
                do {
                        cout << "Would you like to place a flag, remove a flag, or uncover a tile: (p/r/u) " << endl;
                        cin >> i;
                } while (i != 'U' && i != 'u' && i != 'P' && i != 'p' && i != 'R' && i != 'r');
                do {
                        cin.clear();
                        cin.ignore();
                        cout << "What row: " << endl;
                        cin >> r;
                } while (r < 1 || r > b->rowl || cin.fail());
                do {
                        cin.clear();
                        cin.ignore();
                        cout << "What column: " << endl;
                        cin >> c;
                } while (c < 1 || c > b->coll || cin.fail());
        } while (checktile(r, c, i));
        return;
}

// Function responsible for getting info about first move, since first box uncovered it guaranteed not to be a bomb
void tGame::firstbox(int& row, int& col, char& item) {
                do {
                        b->drawboard();
                        asktile(row, col, item);
                        if(item == 'p' || item == 'P') {
                                b->flagtile(row-1, col-1);
                        }
                        if(item == 'r' || item == 'R') {
                                b->unflagtile(row-1, col-1);
                        }
                        if(item == 'u' || item == 'U') {
                                b->revealtile(row-1, col-1);
                        }
                } while (item != 'U' && item != 'u');
}

// Function responsible for carrying out the users move
// Returns 1 if user uncovers a bomb, otherwise returns 0
bool tGame::playermove(int row, int col, char item) {
        if(item == 'p' || item == 'P') {
                b->flagtile(row-1, col-1);
        }
        if(item == 'r' || item == 'R') {
                b->unflagtile(row-1, col-1);
        }
        if(item == 'u' || item == 'U') {
                if(b->t[row-1][col-1].bomb == 1) {
                        b->revealBoard();
                        return 1;
                }
                else {
                        b->revealtile(row-1, col-1);
                        b->check_empty(row-1, col-1);
                }
        }
        return 0;
}

// Function that is responsible for individual game flow
void tGame::play_game() {
        int row, col, n;
        char item;
        // Must get users first uncovered box before placing bombs
        firstbox(row, col, item);
        b->placebombs(row, col);
        b->check_empty(row-1, col -1);
        while(1) {
                b->drawboard();
                asktile(row, col, item);
                // Gets user input, carries out, and check if user uncovered bomb
                if(playermove(row, col, item)) {
                    cout << "You Lost!" << endl;
                    return;
                }
                // Checks for win after each consecutive move
                if(b->check_win()) {
                        cout << "You Won!" << endl;
                        return;
                }
        }
}
