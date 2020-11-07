#include <iostream>
#include <functional>

#include <RenderBase/rb.h>
#include <RenderBase/platform/platform.h>

using namespace rb;

Application::Application(Configuration config) {

    // init configuration
    this->config = config;
    if (!this->config.valid) {
        addErrorMessage("Invalid configuration");
        return;
    }

    // internal initiation

    // create main window
    this->mainWindow = platform::createWindow(PROJECT_NAME, this->config.windowWidth, this->config.windowHeight);
    this->mainWindow->onEvent([=](const Event &event) { return this->update(event); });
    this->mainWindow->onDraw([=]() { this->draw(); });

    this->graphics = std::make_unique<Graphics>();
    this->scene    = std::make_unique<Scene>();

    state = ApplicationState::valid;
}

int Application::run() {
    if (state == ApplicationState::invalid) {
        addErrorMessage("Cannot run invalid application.");
        return 1; // error
    }

    if (!init()) {
        state = ApplicationState::invalid;
        addErrorMessage("Initialization failed");
        return 1; // error
    }

    std::cout << "Run...\n";
    auto res = this->mainWindow->show();
    std::cout << "End run res: " <<  res << "\n";

    return res;
}

void Application::addErrorMessage(const std::string& message) {
    if (errorMessage != "") {
        errorMessage += "\n";
    }
    errorMessage += message;
}
