#include "script/general.hpp"
#include "script/game.hpp"

int main(int argc, char *argv[]) {
    Game game = Game();
    game.run();
    glfwDestroyWindow(game.window);
    glfwTerminate();
    return 0;
}
