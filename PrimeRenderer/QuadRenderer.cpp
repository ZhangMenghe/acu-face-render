#include "QuadRenderer.h"
#include <GLPipeline/Mesh.h>
#include <GLPipeline/Primitive.h>
namespace{
    const std::string vert_content =
        "#version 300 es\n"
        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 1) in vec3 aTexcoord;\n"
        "uniform vec2 uOffset;\n"
        "uniform vec2 uScale;\n"
        "out vec2 vTexcoord;"

        "void main(){\n"
            "vTexcoord = aTexcoord.xy;\n"
            "gl_Position = vec4(aPosition.xy * uScale+uOffset, .0, 1.0);\n"
        "}";
    std::string frag_content = 
        "#version 300 es\n"
        "precision mediump float;\n"
        "uniform vec4 uBaseColor;\n"
        "in vec2 vTexcoord;\n"
        "out vec4 frag_color;\n"

        "void main() {\n"
        "    frag_color = uBaseColor;\n"
        "}";

    std::string frag_content_with_tex = 
        "#version 300 es\n"
        "precision mediump float;\n"
        "in vec2 vTexcoord;\n"
        "out vec4 frag_color;\n"
        "uniform sampler2D uSampler;"

        "void main() {\n"
        "   fragColor = texture(uSampler, vTexcoord);\n"
        "}";
};
QuadRenderer::QuadRenderer(glm::vec4 color){
    Mesh::InitQuadWithTex(m_vao, quad_vertices_tex_standard, 4, quad_indices, 6);

    if(!m_shader.AddShader(GL_VERTEX_SHADER, vert_content)
       ||!m_shader.AddShader(GL_FRAGMENT_SHADER, frag_content)
       ||!m_shader.CompileAndLink())
        LOGE("Quad===Failed to create shader program===");
    GLuint sp = m_shader.Use();
    Shader::Uniform(sp, "uBaseColor", color);
    m_shader.UnUse();
}

QuadRenderer::QuadRenderer(int width, int height){
    Mesh::InitQuadWithTex(m_vao, quad_vertices_tex_standard, 4, quad_indices, 6);

    if(!m_shader.AddShader(GL_VERTEX_SHADER, vert_content)
       ||!m_shader.AddShader(GL_FRAGMENT_SHADER, frag_content_with_tex)
       ||!m_shader.CompileAndLink())
        LOGE("Quad===Failed to create shader program===");
    
    auto vsize = width* height * 4;
    GLbyte * vdata = new GLbyte[vsize];
    memset(vdata, 0x00, vsize * sizeof(GLbyte));
    m_tex = new Texture(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, width, height, vdata);
}
void QuadRenderer::Draw(glm::vec2 scale, glm::vec2 offset, GLenum mode){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint sp = m_shader.Use();
    if(m_tex!=nullptr){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_tex->GLTexture());
        Shader::Uniform(sp, "uSampler", 0);
    }
    Shader::Uniform(sp, "uScale", scale);
    Shader::Uniform(sp, "uOffset", offset);

    glBindVertexArray(m_vao);
    glDrawElements(mode, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    m_shader.UnUse();
    glDisable(GL_BLEND);
}

