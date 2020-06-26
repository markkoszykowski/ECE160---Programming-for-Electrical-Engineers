#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>

class Tile {
    public:
        Tile() {flag = 0, bomb = 0, show = 0, num = 0;}
        int flag;
        int bomb;
        int show;
        int num;
};

class Board {
    public:
        int rowl; //the last row
        int coll; //the last column
        int bombs;
        int tilesShown;

        std::vector< std::vector<Tile> > t; //the board

        Board() {
            rowl = 0;
            coll = 0;
            bombs = 0;
            tilesShown = 0;
        }
        virtual void revealtile(int r, int c) = 0; //reveals a tile
        virtual void flagtile(int r, int c) = 0; //flags a tile
        virtual void unflagtile(int r, int c) = 0; //unflags a tile
        virtual void drawboard() = 0; //draws the board
        virtual void drawtile(int r, int c) = 0; //draws a tile
        virtual void placebombs(int r, int c) = 0; //bomb placement algorithm
        virtual void check_empty(int r, int c) = 0; //recursive revealing algorithm
        virtual int check_win() = 0; //checks win condition (tallies up tilesShown + bombs)
        virtual bool freesquare(int r1, int r2, int r, int c) = 0; //user must start on blank tile (no adjacent bombs)
        virtual void revealBoard() = 0; //for when player loses
        virtual void reset() = 0; //reset the game to play again
};

enum diffs {easy, medium, hard};

// class Record {
//     public:
//         int rows;
//         int cols;
//         diffs d;
//         double time;
//         virtual bool operator>(Record& r) = 0;
//         virtual void printRecord() = 0;
// };

class Game {
    public:
        Board* b;
        diffs d;
        //time_t begin;
        //time_t end;
        //std::vector<Record*> records;
        Game(){}
        ~Game() { delete b;}
        //virtual void print_Records() = 0;
        //virtual void check_Record() = 0;
        virtual void check_boardsize() = 0; //prompts user for size of board
        virtual void check_difficulty() = 0; //prompts user for difficulty (bomb percentage)
        virtual void play_game() = 0; //main gameplay function
        virtual int play_again() = 0; //prompts user after win/loss
        virtual int checktile(int row, int col, char item) = 0; //checks if action already taken
        virtual void asktile(int& row, int& col, char& item) = 0; //next move
        virtual void firstbox(int& row, int& col, char& item) = 0; //first move influences bomb placement
        virtual bool playermove(int row, int col, char item) = 0; //gameflow function
};
