#include "game.hpp"

Game::Game() {
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

    glStart(this);

    SDL_Init(SDL_INIT_VIDEO);
}

void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        current = SDL_GetTicks();
        delta = current - lastUpdate;
        if (delta >= 1000 / fps) {
            lastUpdate = current;
            loop();
        }
    }
}

void Game::loop() {
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, bTriangle);
    glVertexAttribPointer(laPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(laPosition);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::cbWindowSizeChange(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void Game::cbKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {

}