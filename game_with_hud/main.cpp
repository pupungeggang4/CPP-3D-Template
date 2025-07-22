#include "script/general.hpp"

class Game {
    public:
        GLuint program, vShader, fShader;
        GLuint vao;
        Game() {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            //glfwWindowHint(GLFW_OPENGL);
            SDL_Init(SDL_INIT_VIDEO);
        }
};

int main(int argc, char *argv[]) {
    Game game = Game();
    return 0;
}