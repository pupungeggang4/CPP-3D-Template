#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glad/glad.h>

#include <iostream>

class Game {
    public:
        SDL_Window *window;
        SDL_GLContext context;
        GLuint vao;
        GLuint program, vShader, fShader;
        int delta = 0;

        Game() {
            SDL_Init(SDL_INIT_VIDEO);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        }
};

int main() {
    Game game = Game();
    return 0;
}