#include "widget.h"

#include <QMouseEvent>
#include <QApplication>
#include <math.h>
#include <locale.h>

#include <iostream>




MyWidget::MyWidget(QWidget *parent)
    : QGLWidget(parent),angularSpeed(1)
{
}

MyWidget::~MyWidget()
{
     deleteTexture(texture);
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    mousePressPosition = QVector2D(e->localPos());
}

void MyWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void MyWidget::timerEvent(QTimerEvent *e)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Update scene
        updateGL();
    }
}

void MyWidget::initializeGL()
{
    initializeOpenGLFunctions();

    printDriverInfo();

    qglClearColor(Qt::white);
    initShaders();
    initTextures();
    initLights();
//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    ge.init(conf["ModelFile"].toStdString());
    timer.start(12,this);
}

void MyWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 50.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    //projection.perspective(fov, aspect, zNear, zFar);
    projection.ortho(-3.,3.,-3./aspect,3./aspect,zNear,zFar);
}

void MyWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -10.0);
    matrix.rotate(rotation);
    //matrix.scale(0.75);

    QMatrix4x4 normalMatrix=matrix.inverted().transposed();
    //std::cout<<normalMatrix<<std::endl;
    // Set modelview-projection matrix
    program.setUniformValue("MVP", projection * matrix);
    program.setUniformValue("NormalMatrix", normalMatrix);
    program.setUniformValue("ModelViewMatrix", matrix);
    program.setUniformValue("eyeDirection",QVector3D(0,0,1).normalized());
//! [6]

    // Use texture unit 0 which contains cube.png
    //program.setUniformValue("texture", 0);

    // Draw cube geometry
    ge.render(&program);
}


void MyWidget::initShaders()
{
    // Override system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, conf["ShaderFile"]+".vert"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, conf["ShaderFile"]+".frag"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");
}

void MyWidget::initTextures()
{
    // Load cube.png image
    glEnable(GL_TEXTURE_2D);
    texture = bindTexture(QImage(":/resources/cube.png"));

    // Set nearest filtering mode for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void MyWidget::initDirectionLight()
{
    light.ambient=QVector3D(0.2,0.2,0.2);
    light.color=QVector3D(0.,1.,1.)*0.7;
    light.direction=QVector3D(0,0,1).normalized();
    light.shininess=20;
    light.strength=10;
    light.half=(light.direction+QVector3D(0,0,-5)).normalized();

    program.setUniformValue("ambient",light.ambient);
    program.setUniformValue("lightColor",light.color);
    program.setUniformValue("lightDirection",light.direction);
    program.setUniformValue("shininess",light.shininess);
    program.setUniformValue("strength",light.strength);
}

void MyWidget::initPointLight()
{
    light.ambient=QVector3D(0.2,0.2,0.2);
    light.color=QVector3D(0.,1.,1.)*0.7;
    light.position=QVector3D(0,1,2);
    light.shininess=20;
    light.strength=10;


    program.setUniformValue("ambient",light.ambient);
    program.setUniformValue("lightColor",light.color);
    program.setUniformValue("lightPosition",light.position);
    program.setUniformValue("shininess",light.shininess);
    program.setUniformValue("strength",light.strength);
}

void MyWidget::initLights()
{
    //initDirectionLight();
    initPointLight();

}

void MyWidget::printDriverInfo()
{
    const GLubyte* str=glGetString(GL_VERSION);
    std::cout<<"OpenGL Version: "<<str<<std::endl;

    str=glGetString(GL_VENDOR);
    std::cout<<"OpenGL Vendor: "<<str<<std::endl;

    str=glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout<<"GLSL Version: "<<str<<std::endl;

}


