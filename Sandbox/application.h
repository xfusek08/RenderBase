
#pragma once

#include <RenderBase/application.h>

class Application : public rb::app::BasicOpengGLApplication
{
    using BasicOpengGLApplication::BasicOpengGLApplication;
    
    protected:
        bool init() override;
        void draw() override;
};
