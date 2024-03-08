#pragma once

#include <utils/exit_system.h>

class ImGuiExitSystem : public ExitSystem {
public:
    void exitApplication() override;
};
