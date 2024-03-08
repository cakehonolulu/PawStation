#pragma once

#include "exit_system.h"

class ApplicationManager {
public:
    static void setExitSystem(ExitSystem* exitSystem);
    static bool requestedExit();
    static void exit_();
    static bool requested_exit;
private:
    static ExitSystem* exitSystem;
};
