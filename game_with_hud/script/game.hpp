#pragma once
#include "general.hpp"

class Game {
    public:
        int success;
        char infoLog[2048];
        GLuint program, vShader, fShader;
        GLint luModeV, luModeF, luMPos, luMSize, luMRot, luColor, luLightD;
        GLint laPosition, laTexcoord, laNormal;
        GLuint vao, bTriangle, bHUD, bHUDIndex, bCuboid, bCuboidIndex;
        GLFWwindow* window;
        unsigned int lastUpdate = 0, current = 0, delta = 16, fps = 60;

        Game();
        void run();
        void loop();

        static void cbWindowSizeChange(GLFWwindow* window, int width, int height);
        static void cbKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
};