#ifndef LINE_RENDERER_H
#define LINE_RENDERER_H

#include <GLPipeline/Mesh.h>
#include <GLPipeline/Shader.h>
#include <GLPipeline/Texture.h>

class lineRenderer{
private:
    const int MAX_POINT_NUM=500;
    GLuint vao_, vbo_;
    Shader shader_;
    glm::vec4 line_color = glm::vec4(.7f, 0.5f, .0f, 1.0f);

public:
    lineRenderer();
    void updateVertices(int point_num, const float * data);
    void Draw();
};
#endif