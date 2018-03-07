#ifndef FLOCK_H
#define FLOCK_H

#include <ngl/Vec3.h>
#include <vector>
#include <ngl/SimpleVAO.h>
#include <memory>
#include "Boid.h"
class Flock
{
  public :
    Flock(const int num, ngl::Vec3 pos);
    void draw();
    void update();
    void updatePosition();
  private :

    //void resetParticle(Particle &io_p);

    std::vector<Boid> m_flock;
    ngl::Vec3 m_pos;
    std::unique_ptr<ngl::AbstractVAO> m_vao;
};


#endif

