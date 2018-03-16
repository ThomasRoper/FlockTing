#ifndef FLOCK_H
#define FLOCK_H

#include <ngl/Vec3.h>
#include <vector>
#include <ngl/SimpleVAO.h>
#include <memory>
#include "Boid.h"
#include <ngl/Camera.h>



class Flock
{
  public :
    Flock(const int num, ngl::Vec3 pos);
    void draw() const;
    void update();
    void updatePosition();
    inline void setShaderName(const std::string &_n){m_shaderName=_n;}
    inline const std::string getShaderName()const {return m_shaderName;}
    inline void setCam(ngl::Camera *_cam){m_cam=_cam;}
    inline ngl::Camera * getCam()const {return m_cam;}

    inline void setGlobalTransform(const ngl::Mat4 &_t){m_globalMouseTX=_t;}
    inline const ngl::Mat4 & getGlobalTransform() const { return m_globalMouseTX;}
  private :

    //void resetParticle(Particle &io_p);
    std::string m_shaderName;
    std::vector<Boid> m_flock;
    ngl::Vec3 m_pos;
    std::unique_ptr<ngl::AbstractVAO> m_vao;
     ngl::Camera *m_cam;
    ngl::Mat4 m_globalMouseTX;
};


#endif

