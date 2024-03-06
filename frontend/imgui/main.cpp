#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileDialog.h"
#include <cstdio>
#include <SDL2/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#include <bus/bus.h>
#include <cpu/cpu.h>

int main(int, char**)
{
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	Bus *bus = new Bus();
	Cpu *cpu = new Cpu(bus);


	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
	// GL 3.2 Core + GLSL 150
	const char* glsl_version = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_Window* window = SDL_CreateWindow("Pawstation | SDL2 (OpenGL 3)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
	if (window == nullptr)
	{
		printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		return -1;
	}

	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Our state
	bool cpu_reg_debug_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	bool done = false;

	while (!done)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		IGFD::FileDialogConfig config; config.path = ".";

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open BIOS", ""))
				{
					ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".*,.cpp,.h,.hpp", config);
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Debug"))
			{
				static bool menu_toggle_cpu_reg_window = false;

				ImGui::MenuItem("CPU Registers", "", &menu_toggle_cpu_reg_window, true);

				// Check the status of the menu item and act accordingly
				if (menu_toggle_cpu_reg_window)
				{
					cpu_reg_debug_window = true;
				}
				else
				{
					cpu_reg_debug_window = false;
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			bool isButtonEnabled = true;

			ImGui::Begin("Pawstation debug");

			if (bus->is_bios_loaded()) {
				ImGui::Text("BIOS loaded");
			}
			else {
				ImGui::Text("BIOS not loaded");
			}

			// Use the condition to enable or disable the button
			if (bus->is_bios_loaded())
			{
				if (ImGui::Button("Run"))
				{
					// Handle button click
				}
			}

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		if (cpu_reg_debug_window)
		{
			ImGui::Begin("CPU Registers", &cpu_reg_debug_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			                                                        // Display the general-purpose registers
			ImGui::Text("General-Purpose Registers:");

			const int numColumns = 4;  // Adjust the number of columns as needed
			const float columnWidth = 150.0f;  // Adjust the column width as needed

			ImGui::Columns(numColumns, nullptr, false);

			for (int i = 0; i < 32; ++i)
			{
				ImGui::Text("%s:", cpu->cpu_register_names[i].c_str());
				ImGui::NextColumn();
				ImGui::Text("0x%08X", cpu->registers[i]);
				ImGui::NextColumn();
			}

			ImGui::Columns(1);  // Reset to a single column layout

			// Display the COP0 registers
			ImGui::Separator();
			ImGui::Text("COP0 Registers:");

			ImGui::Columns(numColumns, nullptr, false);

			for (int i = 0; i < 32; ++i)
			{
				// Skip printing if the register name is "Reserved"
				if (cpu->cop0_register_names[i] != "Reserved")
				{
					ImGui::Text("%s:", cpu->cop0_register_names[i].c_str());
					ImGui::NextColumn();
					ImGui::Text("0x%08X", cpu->cop0_registers[i]);
					ImGui::NextColumn();
				}
			}

			ImGui::Columns(1);  // Reset to a single column layout

			// Display other relevant information as needed
			ImGui::Separator();
			ImGui::Text("Program Counter (PC): 0x%08X", cpu->pc);
			ImGui::Text("Next Program Counter (Next PC): 0x%08X", cpu->next_pc);

			ImGui::End();
		}

		if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
			if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
				std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				bus->load_bios(filePathName);
			}

			// close
			ImGuiFileDialog::Instance()->Close();
		}

		// Rendering
		ImGui::Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}