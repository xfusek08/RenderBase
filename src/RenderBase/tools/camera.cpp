
#include <RenderBase/tools/camera.h>
#include <RenderBase/tools/logging.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

using namespace std;
using namespace rb;

//////////////////////////////////////////
// Camera class implementation
//////////////////////////////////////////

Camera::Camera(
    glm::vec3 position,
    glm::vec3 target,
    glm::vec3 up,
    float     aspectRatio,
    float     fovDegrees,
    float     nearPlane,
    float     farPlane
) :
    position(position),
    target(target),
    up(up),
    aspectRatio(aspectRatio),
    fovDegrees(fovDegrees),
    nearPlane(nearPlane),
    farPlane(farPlane)
{
    updateProjectionMatrix();
    updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
    if (viewChanged) {
        updateViewMatrix();
    }
    return viewMatrix;
}

void Camera::updateViewMatrix()
{
    viewMatrix = glm::lookAt(position, target, up);
    viewChanged = false;
}

void Camera::updateProjectionMatrix()
{
    projectionMatrix = glm::perspective(
        glm::radians(fovDegrees),
        aspectRatio,
        nearPlane,
        farPlane
    );
}

//////////////////////////////////////////
// OrbitCameraController class implementation
//////////////////////////////////////////

OrbitCameraController::OrbitCameraController(shared_ptr<Camera> camera) : CameraController(camera) {

    // compute theta, phi and zoom from camera postion relative to target so its position remains th same after applying this controller
    auto normalizedPosition = glm::normalize(camera->getPosition() - camera->getTargetPosition());
    auto xzShadow = normalizedPosition;
    xzShadow.y = 0.0f;
    xzShadow = glm::normalize(xzShadow);

    phi = glm::angle(xzShadow, normalizedPosition) / glm::half_pi<float>();
    if (signbit(normalizedPosition.y)) {
        phi = -phi;
    }
    theta = glm::angle(glm::vec3(1.0, 0.0, 0.0), xzShadow) / glm::two_pi<float>();
    if (signbit(normalizedPosition.z)) {
        theta = 1 - theta;
    }
    setZoom(glm::length(camera->getTargetPosition() - camera->getPosition()));
}

bool OrbitCameraController::processEvent(Event event) {
    switch (event.type)
    {
        case EventType::MouseMove:
            if (event.mouseMoveData.buttons.left) {
                lookXY({-event.mouseMoveData.xMovedRel, event.mouseMoveData.yMovedRel});
                return true;
            }
            break;
    }
    return false;
}

void OrbitCameraController::upDown(float degree)
{
    phi = glm::clamp(phi + degree, -0.9f, 0.9f);
    updateCamera();
}

void OrbitCameraController::leftRight(float degree)
{
    theta = fmod(theta + degree, 1.0f);
    updateCamera();
}

void OrbitCameraController::setZoom(float zoom)
{
    actZoom = glm::clamp(zoom, minZoom, maxZoom);
    updateCamera();
}

void OrbitCameraController::lookXY(glm::vec2 delta)
{
    upDown(delta.y * sensitivityY);
    leftRight(delta.x * sensitivityX * 0.5);
}

void OrbitCameraController::updateCamera()
{
    LOG_DEBUG("{ phi, theta, actZoom}: { " << this->phi << ", " << this->theta << ", " << this->actZoom << " }");

    auto phi   = this->phi   * glm::half_pi<float>();
    auto theta = this->theta * glm::two_pi<float>();

    auto target = camera->getTargetPosition();

    glm::vec3 normalRotation = {
        glm::cos(phi) * glm::cos(theta),
        glm::sin(phi),
        glm::sin(theta) * glm::cos(phi)
    };

    camera->setPosition(target + actZoom * normalRotation);
}
