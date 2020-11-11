#pragma once

#include <string>
#include <memory>

#include <RenderBase/event.h>

namespace rb {

    class Scene;
    class Graphics;
    class Window;

    struct Configuration {
        Configuration() = default;
        Configuration(int argc, char *argv[]) {} // TODO: in implementation parse cmd arguments

        uint32_t windowWidth  = 1280;
        uint32_t windowHeight = 720;

        bool valid = true;
    };

    enum class ApplicationState {
        valid, invalid
    };

    class Application
    {
        public:
            Application(Configuration config = {});

            // getter methods
            inline       Configuration getConfig()     const { return config; }
            inline const Window&       getMainWindow() const { return *mainWindow; }

            // methods
            int run(); // todo: runResult struct

            ApplicationState state        = ApplicationState::invalid;
            std::string      errorMessage = "";

        protected:
            virtual bool init()                     = 0;
            virtual bool update(const Event& event) = 0;
            virtual void draw()                     = 0;

            void addErrorMessage(const std::string& message);

            Configuration                    config              = {};
            std::unique_ptr<Window>          mainWindow          = nullptr;
            std::unique_ptr<Scene>           scene               = nullptr;
            std::unique_ptr<GraphicsContext> mainGraphicsContext = nullptr;
    };

}
