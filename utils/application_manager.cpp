#include <utils/application_manager.h>

ExitSystem* ApplicationManager::exitSystem = nullptr;
bool ApplicationManager::requested_exit = false;

void ApplicationManager::setExitSystem(ExitSystem* exitSystem) {
    ApplicationManager::exitSystem = exitSystem;
}

bool ApplicationManager::requestedExit() {
    return requested_exit;
}

void ApplicationManager::exit_() {
    if (exitSystem) {
        exitSystem->exitApplication();
    }
}
