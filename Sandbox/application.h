
#pragma once

#include <RenderBase/application.h>

class Application : public rb::app::BasicOpenGLApplication
{
    using BasicOpenGLApplication::BasicOpenGLApplication;
    
    protected:
        bool init() override;
        void draw() override;
};
