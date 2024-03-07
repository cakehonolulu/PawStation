#pragma once

#include <vector>
#include <string>

namespace ImGuiLogger
{
    // Custom log function for ImGui frontend
    void ImGuiLogFunction(const std::string& message);

    // Initialize ImGui Logger
    void InitializeImGuiLogger();

    // ImGui-specific setup and rendering code...

    // Example of using ImGui Logger
    void ImGuiSpecificCode();

    // Access the ImGui log buffer
    const std::vector<std::string>& GetImGuiLogBuffer();

    // Clear the ImGui log buffer
    void ClearImGuiLogBuffer();
}
