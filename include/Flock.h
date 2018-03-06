#ifndef FLOCK_H
#define FLOCK_H

#include <ngl/Vec3.h>
#include <vector>
#include <ngl/SimpleVAO.h>
#include <memory>
#include "Boid.h"
class Emitter
{
  public :
    Emitter(ngl::Vec3 _pos, size_t nParticles);
    void draw();
    void update();
    void updatePosition(ngl::Real _dx, ngl::Real _dy, ngl::Real _dz);
  private :

    //void resetParticle(Particle &io_p);

    std::vector<Boid> m_flock;
    ngl::Vec3 m_pos;
    std::unique_ptr<ngl::AbstractVAO> m_vao;
};


#endif

