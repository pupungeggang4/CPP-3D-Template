#include "script/general.hpp"

class Game {
    public:
        int success;
        char infoLog[2048];
        GLuint program, vShader, fShader;
        GLint luColor, luModeV, luModeF;
        GLint laPosition;
        GLuint vao, bTriangle;
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
            std::cout << fSourceStr.str().c_str() << std::endl;
            f.close();

            vShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vShader, 1, &vSource, NULL);
            glCompileShader(vShader);
            fShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fShader, 1, &fSource, NULL);
            glCompileShader(fShader);
            program = glCreateProgram();
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

            luColor = glGetUniformLocation(program, "u_color");
            luModeV = glGetUniformLocation(program, "u_mode_v");
            luModeF = glGetUniformLocation(program, "u_mode_f");
            laPosition = glGetAttribLocation(program, "a_position");

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            glGenBuffers(1, &bTriangle);
            glBindBuffer(GL_ARRAY_BUFFER, bTriangle);
            glBufferData(GL_ARRAY_BUFFER, sizeof(bTriangleData), bTriangleData, GL_STATIC_DRAW);

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
            glUseProgram(program);

            glUniform1i(luModeV, 0);
            glUniform1i(luModeF, 1);
            glUniform3f(luColor, 0.0, 1.0, 0.0);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, bTriangle);
            glVertexAttribPointer(laPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
            glEnableVertexAttribArray(laPosition);
            glDrawArrays(GL_TRIANGLES, 0, 3);

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
