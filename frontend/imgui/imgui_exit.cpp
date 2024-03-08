#include <frontend/imgui/imgui_exit.h>
#include <pawstation.h>

void ImGuiExitSystem::exitApplication() {
    // Set ApplicationManger::requested_exit to true
    Pawstation::requested_exit = true;
}
