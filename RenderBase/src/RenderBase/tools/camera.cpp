#ifdef DEBUG
    #define NO_LOG // uncomment if debug logging should be ignored for this file
    #include <glm/gtx/string_cast.hpp>
#endif

#include <RenderBase/logging.h>
#include <RenderBase/tools/camera.h>

#include <GLFW/glfw3.h>

using namespace std;
using namespace rb;

//////////////////////////////////////////
// Camera class implementation
//////////////////////////////////////////

Camera::Camera(
    glm::vec3 position,
    glm::vec3 target,
    glm::vec3 up,
    float32   aspectRatio,
    float32   fov,
    float32   nearPlane,
    float32   farPlane
) :
    position(position),
    target(target),
    up(up),
    aspectRatio(aspectRatio),
    fov(fov),
    nearPlane(nearPlane),
    farPlane(farPlane)
{ }

//////////////////////////////////////////
// CameraController vase class implementation
//////////////////////////////////////////

CameraController::CameraController(Camera camera) : camera(camera)
{
    
}

//////////////////////////////////////////
// OrbitCameraController class implementation
//////////////////////////////////////////

OrbitCameraController::OrbitCameraController(Camera camera) : CameraController(camera)
{
    // calculate state from current camera orientation
    
    glm::vec3 cameraDirection = glm::normalize(camera.getPosition() - camera.getTargetPosition());
    
    zoomVal = glm::distance(camera.getTargetPosition(), camera.getPosition());
    theta = glm::angle(glm::vec3{0, 1, 0}, cameraDirection) / glm::pi<float32>();
    
    // calculate phi
    auto xzShadow = glm::vec3{cameraDirection.x, 0, cameraDirection.z};
    if (glm::length(xzShadow) > 0) {
        phi = glm::angle(glm::vec3{0, 0, 1}, xzShadow) / glm::two_pi<float32>();
        if (!signbit(cameraDirection.x)) {
            phi = 0.5f + (1 - phi);
        }
    }
    
    updateCamera();
}

void OrbitCameraController::updateCamera()
{
    // camera target is origin
    // vector from origin to camera is vector locating camera in local space
    // phi (0 - 1) needs to be converted to radians
    // theta (0 - 1) needs to be converted to radians
    // position of camera needs to me normalized
    // lets do a rotation using the values
    
    RB_DEBUG(
        " camera movement: \n"
        "    phi:   "  << getPhi()   << "\n"
        "    theta: "  << getTheta() << "\n"
        "    zoom:  "  << getZoom()  << "\n"
    );

    auto phi    = getPhi()   * glm::two_pi<float32>();
    auto theta  = getTheta() * glm::pi<float32>();
    auto origin = camera.getTargetPosition();
    auto zoom   = getZoom();

    glm::vec3 newPosition = zoom * glm::vec3{
        glm::sin(theta) * glm::sin(phi),
        glm::cos(theta),
        glm::sin(theta) * glm::cos(phi),
    };

    camera.setPosition(origin + newPosition);
}

void OrbitCameraController::setLeftRight(float32 value)
{
    phi = glm::mod(value, 1.0f);
}

void OrbitCameraController::setUpDown(float32 value)
{
    theta = glm::clamp(value, 0.01f, 0.99f);
}

void OrbitCameraController::setZoom(float32 value)
{
    zoomVal = glm::clamp(value, minZoom, maxZoom);
}

void OrbitCameraController::zoom(float32 delta)
{
    setZoom(zoomVal + (delta * zoomVal * 0.1)); // make zooming faster when far away
}

bool OrbitCameraController::onInputChange(const input::InputState& inputState, const timing::TimeStep& tick)
{
    bool updated = false;
    auto zoomDelta = -inputState.getScroll().y;
    
    if (inputState.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
        lookXY(inputState.getMouseDelta());
        updated = true;
    }
    
    if (zoomDelta != 0) {
        zoom(zoomDelta);
        updated = true;
    }
    
    if (updated) {
        updateCamera();
    }
    
    return updated;
}

bool OrbitCameraController::onTick(const input::InputState& inputState, const timing::TimeStep& tick)
{
    bool updated = false;
    
    auto leftKey    = inputState.isKeyPressed(GLFW_KEY_LEFT);
    auto rightKey   = inputState.isKeyPressed(GLFW_KEY_RIGHT);
    auto upKey      = inputState.isKeyPressed(GLFW_KEY_UP);
    auto downKey    = inputState.isKeyPressed(GLFW_KEY_DOWN);
    auto zoomInKey  = inputState.isKeyPressed(GLFW_KEY_W);
    auto zoomOutKey = inputState.isKeyPressed(GLFW_KEY_S);
    
    if (leftKey != rightKey) {
        leftKey ? moveLeft() : moveRight();
        updated = true;
    }
    
    if (upKey != downKey) {
        upKey ? moveUp() : moveDown();
        updated = true;
    }
    
    if (zoomInKey != zoomOutKey) {
        zoomInKey ? zoomIn() : zoomOut();
        updated = true;
    }
    
    if (updated) {
        updateCamera();
    }
    
    return updated;
}

bool FreeCameraController::onInputChange(const input::InputState& inputState, const timing::TimeStep& tick)
{
    bool updated = false;
    auto zoomDelta = -inputState.getScroll().y;
    
    if (inputState.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
        lookXY(inputState.getMouseDelta());
        updated = true;
    }
    
    if (zoomDelta != 0) {
        zoom(zoomDelta);
        updated = true;
    }
    
    if (updated) {
        updateCamera();
    }
    
    return updated;
}

bool FreeCameraController::onTick(const input::InputState& inputState, const timing::TimeStep& tick)
{
    bool updated = false;
    
    auto leftKey    = inputState.isKeyPressed(GLFW_KEY_LEFT);
    auto rightKey   = inputState.isKeyPressed(GLFW_KEY_RIGHT);
    auto upKey      = inputState.isKeyPressed(GLFW_KEY_UP);
    auto downKey    = inputState.isKeyPressed(GLFW_KEY_DOWN);
    auto zoomInKey  = inputState.isKeyPressed(GLFW_KEY_Q);
    auto zoomOutKey = inputState.isKeyPressed(GLFW_KEY_E);
    
    auto forward   = inputState.isKeyPressed(GLFW_KEY_W);
    auto backwards = inputState.isKeyPressed(GLFW_KEY_S);
    auto left      = inputState.isKeyPressed(GLFW_KEY_A);
    auto right     = inputState.isKeyPressed(GLFW_KEY_D);
    auto raise     = inputState.isKeyPressed(GLFW_KEY_LEFT_SHIFT);
    auto sink      = inputState.isKeyPressed(GLFW_KEY_LEFT_CONTROL);
    
    if (leftKey != rightKey) {
        leftKey ? moveLeft() : moveRight();
        updated = true;
    }
    
    if (upKey != downKey) {
        upKey ? moveUp() : moveDown();
        updated = true;
    }
    
    if (zoomInKey != zoomOutKey) {
        zoomInKey ? zoomIn() : zoomOut();
        updated = true;
    }
    
    if (forward != backwards) {
        glm::vec3 direction = camera.getTargetPosition() - camera.getPosition();
        direction.y = 0;
        direction = glm::normalize(direction);
        camera.setTargetPosition(camera.getTargetPosition() + direction * (forward ? 0.05f : -0.05f) * getZoom());
        updated = true;
    }
    
    if (left != right) {
        glm::vec3 direction = glm::cross(camera.getTargetPosition() - camera.getPosition(), camera.getUpVector());
        direction.y = 0;
        direction = glm::normalize(direction);
        camera.setTargetPosition(camera.getTargetPosition() + direction * (right ? 0.05f : -0.05f) * getZoom());
        updated = true;
    }
    
    // if (raise != sink) {
    //     glm::vec3 direction = camera.getUpVector();
    //     direction = glm::normalize(direction);
    //     camera.setTargetPosition(camera.getTargetPosition() + direction * (raise ? 0.1f : -0.1f) * getZoom());
    //     updated = true;
    // }

    if (updated) {
        updateCamera();
    }
    
    return updated;
}