#include "NGLScene.h"
#include "WindowParams.h"
#include "Flock.h"
#include <QGuiApplication>
#include <QMouseEvent>

#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>


NGLScene::NGLScene()
{
    setTitle( "Qt5 Simple NGL Demo" );
    //test = Boid();
}


NGLScene::~NGLScene()
{
    std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL( int _w, int _h )
{
    m_cam.setShape( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
    m_win.width  = static_cast<int>( _w * devicePixelRatio() );
    m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::initializeGL()
{

    // we must call that first before any other GL commands to load and link the
    // gl commands from the lib, if that is not done program will crash
    ngl::NGLInit::instance();
    glClearColor( 1.0f, 0.4f, 0.4f, 1.0f ); // Grey Background
    // enable depth testing for drawing
    glEnable( GL_DEPTH_TEST );
    // enable multisampling for smoother drawing
#ifndef USINGIOS_
    glEnable( GL_MULTISAMPLE );
#endif
    // now to load the shader and set the values
    // grab an instance of shader manager
    ngl::ShaderLib* shader = ngl::ShaderLib::instance();
    // we are creating a shader called Phong to save typos
    // in the code create some constexpr
    constexpr auto shaderProgram = "Phong";
    constexpr auto vertexShader  = "PhongVertex";
    constexpr auto fragShader    = "PhongFragment";
    // create the shader program
    shader->createShaderProgram( shaderProgram );
    // now we are going to create empty shaders for Frag and Vert
    shader->attachShader( vertexShader, ngl::ShaderType::VERTEX );
    shader->attachShader( fragShader, ngl::ShaderType::FRAGMENT );
    // attach the source
    shader->loadShaderSource( vertexShader, "shaders/PhongVertex.glsl" );
    shader->loadShaderSource( fragShader, "shaders/PhongFragment.glsl" );
    // compile the shaders
    shader->compileShader( vertexShader );
    shader->compileShader( fragShader );
    // add them to the program
    shader->attachShaderToProgram( shaderProgram, vertexShader );
    shader->attachShaderToProgram( shaderProgram, fragShader );


    // now we have associated that data we can link the shader
    shader->linkProgramObject( shaderProgram );
    // and make it active ready to load values
    ( *shader )[ shaderProgram ]->use();
    // the shader will use the currently active material and light0 so set them
    ngl::Material m( ngl::STDMAT::GOLD );
    // load our material values to the shader into the structure material (see Vertex shader)
    m.loadToShader( "material" );
    // Now we will create a basic Camera from the graphics library
    // This is a static camera so it only needs to be set once
    // First create Values for the camera position
    ngl::Vec3 from( 1, 1, 1 );
    ngl::Vec3 to( 0, 0, 0 );
    ngl::Vec3 up( 0, 1, 0 );
    // now load to our new camera
    m_cam.set( from, to, up );
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    m_cam.setShape( 45.0f, 720.0f / 576.0f, 0.05f, 350.0f );
    shader->setUniform( "viewerPos", m_cam.getEye().toVec3() );
    // now create our light that is done after the camera so we can pass the
    // transpose of the projection matrix to the light to do correct eye space
    // transformations
    ngl::Mat4 iv = m_cam.getViewMatrix();
    iv.transpose();
    ngl::Light light( ngl::Vec3( -2, 5, 2 ), ngl::Colour( 1, 1, 1, 1 ), ngl::Colour( 1, 1, 1, 1 ), ngl::LightModes::POINTLIGHT );
    //light.setTransform( iv );
    iv.inverse().transpose();
    light.setTransform(iv);
    light.setAttenuation(1,0,0);
    light.enable();
    // load these values to the shader as well
    light.loadToShader( "light" );


    //init vao
    ngl::VAOPrimitives *mesh=ngl::VAOPrimitives::instance();
    mesh->createSphere("sphere",0.1f,10);



    ting.reset(new Flock(3,ngl::Vec3(0,0,0)));
    ting->setCam(&m_cam);
    ting->setShaderName("Phong");

    m_fpsTimer =startTimer(0);
    m_timer.start();
    //  test.init();
    //NGLScene::buildVAO( test.getPos(),test.getSize() );

}


void NGLScene::loadMatricesToShader()
{
    ngl::ShaderLib* shader = ngl::ShaderLib::instance();

    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    M            = m_mouseGlobalTX;
    MV           = m_cam.getViewMatrix() * M;
    MVP          = m_cam.getVPMatrix() * M;

    normalMatrix = MV;
    normalMatrix.inverse().transpose();
    shader->setUniform( "MV", MV );
    shader->setUniform( "MVP", MVP );
    shader->setUniform( "normalMatrix", normalMatrix );
    shader->setUniform( "M", M );
}

void NGLScene::paintGL()
{
    glViewport( 0, 0, m_win.width, m_win.height );
    // clear the screen and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//    // grab an instance of the shader manager
    ngl::ShaderLib* shader = ngl::ShaderLib::instance();
   ( *shader )[ "Phong" ]->use();

 // Rotation based on the mouse position for our global transform
    ngl::Mat4 rotX;
    ngl::Mat4 rotY;
    // create the rotation matrices
    rotX.rotateX( m_win.spinXFace );
    rotY.rotateY( m_win.spinYFace );
    // multiply the rotations
    m_mouseGlobalTX = rotX * rotY;
    // add the translations
    m_mouseGlobalTX.m_m[ 3 ][ 0 ] = m_modelPos.m_x;
    m_mouseGlobalTX.m_m[ 3 ][ 1 ] = m_modelPos.m_y;
    m_mouseGlobalTX.m_m[ 3 ][ 2 ] = m_modelPos.m_z;
    ting->setGlobalTransform(m_mouseGlobalTX);



    // get the VBO instance and draw the built in boids
    //early my stuff


    ting->draw();


    //test.update();
    //NGLScene::buildVAO(test.getPos(),test.getSize());

    // draw

    loadMatricesToShader();

    //------------------------------MYSTUFF-------------------------------------
    shader->setUniform("Colour",0.0f,0.0f,0.0f,1.0f);
    ngl::VAOPrimitives::instance()->createLineGrid("Ground", 2.0, 2.0, 8);
    ngl::VAOPrimitives::instance()->draw("Ground");
    ngl::Vec3 hi=ngl::Vec3 (1,1,1);
    ngl::VAOPrimitives::instance()->createTrianglePlane("Triangle",1.0,1.0,1,1,hi );
    ngl::VAOPrimitives::instance()->draw("Triangle");

  //  m_vao->bind();
    //shader->setUniform("MVP",MVP);

  //  m_vao->draw();


    //  ngl::Mat4 tx;
    //  tx.translate(0,2,0);
    //  MVP=m_mouseGlobalTX*m_cam.getVPMatrix()*tx;

    //  shader->setUniform("MVP",MVP);
    //  m_vao->draw();


 //   m_vao->unbind();
    //update();

}



//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent( QKeyEvent* _event )
{
    // that method is called every time the main window recives a key event.  void loadMatricesToShader();
    // we then switch on the key value and set the camera in the GLWindow
    switch ( _event->key() )
    {
    // escape key to quit
    case Qt::Key_Escape:
        QGuiApplication::exit( EXIT_SUCCESS );
        break;
        // turn on wirframe rendering
#ifndef USINGIOS_
    case Qt::Key_W:
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        break;
        // turn off wire frame
    case Qt::Key_S:
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        break;
#endif
        // show full screen
    case Qt::Key_F:
        showFullScreen();
        break;
        // show windowed
    case Qt::Key_N:
        showNormal();
        break;
    case Qt::Key_Space :
        m_win.spinXFace=0;
        m_win.spinYFace=0;
        m_modelPos.set(ngl::Vec3::zero());
        break;
    default:
        break;
    }
    update();

}

void NGLScene::timerEvent(QTimerEvent *_event )
{
    ting->update();
    if(_event->timerId() == m_fpsTimer)
    {
        if( m_timer.elapsed() > 1000.0)
        {
            m_fps=m_frames;
            m_frames=0;
            m_timer.restart();
        }
    }
    // re-draw GL
    update();
}
