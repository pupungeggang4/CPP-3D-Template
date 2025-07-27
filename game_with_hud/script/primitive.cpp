#include "general.hpp"
#include "objs.hpp"

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::setVector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Cuboid3::Cuboid3(float px, float py, float pz, float sx, float sy, float sz, float rx, float ry, float rz) {
    this->pos = Vector3(px, py, pz);
    this->size = Vector3(sx, sy, sz);
    this->rot = Vector3(rx, ry, rz);
}

ColorCuboid3::ColorCuboid3(float px, float py, float pz, float sx, float sy, float sz, float rx, float ry, float rz) : Cuboid3(px, py, pz, sx, sy, sz, rx, ry, rz) {

}

void ColorCuboid3::setColor(float r, float g, float b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}

