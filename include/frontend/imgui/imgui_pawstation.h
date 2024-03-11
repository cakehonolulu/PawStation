#pragma once

#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#include <bus/bus.h>
#include <cpu/cpu.h>

#include <frontend/imgui/imgui_pawstation.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileDialog.h"
#include <log/log.h>
#include <log/imgui_log.h>
#include <cstdio>

#include <frontend/imgui/imgui_exit.h>

class ImGuiPawstation : public Pawstation {
public:
    void init() override;
    void run() override;

private:
    Bus* bus = nullptr;
    Cpu* cpu = nullptr;
    SDL_Window* window = nullptr;
    SDL_GLContext gl_context;
    std::string glsl_version;
};

void imgui_disassembly_window(Cpu *cpu, Bus *bus);
