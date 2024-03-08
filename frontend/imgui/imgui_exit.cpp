#include <frontend/imgui/imgui_exit.h>
#include <utils/application_manager.h>

void ImGuiExitSystem::exitApplication() {
    // Set ApplicationManger::requested_exit to true
    ApplicationManager::requested_exit = true;
}
