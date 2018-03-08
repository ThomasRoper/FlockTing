#include "NGLScene.h"
#include "Boid.h"
#include "WindowParams.h"
#include <QGuiApplication>
#include <QMouseEvent>
#include <stdio.h>



#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <math.h>

Boid::Boid()
{
   m_position = ngl::Vec3(0,0,0);
   m_size = 0.2f;
}

//-------------------------------------------------------------------------------

void Boid::update()
{
    //think about what to do
   steering();

   //add change in acceleration
   m_velocity += m_acceleration;

   //limit the velocity
   ScaleVec(&m_velocity, m_maxspeed);


   m_position.m_x += m_velocity.m_x;
   m_position.m_y += m_velocity.m_y;
   m_position.m_z += m_velocity.m_z;


   m_life += 1;
   if (m_life > 500)
   {
        m_position = ngl::Vec3(0,0,0);
        m_life = 0;
   }

   m_acceleration = ngl::Vec3(0,0,0);
}

//-------------------------------------------------------------------------------

void Boid::steering()
{
    arrive();
}

//-------------------------------------------------------------------------------

void Boid::attract()
{
    //find the desired direction
    ngl::Vec3 desired = ngl::Vec3(1,1,0) - m_position;

    //set desired's magnitude to maxspeed
    ScaleVec(&desired,m_maxspeed);

    //then minus velocity off of desired
    m_destination = desired - m_velocity;

    //then limit the force
    ScaleVec(&m_destination,m_maxforce);

    //then add to accelleration
    ApplyForce(m_destination);
}

//-------------------------------------------------------------------------------

void Boid::arrive()
{
    //find the desired direction
    ngl::Vec3 desired = ngl::Vec3(-0.5,0,-1) - m_position;
    //then find its lenth
    float deslen = desired.length();
    //set desired's magnitude to maxspeed
    std::cout<<"deslen = "<<deslen<<".\n";

    if (deslen < 1.0)
    {
        float limspeed = m_maxspeed;
         ScaleVec(&desired, limspeed);
    }
    else if (deslen < 0.0)
    {
        float limspeed = 0;
         ScaleVec(&desired, limspeed);
    }
    else
    {
        ScaleVec(&desired,m_maxspeed);
    }


    //then minus velocity off of desired
    m_destination = desired - m_velocity;

    //then limit the force
    ScaleVec(&m_destination,m_maxforce);

    //then add to accelleration
    ApplyForce(m_destination);
}

//-------------------------------------------------------------------------------

void Boid::ScaleVec(ngl::Vec3 * v, float limlen)
{
   std::cout<<"limlen = "<<limlen<<"\n";
   float vlen = sqrt(((v->m_x) * (v->m_x)) + ((v->m_y) * (v->m_y)) + ((v->m_z) * (v->m_z)));
   if (vlen != 0)
   {
   float ratio = (limlen/vlen);
   std::cout<<"ratio = "<<ratio<<". x/y -> "<<limlen<<"/"<<vlen<<".\n";
   *v *= ratio;
   }
}

//-------------------------------------------------------------------------------

void Boid::ApplyForce( ngl::Vec3 const & x)
{
    m_acceleration += x;
}

//-------------------------------------------------------------------------------
