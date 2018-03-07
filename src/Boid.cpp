#include "NGLScene.h"
#include "Boid.h"
#include "WindowParams.h"
#include <QGuiApplication>
#include <QMouseEvent>


#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <math.h>

void Boid::init()
{
   pos = ngl::Vec3(0,0,0);
   size = 0.1;
}

void Boid::update()
{
    //think about what to do
   steering();

   //add change in acceleration
   vel + acceleration;

   //limit the velocity
   ScaleVec(&vel, maxspeed);

   //if (vel > maxspeed)vel = maxspeed;
   pos.m_x += vel.m_x;
   pos.m_y += vel.m_y;
   pos.m_z += vel.m_z;


   life += 1;
   if (life > 100)
   {
        pos = ngl::Vec3(0,0,0);
        life = 0;
   }

   acceleration = ngl::Vec3(0,0,0);
}

void Boid::steering()
{
    //find the desired direction
    ngl::Vec3 desired = ngl::Vec3(0,10000,0) - pos;

    //set desired's magnitude to maxspeed
    ScaleVec(&desired,maxspeed);

    //then minus velocity off of desired
    des = desired - vel;

    //then limit the force
    ScaleVec(&des,maxforce);

    //then add to accelleration
    ApplyForce(des);
}

void Boid::ScaleVec(ngl::Vec3* v, float limlen)
{
   float vlen = sqrt((v->m_x*v->m_x) + (v->m_y*v->m_y)+ (v->m_z*v->m_z));
   float ratio = (limlen/vlen);
   *v *= ratio;
}

void Boid::ApplyForce(ngl::Vec3 x)
{
    acceleration += x;
}







