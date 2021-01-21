/**
 * This file was inspired by Hazel engine project by The Cherno: https://github.com/TheCherno/Hazel
 */

#include <RenderBase/application.h>

extern rb::Application* createApplication(int argc, char **argv);

int main(int argc, char **argv) {

    // Do render base initiation
    //    - loggig
    //    - debug profiling
    //    - etc.

    // run the user defined app class
    auto app = createApplication(argc, argv);
    auto resCode = app->run();
    delete app;
    return resCode;
}

#define RB_APPLICATION_START(className)\
    rb::Application* createApplication(int argc, char **argv) {\
        return new className(rb::Configuration(argc, argv));\
    }