#include "lineRenderer.h"

lineRenderer::lineRenderer(bool screen_baked)
:DRAW_BAKED(screen_baked){
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray((GLuint)vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * MAX_POINT_NUM * 3, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // if(!shader_.AddShader(GL_VERTEX_SHADER, Manager::shader_contents[dvr::SHADER_CPLANE_VERT])
    //    ||!shader_.AddShader(GL_FRAGMENT_SHADER,  Manager::shader_contents[dvr::SHADER_CPLANE_FRAG])
    //    ||!shader_.CompileAndLink())
    //     LOGE("Center Line===Failed to create shader program===");
    // GLuint sp = shader_.Use();
    // Shader::Uniform(sp, "uBaseColor", glm::vec4(1.0f, 1.0f, .0f, 1.0f));
    // shader_.UnUse();
        std::string vert_content =
    "#version 300 es\n"
    "layout(location = 0) in vec2 aPosition;\n"
    "void main(){\n"
    "    gl_Position = vec4(aPosition.xy * 2.0-1.0, .0, 1.0);\n"
    "}";

    std::string frag_content = 
    "#version 300 es\n"
    "precision mediump float;\n"
    "uniform vec4 uBaseColor;\n"
    "out vec4 frag_color;\n"
    "void main() {\n"
    "    frag_color = uBaseColor;\n"
    "}";


    if(!shader_.AddShader(GL_VERTEX_SHADER, vert_content)
       ||!shader_.AddShader(GL_FRAGMENT_SHADER, frag_content)
       ||!shader_.CompileAndLink())
        LOGE("line ===Failed to create shader program===");
    GLuint sp = shader_.Use();
    Shader::Uniform(sp, "uBaseColor", line_color);
    shader_.UnUse();
}
void lineRenderer::updateVertices(int point_num, const float * data){
        draw_point_num = point_num;
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, point_num * 2 * sizeof(float), data);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void lineRenderer::Draw(){
    GLuint sp = shader_.Use();
    glLineWidth(5.0f);

    glBindVertexArray(vao_);
    glDrawArrays(GL_LINES, 0, draw_point_num);
    glBindVertexArray(0);
    shader_.UnUse();
}

void lineRenderer::onDraw(glm::mat4 model_mat){
    if(DRAW_BAKED) draw_baked(model_mat);
    else draw_scene(model_mat);
}
void lineRenderer::draw_scene(glm::mat4 model_mat){
    GLuint sp = shader_.Use();
    glLineWidth(1.0f);
    // Shader::Uniform(sp, "uMVP", Manager::camera->getProjMat() * Manager::camera->getViewMat() * model_mat);
    glBindVertexArray(vao_);
    glDrawArrays(GL_LINES, 0, draw_point_num);
    glBindVertexArray(0);
    shader_.UnUse();
}
void lineRenderer::draw_baked(glm::mat4 model_mat){
    // if(!baked_dirty_) return;
    // if(!frame_buff_) Texture::initFBO(frame_buff_, screenQuad::instance()->getTex(), nullptr);
    // glm::vec2 tsize = screenQuad::instance()->getTexSize();
    // glViewport(0, 0, tsize.x, tsize.y);
    // glBindFramebuffer(GL_FRAMEBUFFER, frame_buff_);
    // glClear(GL_DEPTH_BUFFER_BIT);
    // draw_scene(model_mat);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // baked_dirty_ = false;
}
