#include <tile.h>
#include <vector>
#include <iostream>

using namespace std;

// Board Class that contains a vector of Tiles and information about the board
class tBoard {
    public:
        int rowl; // Row length
        int coll; // Column length
        int bombs; // Number of Bombs
        int tilesShown; // Number of Tiles Shown
        // Constructor
        tBoard() {
            rowl = 0;
            coll = 0;
            bombs = 0;
            tilesShown = 0;
        }
        // Board Functions
        vector< vector<Tile> > t;
        void revealtile(int r, int c);
        void flagtile(int r, int c);
        void unflagtile(int r, int c);
        void drawboard();
        void drawtile(int r, int c);
        void placebombs(int r, int c);
        void check_empty(int r, int c);
        int check_win();
        bool freesquare(int r1, int r2, int r, int c);
        void revealBoard();
        void reset();
};
