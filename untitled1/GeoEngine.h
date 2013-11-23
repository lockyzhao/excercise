#ifndef MODELS_H
#define MODELS_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <vector>
#include "Libs/model.h"
class GeoEngine: protected QOpenGLFunctions
{
public:
    GeoEngine();
public:
    virtual ~GeoEngine();

    void init(const std::string& file_name);
    void render(QOpenGLShaderProgram *program);

private:
    void initCubeGeometry();
    void initObjeModels(const std::string& file_name);

    Model* model ;
    std::vector<GLuint> vboIds;
};

#endif // MODELS_H
