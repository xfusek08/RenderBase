#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <RenderBase/event.h>

namespace rb
{
    class Camera
    {
        public:
            Camera(
                glm::vec3 position    = glm::vec3(0, 0, -1),
                glm::vec3 target      = glm::vec3(0, 0,  0),
                glm::vec3 up          = glm::vec3(0, 1,  0),
                float     aspectRatio = 1.0f,
                float     fovDegrees  = 45.0f,
                float     nearPlane   = 0.1f,
                float     farPlane    = 100.0f
            );

            // scalars
            inline float getAspectRatio()       const { return aspectRatio; }
            inline float getFov()               const { return fov; }
            inline float getNearPlaneDistance() const { return nearPlane; }
            inline float getFarPlaneDistance()  const { return farPlane; }
            inline bool  hasViewChanged()       const { return viewChanged || !changeAccepted; }

            // vectors
            inline glm::vec3 getPosition()       const { return position; }
            inline glm::vec3 getTargetPosition() const { return target; }
            inline glm::vec3 getUpVector()       const { return up; }
            inline glm::vec3 getDirection()      const { return glm::normalize(target - position);  }

            inline glm::vec3 getOrientationLeft() const { return glm::normalize(glm::cross(up, getDirection())); }
            inline glm::vec3 getOrientationUp()   const { return glm::normalize(glm::cross(getDirection(), getOrientationLeft())); }

            // matrices
            glm::mat4 getViewMatrix();
            inline glm::mat4 getProjectionMatrix() const { return projectionMatrix; }

            // setters
            inline void setViewChanged() { viewChanged = true; changeAccepted = false; }
            inline void acceptChange()   { changeAccepted = true; }

            inline void setPosition(glm::vec3 position)     { this->position    = position;    setViewChanged(); }
            inline void setTargetPosition(glm::vec3 target) { this->target      = target;      setViewChanged(); }
            inline void setUpVector(glm::vec3 up)           { this->up          = up;          setViewChanged(); }
            inline void setAspectRatio(float aspectRatio)   { this->aspectRatio = aspectRatio; setViewChanged();  updateProjectionMatrix(); }
            inline void setFov(float fov)                   { this->fov         = glm::clamp(fov, glm::pi<float>() * 0.1f, glm::pi<float>() * 0.9f);  setViewChanged();  updateProjectionMatrix(); }

        protected:
            // flags
            bool viewChanged    = true;
            bool changeAccepted = false;

            // view details
            glm::vec3 position;
            glm::vec3 target;
            glm::vec3 up;

            // projection details
            float aspectRatio;
            float fov;
            float nearPlane;
            float farPlane;

            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;

            // methods
            void updateViewMatrix();
            void updateProjectionMatrix();
    };

    class CameraController
    {
        public:
            std::shared_ptr<Camera> camera;

            CameraController(std::shared_ptr<Camera> camera) : camera(camera) {}

            virtual bool processEvent(Event event) = 0;
    };

    class OrbitCameraController : public CameraController
    {
        public:
            // configuration is by this procerties
            float sensitivityX    =  1.5;
            float sensitivityY    =  1.5;
            float zoomSensitivity =  0.5;
            float speedX          =  0.1;
            float speedY          =  0.1;
            float zoomSpeed       =  0.01;
            float maxZoom         = 100.0;
            float minZoom         =  2.0;

            // Default constructor from superclass
            OrbitCameraController(std::shared_ptr<Camera> camera);

            bool processEvent(Event event) override;

            void upDown(float degree);
            inline void up(float degree = 0)   { upDown(-(degree ? degree : speedY)); }
            inline void down(float degree = 0) { upDown(degree ? degree : speedY); }

            void leftRight(float degree);
            inline void left(float degree = 0)  { leftRight(degree ? degree : speedX); }
            inline void right(float degree = 0) { leftRight(-(degree ? degree : speedX)); }

            void lookXY(glm::vec2 delta);

            inline void zoomIn()           { setZoom(actZoom + zoomSpeed); }
            inline void zoomOut()          { setZoom(actZoom - zoomSpeed); }
            inline void zoom(float amount) { setZoom(actZoom + amount * zoomSensitivity); }

        private:
            float actZoom = 1.0f;
            float phi     = 0.0f;
            float theta   = 0.0f;

            void setZoom(float zoom);
            void updateCamera();
    };
}
