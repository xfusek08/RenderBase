
#include <RenderBase/tools/camera.h>

#ifdef DEBUG
    // #define NO_DEBUG_LOG // uncomment if debug logging should be ignored for this file
    #include <RenderBase/logging.h>
    #include <glm/gtx/string_cast.hpp>
#endif

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
// OrbitCameraController class implementation
//////////////////////////////////////////

void updateCamera(Camera& camera, const OrbitCameraController& orbitController)
{
    // camera target is origin
    // vector from origin to camera is vector locating camera in local space
    // phi (0 - 1) needs to be converted to radians
    // theta (0 - 1) needs to be converted to radians
    // position of camera needs to me normalized
    // lets do a rotation using the values
    
    RB_DEBUG(
        " camera movement: \n"
        "    phi:   "  << orbitController.getPhi()   << "\n"
        "    theta: "  << orbitController.getTheta() << "\n"
        "    zoom:  "  << orbitController.getZoom()  << "\n"
    );

    auto phi    = orbitController.getPhi()   * glm::two_pi<float32>();
    auto theta  = orbitController.getTheta() * glm::pi<float32>();
    auto origin = camera.getTargetPosition();
    auto zoom   = orbitController.getZoom();

    glm::vec3 newPosition = zoom * glm::vec3{
        glm::sin(theta) * glm::sin(phi),
        glm::cos(theta),
        glm::sin(theta) * glm::cos(phi),
    };

    camera.setPosition(origin + newPosition);
}

OrbitCameraController::OrbitCameraController(Camera camera) : camera(camera)
{
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
    
    updateCamera(camera, *this);
}

void OrbitCameraController::setLeftRight(float32 phi)
{
    this->phi = glm::mod(phi, 1.0f);
    updateCamera(camera, *this);
}

void OrbitCameraController::setUpDown(float32 theta)
{
    this->theta = glm::clamp(theta, 0.01f, 0.99f);
    updateCamera(camera, *this);
}

void OrbitCameraController::setZoom(float32 zoomVal)
{
    this->zoomVal = glm::clamp(zoomVal, minZoom, maxZoom);
    updateCamera(camera, *this);
}

    
