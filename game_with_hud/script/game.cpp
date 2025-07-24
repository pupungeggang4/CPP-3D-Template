#include "general.hpp"
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

    gameGLInit();

    SDL_Init(SDL_INIT_VIDEO);

    std::cout << 2 << std::endl;
}

void Game::gameGLInit() {
    std::ifstream f;
    f.open("shader/vertex.vert");
    std::stringstream vSourceStr;
    vSourceStr << f.rdbuf();
    const GLchar *vSource = vSourceStr.str().c_str();
    f.close();

    f.open("shader/fragment.frag");
    std::stringstream fSourceStr;
    fSourceStr << f.rdbuf();
    const GLchar *fSource = fSourceStr.str().c_str();
    f.close();

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSource, NULL);
    glCompileShader(vShader);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSource, NULL);
    glCompileShader(fShader);
    program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, vShader);
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

    float xscale, yscale;
    monitor = glfwGetPrimaryMonitor();
    glfwGetWindowContentScale(window, &xscale, &yscale);
    glViewport(0, 0, 800 * xscale, 600 * yscale);
}

void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        current = SDL_GetTicks();
        delta = current - lastUpdate;
        if (delta >= 1000 / fps) {
            lastUpdate = current;
            this->loop();
        }
    }
}

void Game::loop() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);

    renderCuboid(this, &c);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::cbWindowSizeChange(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void Game::cbKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {

}