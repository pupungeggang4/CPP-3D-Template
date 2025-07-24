#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#ifndef __APPLE__
#include <GLFW/glfw3.h>
#else
#include <glfw/glfw3.h>
#endif
#include <SDL3/SDL.h>

#include "game.hpp"
#include "bufferdata.hpp"
#include "shader.hpp"
#include "primitive.hpp"
#include "render.hpp"