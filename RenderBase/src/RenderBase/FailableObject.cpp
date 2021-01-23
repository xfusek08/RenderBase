
#include <RenderBase/FailableObject.h>

void rb::FailableObject::fail(std::string message) {
    if (isOk()) {
        errorMessage = message;
    } else {
        errorMessage += "\n --- \n" + message;
    }
}
