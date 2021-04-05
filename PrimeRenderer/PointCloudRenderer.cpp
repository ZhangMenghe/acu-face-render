#include <PrimeRenderer/PointCloudRenderer.h>
PointRenderer::PointRenderer(glm::vec4 color, bool wibo){
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray((GLuint)vao_);
    if(wibo){
        glGenBuffers(1, &ibo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*MAX_POINT_NUM, nullptr, GL_DYNAMIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * MAX_POINT_NUM * 3, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::string vert_content =
    "#version 300 es\n"
    "layout(location = 0) in vec3 aPosition;\n"
    "uniform float point_size;\n"
    "void main(){\n"
    "    gl_PointSize = point_size;\n"
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
        LOGE("point cloud===Failed to create shader program===");
    GLuint sp = shader_.Use();
    Shader::Uniform(sp, "point_size", point_size);
    Shader::Uniform(sp, "uBaseColor", color);
    shader_.UnUse();
}
void PointRenderer::Draw(const float * pointcloud, int point_num, GLenum mode){
    if(point_num > 0){
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferSubData(GL_ARRAY_BUFFER,0, point_num*3* sizeof(float),pointcloud);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    GLuint sp = shader_.Use();
    glBindVertexArray(vao_);
    glDrawArrays(mode, 0, point_num);
    glBindVertexArray(0);
    shader_.UnUse();
}
void PointRenderer::Draw(const float * points, const unsigned short* indices, int point_num, int indice_num, GLenum mode){
   
    if(point_num > 0){
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, point_num*3* sizeof(float),points);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    if(indice_num > 0){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indice_num * sizeof(unsigned short), indices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    glEnable(GL_LINE_WIDTH);
    glLineWidth(1.0);
    
    GLuint sp = shader_.Use();
    glBindVertexArray(vao_);
    // glDrawArrays(mode, 0, point_num);

    glDrawElements(mode, indice_num, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
    shader_.UnUse();

    glDisable(GL_LINE_WIDTH);
    glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
}
