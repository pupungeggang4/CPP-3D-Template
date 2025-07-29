#pragma once
class Vector3;
class Cuboid3;
class ColorCuboid3;
class Game;

class Vector3 {
    public:
        float x, y, z;
        Vector3(float x, float y, float z);
        void setVector3(float x, float y, float z);
};

class Cuboid3 {
    public:
        Vector3 pos = Vector3(0.0, 0.0, 0.0);
        Vector3 size = Vector3(0.0, 0.0, 0.0);
        Vector3 rot = Vector3(0.0, 0.0, 0.0);
        Cuboid3(float px, float py, float pz, float sx, float sy, float sz, float rx, float ry, float rz);
};

class ColorCuboid3 : public Cuboid3 {
    public:
        using Cuboid3::Cuboid3;
        float color[3] = {0.0, 0.0, 0.0};
        ColorCuboid3(float px, float py, float pz, float sx, float sy, float sz, float rx, float ry, float rz); 
        void setColor(float r, float g, float b);
};

class Game {
    public:
        bool running = true; float scale;
        int success; char infoLog[2048];
        GLuint program, vShader, fShader;
        GLint luModeV, luModeF, luMPos, luMSize, luMRot, luCProj, luCPos, luCRot, luColor, luLightD;
        GLint laPosition, laTexcoord, laNormal;
        GLuint vao, bTriangle, bHUD, bHUDIndex, bCuboid, bCuboidIndex, texture;
        SDL_Window *window; SDL_GLContext context; SDL_Surface *uiSurface;
        unsigned int lastUpdate = 0, current = 0, delta = 16, fps = 60;
        std::vector<ColorCuboid3> c;

        Game();
        void run();
        void gameGLInit();
        void gameSDLInit();
        void loop();
};

void renderColorCuboid(Game *game, ColorCuboid3 *cuboid);
void renderHUD(Game *game);
