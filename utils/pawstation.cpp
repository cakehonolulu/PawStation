#include <pawstation.h>

ExitSystem* Pawstation::exitSystem = nullptr;
bool Pawstation::requested_exit = false;

void Pawstation::setExitSystem(ExitSystem* exitSystem) {
    Pawstation::exitSystem = exitSystem;
}

bool Pawstation::requestedExit() {
    return requested_exit;
}

void Pawstation::exit_() {
    if (exitSystem) {
        exitSystem->exitApplication();
    }
}