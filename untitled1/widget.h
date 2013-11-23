#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QMap>
#include "GeoEngine.h"
#include <QVector4D>
#include <QVector3D>

struct LightInfo
{
    QVector3D ambient;
    QVector3D color;
    QVector3D direction;
    QVector3D half;
    QVector3D position;
    float shininess;
    float strength;
};


class MyWidget : public QGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = 0);
    ~MyWidget();

public:
    QMap<QString,QString> conf;

    void initDirectionLight();
    void initPointLight();
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void timerEvent(QTimerEvent *e);

    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();

    void initShaders();
    void initTextures();
    void initLights();
    void  printDriverInfo();

private:

    LightInfo light;

    //QBasicTimer timer;
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    //GeometryEngine geometries;
    GeoEngine ge;

    GLuint texture;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

};

#endif // WIDGET_H
