
#include <RenderBase/graphics/GraphicsObject.h>

void rb::GraphicsObject::fail(std::string message) {
    if (isOk()) {
        errorMessage = message;
    } else {
        errorMessage += "\n --- \n" + message;
    }
}
