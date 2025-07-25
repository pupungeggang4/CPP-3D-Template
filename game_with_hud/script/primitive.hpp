#pragma once
#include "general.hpp"

class Vector3 {
    public:
        float x, y, z;
        Vector3(float x, float y, float z);
        void setVector3(float x, float y, float z);
};

class Cuboid3 {
    public:
        Vector3 pos = Vector3(0, 0, 0);
        Vector3 size = Vector3(0, 0, 0);
        Vector3 rot = Vector3(0, 0, 0);
        Cuboid3(float px, float py, float pz, float sx, float sy, float sz, float rx, float ry, float rz);
};