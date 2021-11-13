
#include <RenderBase/gui.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

using namespace rb::gui;

const char* glsl_version = "#version 460";

Gui::Gui(const window::Window& window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGui_ImplGlfw_InitForOpenGL(window.getGLFWHandle(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    // styling move to custom method to be overriden
    ImGui::StyleColorsDark();
    // fonts?
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::update(const input::InputState& inputState, const timing::TimeStep& tick)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    bool showDemo = true;
    ImGui::ShowDemoWindow(&showDemo);
    
    ImGui::Render();
}

void Gui::draw()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
