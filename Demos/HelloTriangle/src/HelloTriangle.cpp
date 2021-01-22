
#include <iostream>

#include <RenderBase/application.h>
#include <RenderBase/tools/entryPoint.h>

using namespace std;
using namespace rb;

class HelloTriangle : public rb::Application {

    using Application::Application; // inherit base constructor - mandatory

    // GLuint vao;
    shared_ptr<Program> prg;

    bool init() {

        // mainWindow->getPerformanceAnalyzer()->capFPS(60);

        mainWindow->getPerformanceAnalyzer()->perPeriodReport(1s, [](IntervalPerformanceReport report) {
            cout << report.asFormatedString() << "\n";
        });


        // graphics program creation
        prg = Program::create(
            Shader::create(ShaderType::Vertex, vsSrc),
            Shader::create(ShaderType::Fragment, vsSrc)
        );

        if (!prg->getErrorMessage().empty()) {
            cerr << "Error while creating a program: \n" << prg->getErrorMessage() << endl;
            return false;
        }

        glClearColor(0, 0, 0, 1);
        glCreateVertexArrays(1, &vao);

        return true;
    }

    bool update(const Event &event) { return true; }

    void draw() {
        prg->use();

        glPointSize(10);
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
