#include <frontend/imgui/imgui_pawstation.h>

int main(int argc, char** argv)
{
    ImGuiPawstation pawstation;
    pawstation.init();
    pawstation.run();
    return 0;
}