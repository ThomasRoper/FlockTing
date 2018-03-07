#ifndef BOID_H
#define BOID_H
#include <string>
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"

struct Boid
{
    float size;
    ngl::Vec3 vel;
    ngl::Vec3 des;
    ngl::Vec3 acceleration;
    ngl::Vec3 pos;
    ngl::Vec4 col;
    int life = 0;
    int Death;
    int maxspeed = 0.05;
    int maxforce = 0.05;
    bool respawn = false;
    void init();
    void update();
    void steering();
    void ScaleVec(ngl::Vec3* v, float limlen);
    void ApplyForce(ngl::Vec3 x);

};




#endif // BOID_H
