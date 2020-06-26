#include <game.h>

// General flow of program
int main() {
        // Creates a game, and continues to play it until the user claims they dont want to anymore
        tGame game;
        while(1) {
                game.check_boardsize();
                game.check_difficulty();
                game.play_game();
                if (!game.play_again()) {
                        break;
                }
                game.b->reset();
        }
        return 0;
}

