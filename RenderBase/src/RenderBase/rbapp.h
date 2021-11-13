
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
        
        bool onResize(uint32 newWidth, uint32 newHeight)  override;
        bool onInputChange(const rb::input::InputState& inputState, const rb::timing::TimeStep& tick) override;
        bool onTick(const rb::input::InputState& inputState, const rb::timing::TimeStep& tick) override;
        bool onGuiChanged(const rb::gui::GuiState& guiState)  override;
};

int main(int argc, char** argv)
{
    auto config = rb::app::loadDefaultConfigFromArguments(argc, argv);
    auto app = Application(config);
    return app.run() ? 0 : 1;
}
