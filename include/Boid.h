#ifndef BOID_H
#define BOID_H
#include <string>
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"



class Boid
{
public:
    Boid();
    ~Boid() = default;
    void update();
    void steering();
    void attract();
    void arrive();
    void ApplyForce( ngl::Vec3 const & x );
    ngl::Vec3 getPos() const { return m_position; }
    float getSize() const { return m_size; }

private:
    bool m_respawn = false;
    int m_life = 0;
    float m_maxspeed = 0.03f;
    float m_maxforce = 0.02f;
    float m_size;
    /// \brief m_velocity of the boid
    ngl::Vec3 m_velocity;
    /// \brief des,
    ngl::Vec3 m_destination;
    /// \brief acceleration
    ngl::Vec3 m_acceleration;
    /// \brief m_position
    ngl::Vec3 m_position;
    /// \brief ScaleVec
    /// \param v
    /// \param limlen
    void ScaleVec(ngl::Vec3 * v, float limlen);
};



#endif // BOID_H
