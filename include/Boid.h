#ifndef BOID_H
#define BOID_H
#include <string>
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"


// pre declare the Flock
class Flock;

class Boid
{
public:
    Boid(ngl::Vec3 pos, Flock *ting);
    ~Boid() = default;
    void update();
    void steering();
    void attract();
    void arrive();
    void draw() const;
    void ApplyForce( ngl::Vec3 const & x );
    ngl::Vec3 getPos() const { return m_position; }
    ngl::Vec3 getTarget() const { return m_target; }
    float getSize() const { return m_size; }

private:
    bool m_arrived = false;
    float m_maxspeed = 0.00001f;
    float m_maxforce = 0.00001f;
    float m_size;
    /// \brief m_velocity of the boid
    ngl::Vec3 m_velocity;
    /// \brief des,
    ngl::Vec3 m_destination;
    /// \brief acceleration
    ngl::Vec3 m_acceleration;
    /// \brief m_position
    ngl::Vec3 m_position;
    ngl::Vec3 m_target;
    /// \brief ScaleVec
    /// \param v
    /// \param limlen
    void ScaleVec(ngl::Vec3 * v, float limlen);
    const Flock *m_ting;
};



#endif // BOID_H
