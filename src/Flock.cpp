#include "NGLScene.h"
#include "Boid.h"
#include "WindowParams.h"
#include "Flock.h"
#include <QGuiApplication>
#include <QMouseEvent>
#include <stdio.h>
#include "time.h"



#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Random.h>
#include <math.h>

Flock::Flock(const int num, ngl::Vec3 pos)
{

     ngl::Random *rand=ngl::Random::instance();




    for(int i;i<num;i++)
    {
        ngl::Vec3 newpos = ngl::Vec3(rand->getRandomVec3());

        newpos.m_y = 0;
        auto temp =Boid(newpos, this);
        std::cout<<"creating new boid in Flock at point: "<<newpos<<".\n";
        m_flock.push_back(temp);


    }
}



void Flock::draw() const
{
    for(auto &p : m_flock)
    {
        p.draw();
    }
}

void Flock::update()
{
    for(auto &p:m_flock)
    {
        p.update();
    }
}
