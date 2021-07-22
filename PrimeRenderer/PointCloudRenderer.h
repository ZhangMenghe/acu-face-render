#ifndef POINT_RENDERER_H
#define POINT_RENDERER_H

#include <platforms/platform.h>
#include <GLPipeline/Shader.h>
class PointRenderer {
public:
    PointRenderer(glm::vec4 color, bool wibo = false);
    ~PointRenderer() = default;
    const float point_size = 5.0f;
    void Draw(const float * pointcloud, int point_num, GLenum mode);
    void Draw(const float * points, const unsigned short* indices, int point_num, int indice_num, GLenum mode);

private:
    Shader shader_;
    GLuint vao_, vbo_, ibo_;
    const int MAX_POINT_NUM = 500;
    // bool DRAW_ELEMENT;
};

#endif