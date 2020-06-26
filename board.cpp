#include <board.h>
#include <iostream>
#include <Global.h>

using namespace std;

// Function responsile for checking if a square is within the one-box guaranteed range of first chosen box
bool tBoard::freesquare(int r1, int r2, int r, int c) {
        return abs(r1 - r) <= 1 && abs(r2 - c) <= 1;
}

// Function responsible for placing bombs pseudorandomly
void tBoard::placebombs(int row, int col) {
        int i;
        int rand1, rand2, n;
        srand(time(0));
        for(i = 0; i < bombs; i++) {
                // Continuously chooses random places to put bombs so long they are not in the "free square"
                do {
                        rand1 = rand() % rowl;
                        rand2 = rand() % coll;
                } while (freesquare(rand1, rand2, row-1, col-1) || t[rand1][rand2].bomb == 1);
                t[rand1][rand2].bomb = 1;
                // Increases the num in each of the boxes surrounding the bomb
                if(rand1 >= 1) {
                    t[rand1 - 1][rand2].num++;
                }
                if(rand2 >= 1) {
                    t[rand1][rand2 - 1].num++;
                }
                if(rand1 < rowl - 1) {
                    t[rand1 + 1][rand2].num++;
                }
                if(rand2 < coll - 1) {
                    t[rand1][rand2 + 1].num++;
                }
                if(rand1 >= 1 && rand2 >= 1) {
                    t[rand1 - 1][rand2 - 1].num++;
                }
                if(rand1 >= 1 && rand2 < coll - 1) {
                    t[rand1 - 1][rand2 + 1].num++;
                }
                if(rand1 < rowl - 1 && rand2 < coll - 1) {
                    t[rand1 + 1][rand2 + 1].num++;
                }
                if(rand1 < rowl - 1 && rand2 >= 1) {
                    t[rand1 + 1][rand2 - 1].num++;
                }
        }
}

// Function responsible for revealing a tile
void tBoard::revealtile(int r, int c) {
        t[r][c].show = 1;
        tilesShown++;
}

// Function responsible for Flagging a tile
void tBoard::flagtile(int r, int c) {
        t[r][c].flag = 1;
}

// Function responsible for Unflagging a tile
void tBoard::unflagtile(int r, int c) {
        t[r][c].flag = 0;
}

// Function responsible for drawing each tile
void tBoard::drawtile(int r, int c) {
        if(c > 0) {
            cout << YELLOW << "|" << RESET;
        }
        if(t[r][c].flag == 1) {
            cout << "  F ";
            return;
        }
        if(t[r][c].show == 0) {
            cout << "||||";
            return;
        }
        if(t[r][c].bomb == 1) {
            cout << RED << "  * " << RESET;
            return;
        }
        // Depending on the num in the tile, tile will be displayed in different colors
        switch(t[r][c].num) {
                case 1: cout << "  " << BLUE << "1 " << RESET;
                        break;
                case 2: cout << "  " << GREEN << "2 " << RESET;
                        break;
                case 3: cout << "  " << RED << "3 " << RESET;
                        break;
                case 4: cout << "  " << PINK << "4 " << RESET;
                        break;
                case 5: cout << "  " << DARKRED << "5 " << RESET;
                        break;
                case 6: cout << "  " << CYAN << "6 " << RESET;
                        break;
                case 7: cout << "  " << PURPLE << "7 " << RESET;
                        break;
                case 8: cout << "  " << BLUE << "8 " << RESET;
                        break;
                default: cout << "    ";
                        break;
        }
        return;
}

// Function responsible for drawing the board
void tBoard::drawboard() {
        int row;
        int col;
        cout << endl << "    ";
        // Draws the column numbers
        for(col = 0; col < coll; col++) {
                if(col < 9) {
                        cout << "  " << col + 1 << "  ";
                }
                else {
                        cout << " " << col + 1 << "  ";
                }
        }
        cout << endl;
        // Draws the row numbers
        for (row = 0; row < rowl; row++) {
                if (row < 9) {
                        cout << " " << row + 1 << ": ";
                }
                else {
                        cout << row + 1 << ": ";
                }
                for (col = 0; col < coll; col++) {
                        drawtile(row, col);
                }
                cout << endl;
                if (row != (rowl - 1)) {
                        cout << "    " << YELLOW;
                        for (col = 0; col < coll; col++) {
                            cout << "-----";
                        }
                        cout << RESET << endl;
                }
        }
        cout << endl;
        return;
}

// Checks if all the tiles that are not bombs are revealed (thus a win)
int tBoard::check_win() {
    return (tilesShown + bombs == rowl * coll);
}

// Function that is responsible for revealing boxes that have a num of 0
void tBoard::check_empty(int r, int c) {
    if(t[r][c].num == 0) {
        // For each box in perimeter, checks to see if already being shown, if not then shows it
        if(r-1 >= 0 && c-1 >= 0) {
            if(t[r-1][c-1].show == 1) {
                ;
            }
            else{
                revealtile(r-1, c-1);
                check_empty(r-1, c-1);
            }
        }
        if(r-1 >= 0) {
            if(t[r-1][c].show == 1) {
                ;
            }
            else {
                revealtile(r-1, c);
                check_empty(r-1, c);
            }
        }
        if(r-1 >= 0 && c+1 < coll) {
            if(t[r-1][c+1].show == 1) {
                ;
            }
            else {
                revealtile(r-1, c+1);
                check_empty(r-1, c+1);
            }
        }
        if(c+1 < coll) {
            if(t[r][c+1].show == 1) {
                ;
            }
            else {
                revealtile(r, c+1);
                check_empty(r, c+1);
            }
        }
        if(r+1 < rowl && c+1 < coll) {
            if(t[r+1][c+1].show == 1) {
                ;
            }
            else {
                revealtile(r+1, c+1);
                check_empty(r+1, c+1);
            }
        }
        if(r+1 < rowl) {
            if(t[r+1][c].show == 1) {
                ;
            }
            else {
                revealtile(r+1, c);
                check_empty(r+1, c);
            }
        }
        if(r+1 < rowl && c-1 >= 0) {
            if(t[r+1][c-1].show == 1) {
                ;
            }
            else {
                revealtile(r+1, c-1);
                check_empty(r+1, c-1);
            }
        }
        if(c-1 >= 0) {
            if(t[r][c-1].show == 1) {
                ;
            }
            else {
                revealtile(r, c-1);
                check_empty(r, c-1);
            }
        }
    }
    return;
}

// Function that is responsible for displaying entire board after player loses
void tBoard::revealBoard() {
    // For all boxes, gets ride of flags and shows them
    for (int r = 0; r < rowl; r++) {
            for (int c = 0; c < coll; c++) {
                    t[r][c].flag = 0;
                    t[r][c].show = 1;
            }
    }
    drawboard();
}

// Resets all the game perameters for next game
void tBoard::reset() {
        t.erase(t.begin(), t.end());
        rowl = 0;
        coll = 0;
        bombs = 0;
        tilesShown = 0;
}
