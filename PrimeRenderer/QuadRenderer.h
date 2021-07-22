#ifndef QUAD_RENDERER_H
#define QUAD_RENDERER_H

#include <platforms/platform.h>
#include <GLPipeline/Shader.h>
#include <GLPipeline/Texture.h>

class QuadRenderer {
public:
    QuadRenderer(glm::vec4 color);
    QuadRenderer(int width, int height);

    ~QuadRenderer() = default;

    Texture* GetTexture(){ return m_tex;}

    void Draw(glm::vec2 scale, glm::vec2 offset, GLenum mode);
private:
    Shader m_shader;
    Texture* m_tex = nullptr;
    GLuint m_vao;
};

#endif