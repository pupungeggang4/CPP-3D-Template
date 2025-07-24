#pragma once
#include "general.hpp"
#include "primitive.hpp"
#include "shader.hpp"
#include "bufferdata.hpp"
#include "render.hpp"

class Game {
    public:
        int success;
        char infoLog[2048];
        GLuint program, vShader, fShader;
        GLint luModeV, luModeF, luMPos, luMSize, luMRot, luCProj, luCPos, luCRot, luColor, luLightD;
        GLint laPosition, laTexcoord, laNormal;
        GLuint vao, bTriangle, bHUD, bHUDIndex, bCuboid, bCuboidIndex;
        GLFWwindow* window;
        GLFWmonitor* monitor;
        unsigned int lastUpdate = 0, current = 0, delta = 16, fps = 60;
        Cuboid3 c = Cuboid3(0.0, 0.0, 1.0, 0.2, 0.2, 0.2, 0.0, 0.0, 0.0);

        Game();
        void run();
        void gameGLInit();
        void loop();
        static void cbWindowSizeChange(GLFWwindow* window, int width, int height);
        static void cbKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
};