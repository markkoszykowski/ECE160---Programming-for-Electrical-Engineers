#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int rowl;
int coll;
char difficulty;

class Tile {
        public:
        int flag;
        int bomb;
        int show;
        int num;
};

class Board {
        public:
        Tile t[30][30];
        int bombs;
        void initboard();
        void revealtile(int r, int c);
        void flagtile(int r, int c);
        void unflagtile(int r, int c);
        void drawboard();
        void placebombs(int row, int col);
};

void Board::initboard() {
        int row, col, n;
        
        if(difficulty == 'e' || difficulty == 'E') {
                bombs = (rowl * coll) * .12;
        }
        else if(difficulty == 'm' || difficulty == 'M') {
                bombs = (rowl * coll) * .16;
        }
        else {
                bombs = (rowl * coll) * .18;
        }

        for(row = 0; row < 30; row++) {
                for (col = 0; col < 30; col++) {
                        n = 0;
                        t[row][col].flag = 0;
                        t[row][col].bomb = 0;
                        t[row][col].show = 0;
                }
        }
        
}

int freesquare(int r1, int r2, int r, int c) {
        if (r1 == r && r2 == c) {
                return 1;
        }
        if (r1 == r-1 && r2 == c-1) {
                return 1;
        }
        if (r1 == r-1 && r2 == c) {
                return 1;
        }
        if (r1 == r-1 && r2 == c+1) {
                return 1;
        }
        if (r1 == r && r2 == c+1) {
                return 1;
        }
        if (r1 == r+1 && r2 == c+1) {
                return 1;
        }
        if (r1 == r+1 && r2 == c) {
                return 1;
        }
        if (r1 == r+1 && r2 == c-1) {
                return 1;
        }
        if (r1 == r && r2 == c-1) {
                return 1;
        }
        return 0;
}

void Board::placebombs(int row, int col) {
        int i;
        int rand1, rand2, n;
        srand(time(0));
        for(i = 0; i < bombs; i++) {
                do {
                        rand1 = rand() % rowl;
                        rand2 = rand() % coll;
                } while (freesquare(rand1, rand2, row-1, col-1) || t[rand1][rand2].bomb == 1);
                t[rand1][rand2].bomb = 1;
        }
        for(row = 0; row < rowl; row++) {
                for (col = 0; col < rowl; col++) {
                        n = 0;
                        if(row - 1 >= 0 && col - 1 >= 0 && t[row-1][col-1].bomb == 1) {
                                n += 1;
                        }
                        if(row - 1 >= 0 && t[row-1][col].bomb == 1) {
                                n += 1;
                        }
                        if(row - 1 >= 0 && col + 1 < coll && t[row-1][col+1].bomb == 1) {
                                n += 1;
                        }
                        if(col + 1 < coll && t[row][col+1].bomb == 1) {
                                n += 1;
                        }
                        if(col + 1 < coll && row + 1 < rowl && t[row+1][col+1].bomb == 1) {
                                n += 1;
                        }
                        if(row + 1 < rowl && t[row+1][col].bomb == 1) {
                                n += 1;
                        }
                        if(row + 1 < rowl && col - 1 >= 0 && t[row+1][col-1].bomb == 1) {
                                n += 1;
                        }
                        if(col - 1 >= 0 && t[row][col-1].bomb == 1) {
                                n += 1;
                        }
                        t[row][col].num = n;
                }
        }

}

void Board::revealtile(int r, int c) {
        t[r][c].show = 1;
}

void Board::flagtile(int r, int c) {
        t[r][c].flag = 1;
}

void Board::unflagtile(int r, int c) {
        t[r][c].flag = 0;
}

void tileprint(Tile t[30][30], int r, int c) {
        switch(t[r][c].num) {
                case 1: printf("  \033[1;34m%i\033[0m ", t[r][c].num);
                        break;
                case 2: printf("  \033[1;32m%i\033[0m ", t[r][c].num);
                        break;
                case 3: printf("  \033[1;31m%i\033[0m ", t[r][c].num);
                        break;
                case 4: printf("  \033[1;35m%i\033[0m ", t[r][c].num);
                        break;
                case 5: printf("  \033[0;31m%i\033[0m ", t[r][c].num);
                        break;
                case 6: printf("  \033[1;36m%i\033[0m ", t[r][c].num);
                        break;
                case 7: printf("  \033[0;35m%i\033[0m ", t[r][c].num);
                        break;
                case 8: printf("  \033[0;34m%i\033[0m ", t[r][c].num);
                        break;
                default: printf("    ", t[r][c].num);
                        break;
        }
}

void Board::drawboard() {
        int row;
        int col;
        printf("\n");
        printf("    ");
        for(col = 0; col < coll; col++) {
                if(col < 9) {
                        printf("  %i  ", col + 1);
                }
                else {
                        printf(" %i  ", col + 1);
                }
        }
        printf("\n");
        for (row = 0; row < rowl; row++) {
                if (row < 9) {
                        printf(" %i: ", row + 1);
                }
                else {
                        printf("%i: ", row + 1);
                }
                if(t[row][0].flag == 1) {
                        printf("  F ");
                }
                else if (t[row][0].show == 0) {
                        printf("||||");
                }
                else if (t[row][0].show == 1) {
                        if(t[row][0].bomb == 1) {
                                printf("  \033[1;31m*\033[0;0m ");
                        }
                        else {
                                tileprint(t, row, 0);
                        }
                }
                for (col = 1; col < coll; col++) {
                        if(t[row][col].flag == 1) {
                                printf("\033[0;36m|\033[0m  F ");
                        }
                        else if (t[row][col].show == 0) {
                                printf("\033[0;36m|\033[0m||||");
                        }
                        else if (t[row][col].show == 1) {
                                if(t[row][col].bomb == 1) {
                                        printf("\033[0;36m|\033[0m \033[1;31m*\033[0;0m  ");
                                }
                                else {
                                        printf("\033[0;36m|\033[0m");
                                        tileprint(t, row, col);
                                }
                        }
                }
                printf("\n");
                if (row != (rowl - 1)) {
                        printf("    ");
                        for (col = 0; col < coll; col++) {
                                printf("\033[0;36m-----\033[0m");
                        }
                        printf("\n");
                }
        }
        printf("\n");
        return;
}

void check_boardsize() {
        do {
                cout << "Enter a board height: (10-30) " << endl;
                cin >> rowl;
        } while (rowl < 10 || rowl > 30);
        do {
                cout << "Enter a board width: (10-30) " << endl;
                cin >> coll;
        } while (coll < 10 || coll > 30);
}

void check_difficulty() {
        do {
                cout << "Easy (E or e): ~12% Bombs" << endl;
                cout << "Medium (M or m): ~16% Bombs" << endl;
                cout << "Hard (H or h): ~18% Bombs" << endl;
                cout << "Enter a difficulty: " << endl;
                cin >> difficulty;
        } while (difficulty != 'E' && difficulty != 'e' && difficulty != 'M' && difficulty != 'm' && difficulty != 'H' && difficulty != 'h');
}

int play_again() {
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

int checktile(Board b, int r, int c, char i) {
        if ((i == 'u' || i == 'U') && b.t[r-1][c-1].flag == 1) {
                return 1;
        }
        if ((i == 'p' || i == 'P') && b.t[r-1][c-1].show == 1) {
                return 1;
        }
        if ((i == 'u' || i == 'U') && b.t[r-1][c-1].show == 1) {
                return 1;
        }
        if ((i == 'p' || i == 'P') && b.t[r-1][c-1].flag == 1) {
                return 1;
        }
        if ((i == 'r' || i == 'R') && b.t[r-1][c-1].flag == 0) {
                return 1;
        }
        else {
                return 0;
        }
}

void asktile(Board b, int* r, int* c, char* i) {
        do {        
                do {
                        cout << "Would you like to place a flag, remove a flag, or uncover a tile: (p/r/u) " << endl;
                        cin >> *i;
                } while (*i != 'U' && *i != 'u' && *i != 'P' && *i != 'p' && *i != 'R' && *i != 'r');
                do {
                        cout << "What row: " << endl;
                        cin >> *r;
                } while (*r < 1 || *r > rowl);
                do {
                        cout << "What column: " << endl;
                        cin >> *c;
                } while (*c < 1 || *c > coll);
        } while (checktile(b, *r, *c, *i));
        return;
}

int checkwin(Board b) {
        int row, col;
        int n = 0;
        for (row = 0; row < rowl; row++) {
                for (col = 0; col < coll; col++) {
                        if(b.t[row][col].bomb == 0 && b.t[row][col].show == 1) {
                                n+= 1;
                        }
                }
        }
        if (n == (rowl * coll) - b.bombs) {
                return 1;
        }
        else {
                return 0;
        }
}

void checkempty(Board* b, int r, int c) {
        if(b->t[r][c].num == 0) {
                if(r-1 >= 0 && c-1 >= 0) {
                        if(b->t[r-1][c-1].show == 1) {
                                ;
                        }
                        else{
                                b->t[r-1][c-1].show = 1;
                                checkempty(b, r-1, c-1);
                        }
                }
                if(r-1 >= 0) {
                        if(b->t[r-1][c].show == 1) {
                                ;
                        }
                        else {
                                b->t[r-1][c].show = 1;
                                checkempty(b, r-1, c);
                        }
                }
                if(r-1 >= 0 && c+1 < coll) {
                        if(b->t[r-1][c+1].show == 1) {
                                ;
                        }
                        else {
                                b->t[r-1][c+1].show = 1;
                                checkempty(b, r-1, c+1);
                        }
                }
                if(c+1 < coll) {
                        if(b->t[r][c+1].show == 1) {
                                ;
                        }
                        else {
                                b->t[r][c+1].show = 1;
                                checkempty(b, r, c+1);
                        }
                }
                if(r+1 < rowl && c+1 < coll) {
                        if(b->t[r+1][c+1].show == 1) {
                                ;
                        }
                        else {
                                b->t[r+1][c+1].show = 1;
                                checkempty(b, r+1, c+1);
                        }
                }
                if(r+1 < rowl) {
                        if(b->t[r+1][c].show == 1) {
                                ;
                        }
                        else {
                                b->t[r+1][c].show = 1;
                                checkempty(b, r+1, c);
                        }
                }
                if(r+1 < rowl && c-1 >= 0) {
                        if(b->t[r+1][c-1].show == 1) {
                                ;
                        }
                        else {
                                b->t[r+1][c-1].show = 1;
                                checkempty(b, r+1, c-1);
                        }
                }
                if(c-1 >= 0) {
                        if(b->t[r][c-1].show == 1) {
                                ;
                        }
                        else {
                                b->t[r][c-1].show = 1;
                                checkempty(b, r, c-1);
                        }
                }
        }
        return;
}

void firstbox(Board *b, int *row, int *col, char *item) {
                do {
                        b->drawboard();
                        asktile(*b, row, col, item);
                        if(*item == 'p' || *item == 'P') {
                                b->flagtile((*row)-1, (*col)-1);
                        }
                        if(*item == 'r' || *item == 'R') {
                                b->unflagtile((*row)-1, (*col)-1);
                        }
                        if(*item == 'u' || *item == 'U') {
                                b->revealtile((*row)-1, (*col)-1);
                        }
                } while (*item != 'U' && *item != 'u');

}

void play_game() {
        int row, col, n;
        char item;
        Board b;
        b.initboard();
        firstbox(&b, &row, &col, &item);
        b.placebombs(row, col);
        checkempty(&b, row-1, col -1);
        while(1) {
                b.drawboard();
                asktile(b, &row, &col, &item);
                if(item == 'p' || item == 'P') {
                        b.flagtile(row-1, col-1);
                }
                if(item == 'r' || item == 'R') {
                        b.unflagtile(row-1, col-1);
                }
                if(item == 'u' || item == 'U') {
                        if(b.t[row-1][col-1].bomb == 1) {
                                for (int r = 0; r < rowl; r++) {
                                        for (int c = 0; c < coll; c++) {
                                                b.t[r][c].flag = 0;
                                                b.t[r][c].show = 1;
                                        }
                                }
                                b.drawboard();
                                cout << "You Lost!" << endl;
                                return;
                        }
                        else {
                                b.revealtile(row-1, col-1);
                                checkempty(&b, row-1, col-1);
                        }
                }
                if(checkwin(b)) {
                        cout << "You Won!" << endl;
                        return;
                }
        }
}

int main() {
        while(1) {
                check_boardsize();
                check_difficulty();
                play_game();
                if (!play_again()) {
                        break;
                }
        }
        return 0;
}
