#include "script/general.hpp"

class Game {
    public:
        GLuint program, vShader, fShader;
        GLuint vao;
        GLFWwindow* window;
        unsigned int lastUpdate = 0, current = 0, delta = 16, fps = 60;

        Game() {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
            window = glfwCreateWindow(800, 600, "OpenGL 3D With HUD Template", NULL, NULL);
            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);
            glfwSetFramebufferSizeCallback(window, cbWindowSizeChange);
            glfwSetKeyCallback(window, cbKeyPress);
            gladLoadGL();
            SDL_Init(SDL_INIT_VIDEO);
        }

        void run() {
            while (!glfwWindowShouldClose(window)) {
                current = SDL_GetTicks();
                delta = current - lastUpdate;
                if (delta >= 1000 / fps) {
                    lastUpdate = current;
                    loop();
                }
            }
        }

        void loop() {
            glClearColor(0.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        static void cbWindowSizeChange(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
            glClearColor(0.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSwapBuffers(window);
        }

        static void cbKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {

        }
};

int main(int argc, char *argv[]) {
    Game game = Game();
    game.run();
    return 0;
}