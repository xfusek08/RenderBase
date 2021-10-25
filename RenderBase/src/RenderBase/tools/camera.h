#pragma once

#include <RenderBase/defines.h>
#include <RenderBase/logging.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace rb
{
    struct Camera
    {
        Camera(
            glm::vec3 position    = glm::vec3(0, 0, -1),
            glm::vec3 target      = glm::vec3(0, 0, 0),
            glm::vec3 up          = glm::vec3(0, 1, 0),
            float32   aspectRatio = 1.0f,
            float32   fovDegrees  = 45.0f,
            float32   nearPlane   = 0.1f,
            float32   farPlane    = 100.0f
        );

        // scalars
        inline float32 getAspectRatio()       const { return aspectRatio; }
        inline float32 getFov()               const { return fov; }
        inline float32 getNearPlaneDistance() const { return nearPlane; }
        inline float32 getFarPlaneDistance()  const { return farPlane; }

        // vectors
        inline glm::vec3 getPosition()       const { return position; }
        inline glm::vec3 getTargetPosition() const { return target; }
        inline glm::vec3 getUpVector()       const { return up; }
        inline glm::vec3 getDirection()      const { return glm::normalize(target - position);  }

        inline glm::vec3 getOrientationLeft() const { return glm::normalize(glm::cross(up, getDirection())); }
        inline glm::vec3 getOrientationUp()   const { return glm::normalize(glm::cross(getDirection(), getOrientationLeft())); }

        // matrices
        inline glm::mat4 getViewMatrix()       const { return glm::lookAt(position, target, up); }
        inline glm::mat4 getProjectionMatrix() const { return glm::perspective(fov, aspectRatio, nearPlane, farPlane); }
        inline glm::mat4 getMVPMatrix()        const { return getProjectionMatrix() * getViewMatrix(); }
        
        inline void setPosition(glm::vec3 position)     { this->position    = position; }
        inline void setTargetPosition(glm::vec3 target) { this->target      = target; }
        inline void setUpVector(glm::vec3 up)           { this->up          = up; }
        inline void setAspectRatio(float32 aspectRatio) { this->aspectRatio = aspectRatio; }
        inline void setFov(float32 fov)                 { this->fov         = glm::clamp(fov, glm::pi<float32>() * 0.1f, glm::pi<float32>() * 0.9f); }

        private:
            // view details
            glm::vec3 position;
            glm::vec3 target;
            glm::vec3 up;

            // projection details
            float32 aspectRatio;
            float32 fov;
            float32 nearPlane;
            float32 farPlane;

            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;
    };
    
    // controllers
    
    /**
     * All measurements are in coordinates from this image:
     * https://www.researchgate.net/figure/Figure-A1-Spherical-coordinates_fig8_284609648
     * Meaning that z-axis is up and y is left.
     * So corresponding transformnations to OpenGL coordinate system needs to be performed.
     */
    class OrbitCameraController
    {
        public:
            // run-time configuration for this controller
            float32 leftRightSpeed = 0.1;
            float32 upDownSpeed    = 0.1;
            float32 zoomSpeed      = 0.01;
            float32 maxZoom        = 100.0;
            float32 minZoom        = 2.0;
            
            // Default constructor from superclass
            OrbitCameraController(Camera camera);
            
            void setLeftRight(float32 phi);
            inline void moveLeftRight(float32 deltaPhi) { setLeftRight(phi + deltaPhi); }
            inline void moveRight(float32 deltaPhi = 0) { moveLeftRight(deltaPhi != 0.0f ? deltaPhi : leftRightSpeed); }
            inline void moveLeft(float32 deltaPhi = 0)  { moveLeftRight(deltaPhi != 0.0f ? -deltaPhi : -leftRightSpeed); }
            
            void setUpDown(float32 theta);
            inline void moveUpDown(float32 deltaTheta)   { setUpDown(theta + deltaTheta); }
            inline void moveUp(float32 deltaTheta = 0)   { moveUpDown(deltaTheta != 0.0f ? -deltaTheta : -upDownSpeed); }
            inline void moveDown(float32 deltaTheta = 0) { moveUpDown(deltaTheta != 0.0f ? deltaTheta : upDownSpeed); }
            
            inline void lookXY(float32 deltaPhi, float32 deltaTheta) { moveLeftRight(deltaPhi); moveUpDown(deltaTheta); }
            inline void lookXY(glm::vec2 delta)                      { lookXY(delta.x, delta.y); }
            
            void setZoom(float32 zoom);
            inline void zoom(float32 delta = 0) { setZoom(zoomVal + delta); }
            inline void zoomIn()                { zoom(zoomSpeed); }
            inline void zoomOut()               { zoom(-zoomSpeed); }
            
            // getters
            
            inline Camera& getCamera() { return camera; }
            
            inline float32 getPhi()   const { return phi; }
            inline float32 getTheta() const { return theta; }
            inline float32 getZoom()  const { return zoomVal; }
            
        private:
            Camera camera   = {};
            float32 phi     = 0.0f; // left right angle in normalized value between 0 and 1 ( 1 means 360 deg or 2PI rad )
            float32 theta   = 0.0f; // up down angle in normalizedvalue value between 0 and 1, 0 means top down view (0 deg or 0 rad) and 1 means bottom up view (180 deg or PI rad)
            float32 zoomVal = 1.0f; // radius of orbiting sphere
    };
}
