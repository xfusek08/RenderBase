
#include <iostream>

#include <RenderBase/application.h>
#include <RenderBase/tools/entryPoint.h>
#include <RenderBase/graphics.h>

// lets allow using opengl functions in draw method
#include <RenderBase/platform/graphics/OpenGL/GLGraphicsContext.h>

using namespace std;
using namespace rb;

class HelloTriangle : public rb::Application {

    // inherit base constructor - mandatory
    using Application::Application;

    GLuint vao;
    // shared_ptr<VertexArray> vao;
    shared_ptr<Program> prg;
    shared_ptr<GraphicsContext> graphics;

    bool init() {

        mainWindow->getPerformanceAnalyzer()->capFPS(60);
        mainWindow->getPerformanceAnalyzer()->perPeriodReport(1s, [](IntervalPerformanceReport report) {
            cout << report.asFormatedString() << "\n";
        });

        // graphics program creation
        prg = Program::create(Shader::create(ShaderType::Vertex, vsSrc), Shader::create(ShaderType::Fragment, fsSrc));
        if (!prg->isOk()) {
            fail("Error while creating a program:\n" + prg->getErrorMessage());
        }

        // // glCreateVertexArrays(1, &vao);
        // vao = VertexArray::create();
        // if (!vao->isOk()) {
        //     fail("Error while creating vertex array object:\n" + vao->getErrorMessage());
        // }

        glCreateVertexArrays(1, &vao);
        return true;
    }

    bool update(const Event &event) { return true; }

    void draw() {
        prg->use();

        // vao->bind();

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);
    }

    std::string const vsSrc = R".(
        #version 460 core
        out vec3 vColor;
        void main(){
            if(gl_VertexID == 0){gl_Position = vec4(0,0,0,1);vColor = vec3(1,0,0);}
            if(gl_VertexID == 1){gl_Position = vec4(1,0,0,1);vColor = vec3(0,1,0);}
            if(gl_VertexID == 2){gl_Position = vec4(0,1,0,1);vColor = vec3(0,0,1);}
        }
    ).";

    std::string const fsSrc = R".(
        #version 460 core
        in vec3 vColor;
        layout(location=0)out vec4 fColor;
        void main(){
            fColor = vec4(vColor,1);
        }
    ).";
};

RB_APPLICATION_START(HelloTriangle)
