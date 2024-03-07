#include <log/log.h>
#include <imgui.h>

namespace ImGuiLogger
{
    static std::vector<std::string> ImGuiLogBuffer;

    void ImGuiLogFunction(const std::string& message)
    {
        ImGuiLogBuffer.push_back(message);
    }

    void ImGuiErrorFunction(const std::string& message)
    {
        ImGuiLogBuffer.push_back(message);
    }

    void InitializeImGuiLogger()
    {
        Logger::Instance().SetLogFunction(ImGuiLogFunction);
        Logger::Instance().SetErrorFunction(ImGuiErrorFunction);
    }

    const std::vector<std::string>& GetImGuiLogBuffer()
    {
        return ImGuiLogBuffer;
    }

    void ClearImGuiLogBuffer()
    {
        ImGuiLogBuffer.clear();
    }
}
