
#include <application.h>

int main(int argc, char** argv)
{
    auto config = App::configure(argc, argv);
    return App::run(config) ? 0 : 1;
}
