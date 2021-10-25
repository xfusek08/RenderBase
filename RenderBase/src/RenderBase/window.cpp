/**
 * This file implementation is inspired by Hazel engine by Yan Chernikov:
 *   https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Platform/Windows/WindowsWindow.cpp
 */

#include <RenderBase/window.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

using namespace std;
using namespace rb;
using namespace rb::window;

// internal datastructure implementation
// ---------------------------------------------------------------------------------------------------------

struct Window::State
{
    State(events::EventDispatcher& eventDispatcher) : eventDispatcher(eventDispatcher) {}
    
    const char* title;
    int32 width;
    int32 height;
    bool vSynchEnabled;
    GLFWwindow* glfwWindowHandle;
    events::EventDispatcher& eventDispatcher;
};

static uint8 glfwWindowCount = 0;
static void GLFWErrorCallback(int error, const char* description) {
    RB_ERROR("GLFW Error (" << error << "): " << description);
}

void* rb::window::getGLFunctionTablePointer()
{
    RB_ASSERT_MSG(glfwWindowCount > 0, "rb::window::getGLFunctionTablePointer(): Cannot return function pointer when no window is created.");
    return (void*)glfwGetProcAddress;
}

// module API implementation
// ---------------------------------------------------------------------------------------------------------

// lifetime
        
Window::Window(Config config, rb::events::EventDispatcher& eventDispatcher)
{
    state = make_unique<Window::State>(eventDispatcher);
    state->title = config.title;
    state->width = config.width;
    state->height = config.height;
    state->vSynchEnabled = config.vSynchEnabled;
    state->glfwWindowHandle = nullptr;
}
        
Window::~Window() {
    if (isOpen()) {
        close();
    }
}

bool Window::show()
{
    if (isOpen()) {
        return false;
    }
    
    // Init GLFW
    
    if (glfwWindowCount == 0) {
        bool success = glfwInit();
        RB_ASSERT_MSG(success, "GLFW initialized failed.");
        glfwSetErrorCallback(GLFWErrorCallback);
        #ifdef DEBUG
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        #endif
    }
    
    // Set up GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    state->glfwWindowHandle = glfwCreateWindow(state->width, state->height, state->title, nullptr, nullptr);
    glfwWindowCount++;
    
    setVSynch(state->vSynchEnabled);
        
    glfwSetWindowUserPointer(state->glfwWindowHandle, this); // to access window instance in callbacks
    
    glfwSetWindowSizeCallback(state->glfwWindowHandle, [](GLFWwindow* window, int width, int height) {
        Window* self = (Window*)glfwGetWindowUserPointer(window);
        self->resize(width, height);
    });
    
    glfwSetKeyCallback(state->glfwWindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Window* self = (Window*)glfwGetWindowUserPointer(window);
        events::EventData data;

        switch (action) {
            case GLFW_PRESS: {
                data.u16[0] = key;
                self->state->eventDispatcher.fireEvent(events::EVENT_CODE_KEY_PRESSED, self, data);
                break;
            }
            case GLFW_RELEASE: {
                data.u16[0] = key;
                self->state->eventDispatcher.fireEvent(events::EVENT_CODE_KEY_RELEASED, self, data);
                break;
            }
            // case GLFW_REPEAT: {
            //     self->state->eventDispatcher.fireEvent(events::EVENT_CODE_KEY_PRESSED, self, data);
            //     break;
            // }
        }
    });
    
    glfwSetCursorPosCallback(state->glfwWindowHandle, [](GLFWwindow* window, double xPos, double yPos) {
        Window* self = (Window*)glfwGetWindowUserPointer(window);
        events::EventData data;
        data.f32[0] = float32(xPos);
        data.f32[1] = float32(yPos);
        self->state->eventDispatcher.fireEvent(events::EVENT_CODE_MOUSE_MOVED, self, data);
    });
    
    // Init OpenGL for the window
    
    glfwMakeContextCurrent(state->glfwWindowHandle);
    bool success = gladLoadGLLoader((GLADloadproc)window::getGLFunctionTablePointer());
    RB_ASSERT_MSG(success, "Failed to initialize GLAD");
    RB_INFO("OpenGL Info:");
    RB_INFO("  Vendor:   " << glGetString(GL_VENDOR));
    RB_INFO("  Renderer: " << glGetString(GL_RENDERER));
    RB_INFO("  Version:  " << glGetString(GL_VERSION));
    
    return true;
}

bool Window::close()
{
    if (!isOpen()) {
        return false;
    }
    
    glfwDestroyWindow(state->glfwWindowHandle);
    glfwWindowCount--;
    if (glfwWindowCount == 0) {
        glfwTerminate();
    }
    
    return true;
}

// Setters

void Window::setVSynch(bool enabled)
{
    if (state->vSynchEnabled != enabled) {
        state->vSynchEnabled = enabled;
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
    }
}

void Window::resize(uint32 newWidth, uint32 newHeight)
{
    state->width = newWidth;
    state->height = newHeight;
    
    glViewport(0, 0, newWidth, newHeight);
    
    RB_DEBUG("Window resize to: " << newWidth << " x " << newHeight);
    
    events::EventData data;
    data.u16[0] = newWidth;
    data.u16[1] = newHeight;
    
    state->eventDispatcher.fireEvent(events::EVENT_CODE_RESIZED, this, data);
}

// Getters

bool Window::isOpen() const
{
    return state->glfwWindowHandle != nullptr;
}

bool Window::getVSynch() const
{
    return state->vSynchEnabled;
}

uint32 Window::getWidth()  const
{
    return state->width;
}
            
uint32 Window::getHeight() const
{
    return state->height;
}

GLFWwindow* Window::getGLFWHandle() const
{
    return state->glfwWindowHandle;
}

// runtime

void Window::swapFrames()
{
    glfwSwapBuffers(state->glfwWindowHandle);
}

void Window::fireEvents()
{
    glfwPollEvents();
    if (glfwWindowShouldClose(state->glfwWindowHandle)) {
        events::EventData dummy;
        state->eventDispatcher.fireEvent(events::EVENT_CODE_APPLICATION_QUIT, this, dummy);
    }
}
