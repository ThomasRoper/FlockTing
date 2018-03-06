#ifndef BOID_H
#define BOID_H
#include <string>
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"
struct Boid
{
    float size;
    ngl::Vec3 vel;
    ngl::Vec3 pos;
    ngl::Vec4 col;
    int life = 0;
    int Death;
    bool respawn = false;
};




#endif // BOID_H
