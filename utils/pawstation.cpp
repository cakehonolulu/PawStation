
#include <cstdint>
#include <pawstation.h>

ExitSystem* Pawstation::exitSystem = nullptr;
bool Pawstation::requested_exit = false;
bool Pawstation::abort = false;

void Pawstation::setExitSystem(ExitSystem* exitSystem) {
    Pawstation::exitSystem = exitSystem;
}

bool Pawstation::requestedExit() {
    return requested_exit;
}

bool Pawstation::aborted() {
    return abort;
}

std::uint32_t Pawstation::exit_() {
    if (exitSystem) {
        exitSystem->exitApplication();
    }

    return 0;
}
