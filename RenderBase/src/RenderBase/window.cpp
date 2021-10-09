
#include <RenderBase/window.h>
#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

#include <GLFW/glfw3.h>

using namespace std;
using namespace rb;
using namespace rb::window;

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

void* getGLFunctionTablePointer()
{
    if (glfwWindowCount > 0) {
        return (void*)glfwGetProcAddress;
    }
    return nullptr;
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
    
    // init glfw if this is out first window
    if (glfwWindowCount == 0) {
        bool sucess = glfwInit();
        RB_ASSERT_MSG(sucess, "GLFW initialized failed.");
        glfwSetErrorCallback(GLFWErrorCallback);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    }
    
    // create window
    glfwWindowCount++;
    state->glfwWindowHandle = glfwCreateWindow(state->width, state->height, state->title, nullptr, nullptr);
    setVSynch(state->vSynchEnabled);
    // this is used to be able to access m_data in glfw callbacks: https://discourse.glfw.org/t/what-is-a-possible-use-of-glfwgetwindowuserpointer/1294/2
    // uncomment if needed:
    // glfwSetWindowUserPointer(m_Window, &m_Data);
    
    // create opengl context
    makeGLContextCurrent();
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

// Getters

bool Window::isOpen() const
{
    return state->glfwWindowHandle != nullptr;
}

bool Window::getVSynch() const
{
    return state->vSynchEnabled;
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
        RB_DEBUG("Fireing Window close event");
        state->eventDispatcher.fireEvent(events::EVENT_CODE_APPLICATION_QUIT, this, dummy);
    }
}

// OpenGL
bool Window::makeGLContextCurrent()
{
    if (!isOpen()) {
        return false;
    }
    glfwMakeContextCurrent(state->glfwWindowHandle);
    return true;
}
