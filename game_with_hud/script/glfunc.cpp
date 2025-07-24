#include "glfunc.hpp"

void g(Game game) {
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

    game.vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(game.vShader, 1, &vSource, NULL);
    glCompileShader(game.vShader);
    game.fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(game.fShader, 1, &fSource, NULL);
    glCompileShader(game.fShader);
    game.program = glCreateProgram();
    glAttachShader(game.program, game.vShader);
    glAttachShader(game.program, game.fShader);
    glLinkProgram(game.program);

    glGetShaderiv(game.vShader, GL_COMPILE_STATUS, &game.success);
    if (!game.success) {
        glGetShaderInfoLog(game.vShader, 2048, NULL, game.infoLog);
        std::cout << "v " << game.infoLog << std::endl;
    }
    glGetShaderiv(game.fShader, GL_COMPILE_STATUS, &game.success);
    if (!game.success) {
        glGetShaderInfoLog(game.fShader, 2048, NULL, game.infoLog);
        std::cout << "f " << game.infoLog << std::endl;
    }

    game.luModeV = glGetUniformLocation(game.program, "u_mode_v");
    game.luModeF = glGetUniformLocation(game.program, "u_mode_f");
    game.luMPos = glGetUniformLocation(game.program, "u_m_pos");
    game.luMSize = glGetUniformLocation(game.program, "u_m_size");
    game.luMRot = glGetUniformLocation(game.program, "u_m_rot");
    game.luColor = glGetUniformLocation(game.program, "u_color");
    game.luLightD = glGetUniformLocation(game.program, "u_light_d");

    game.laPosition = glGetAttribLocation(game.program, "a_position");
    game.laTexcoord = glGetAttribLocation(game.program, "a_texcoord");
    game.laNormal = glGetAttribLocation(game.program, "a_normal");

    glGenVertexArrays(1, &game.vao);
    glBindVertexArray(game.vao);
    glGenBuffers(1, &game.bTriangle);
    glGenBuffers(1, &game.bHUD);
    glGenBuffers(1, &game.bCuboid);
    glGenBuffers(1, &game.bHUDIndex);
    glGenBuffers(1, &game.bCuboidIndex);

    glBindBuffer(GL_ARRAY_BUFFER, game.bTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bTriangleData), bTriangleData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, game.bHUD);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bHUDData), bHUDData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, game.bHUDIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bHUDData), bHUDData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, game.bCuboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bCuboidData), bCuboidData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, game.bCuboidIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bCuboidIndexData), bCuboidIndexData, GL_STATIC_DRAW);
}