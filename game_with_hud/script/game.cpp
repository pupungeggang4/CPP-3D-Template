#include "general.hpp"
#include "objs.hpp"

Game::Game() {
    std::srand((unsigned int)std::time(NULL));

    gameSDLInit();
    gameGLInit();

    for (int i = 0; i < 10; i++) {
        float x = std::rand() % 200 / 200.0 * 2.0 - 1.0;
        float y = std::rand() % 200 / 200.0 * 2.0 - 1.0;
        float z = std::rand() % 200 / 200.0 * 2.0;
        c.push_back(ColorCuboid3(x, y, z, 0.4, 0.4, 0.4, 0.0, 0.0, 0.0));
        c[i].setColor(float(std::rand()) / RAND_MAX, float(std::rand()) / RAND_MAX, float(std::rand()) / RAND_MAX);
    }
}

void Game::gameGLInit() {
    std::ifstream f;
    f.open("shader/vertex.vert");
    std::stringstream vSourceSS;
    vSourceSS << f.rdbuf();
    std::string vSourceStr = vSourceSS.str();
    vSourceStr.append(1, 0);
    const GLchar *vSource = vSourceStr.c_str();
    f.close();

    f.open("shader/fragment.frag");
    std::stringstream fSourceSS;
    fSourceSS << f.rdbuf();
    std::string fSourceStr = fSourceSS.str();
    fSourceStr.append(1, 0);
    const GLchar *fSource = fSourceStr.c_str();
    f.close();

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vSource, NULL);
    glCompileShader(vShader);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fSource, NULL);
    glCompileShader(fShader);
    program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 2048, NULL, infoLog);
        std::cout << "v " << infoLog << std::endl;
    }
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 2048, NULL, infoLog);
        std::cout << "f " << infoLog << std::endl;
    }

    luModeV = glGetUniformLocation(program, "u_mode_v");
    luModeF = glGetUniformLocation(program, "u_mode_f");
    luMPos = glGetUniformLocation(program, "u_m_pos");
    luMSize = glGetUniformLocation(program, "u_m_size");
    luMRot = glGetUniformLocation(program, "u_m_rot");
    luCProj = glGetUniformLocation(program, "u_c_proj");
    luCPos = glGetUniformLocation(program, "u_c_pos");
    luCRot = glGetUniformLocation(program, "u_c_rot");
    luColor = glGetUniformLocation(program, "u_color");
    luLightD = glGetUniformLocation(program, "u_light_d");

    laPosition = glGetAttribLocation(program, "a_position");
    laTexcoord = glGetAttribLocation(program, "a_texcoord");
    laNormal = glGetAttribLocation(program, "a_normal");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &bTriangle);
    glGenBuffers(1, &bHUD);
    glGenBuffers(1, &bCuboid);
    glGenBuffers(1, &bHUDIndex);
    glGenBuffers(1, &bCuboidIndex);

    glBindBuffer(GL_ARRAY_BUFFER, bTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bTriangleData), bTriangleData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, bHUD);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bHUDData), bHUDData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bHUDIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bHUDData), bHUDData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, bCuboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bCuboidData), bCuboidData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bCuboidIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bCuboidIndexData), bCuboidIndexData, GL_STATIC_DRAW);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Game::gameSDLInit() {    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    window = SDL_CreateWindow("Triangle Example", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    #ifndef __APPLE__
    scale = SDL_GetWindowDisplayScale(window);
    #else
    scale = 1;
    #endif
    SDL_SetWindowSize(window, 800 * scale, 600 * scale);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    context = SDL_GL_CreateContext(window);
    gladLoadGL();
    uiSurface = SDL_CreateSurface(800, 600, SDL_PIXELFORMAT_RGBA8888);
}

void Game::run() {
    while (running) {
        current = SDL_GetTicks();
        delta = current - lastUpdate;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                std::cout << "(" << event.button.x / scale << ", " << event.button.y / scale << ")" <<  std::endl;
            }
        }

        if (delta >= 1000 / fps) {
            lastUpdate = current;
            loop();
        }
    }
}

void Game::loop() {
    SDL_Rect rect = {0, 0, 40, 40};
    Uint32 color = 0xFFFFFFFF;
    SDL_FillSurfaceRect(uiSurface, NULL, 0x00000000);
    SDL_FillSurfaceRect(uiSurface, &rect, 0xFFFFFFFF);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(vao);
    glUniform1i(luModeV, 0);
    glUniform1i(luModeF, 0);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, uiSurface->w, uiSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, uiSurface->pixels);
    
    glBindBuffer(GL_ARRAY_BUFFER, bHUD);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bHUDIndex);
    glVertexAttribPointer(laPosition, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
    glVertexAttribPointer(laTexcoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(laPosition);
    glEnableVertexAttribArray(laTexcoord);
    glDisableVertexAttribArray(laNormal);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)(0));

    glEnable(GL_DEPTH_TEST);
    for (int i = 0; i < c.size(); i++) {
        c[i].rot.x += 0.5 * delta / 1000.0;
        c[i].rot.y += 0.5 * delta / 1000.0;
        renderColorCuboid(this, &c[i]);
    }

    SDL_GL_SwapWindow(window);
}