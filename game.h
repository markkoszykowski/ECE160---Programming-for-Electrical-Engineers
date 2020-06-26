#include <board.h>

// Game class that contains the functions responsible for game flow
class tGame {
    public:
        // Contains a board
        tBoard* b;
        // Constructor
        tGame() {
            b = new tBoard;
        }
        // Desctructor
        ~tGame() {
            delete b;
        }
        // Gameflow functions
        void check_boardsize();
        void check_difficulty();
        int play_again();
        int checktile(int r, int c, char i);
        void asktile(int& r, int& c, char& i);
        void firstbox(int& row, int& col, char& item);
        void play_game();
        bool playermove(int row, int col, char item);
};

