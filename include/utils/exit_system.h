#pragma once

class ExitSystem {
public:
    virtual ~ExitSystem() = default;
    virtual void exitApplication() = 0;
};
