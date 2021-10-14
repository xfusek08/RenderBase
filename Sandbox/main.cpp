
#include <application.h>

int main(int argc, char** argv)
{
    auto config = rb::app::loadDefaultConfigFromArguments(argc, argv);
    auto app = Application(config);
    return app.run() ? 0 : 1;
}
