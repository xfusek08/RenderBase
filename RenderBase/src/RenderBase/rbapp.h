
#include <RenderBase/application.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>
#include <RenderBase/gl/Program.h>

class Application : public rb::app::BasicOpenGLApplication
{
    using BasicOpenGLApplication::BasicOpenGLApplication;
    
    protected:
        bool init()     override;
        void draw()     override;
        bool finalize() override;
};

int main(int argc, char** argv)
{
    auto config = rb::app::loadDefaultConfigFromArguments(argc, argv);
    auto app = Application(config);
    return app.run() ? 0 : 1;
}
