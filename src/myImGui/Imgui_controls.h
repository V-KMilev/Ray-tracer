#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Settings.h"
#include "Log.h"

class MyImGui {
	public:
		MyImGui() {}
		~MyImGui() {}

		void setup(GLFWwindow* window, const char* gl_version) {
			/* ImGui Setup */
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init(gl_version);
		}

		void newFrame() {
			/* ImGui New Frame */
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void shutdown() {
			/* ImGui Shutdown */
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		void render() {
			/* ImGui Render */
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		void content() {
			setStyle();

			ImGui::Begin("Menu");
			ImGui::InputInt("Samples per pixel", &samples_per_pixel, 0, 1337);
			ImGui::InputInt("Max depth", &max_depth, 0, 250);
			ImGui::NewLine();

			if(ImGui::SliderFloat3("Camera position", &lookfrom[0], -13.0f, 13.0f)) {
				change_position = true;
			}
			else { change_position = false; }

			if(ImGui::SliderFloat3("Camera focus", &lookat[0], -13.0f, 13.0f)) {
				change_view = true;
			}
			else { change_view = false; }

			if(ImGui::InputFloat("Camera aperture ", &aperture, 0.0f, 10.0f)) {
				change_aperture = true;
			}
			else { change_aperture = false; }
			ImGui::NewLine();

			if(ImGui::ColorEdit3("Background color", (float*) &background)) {
				change_bg = true;
			}
			else { change_bg = false; };
			ImGui::NewLine();

			ImGui::InputFloat("Move precision", &precision, 0, 37);
			ImGui::NewLine();

			ImGui::Checkbox("Multithreading", &change_multithreading);
			ImGui::SameLine();

			ImGui::Checkbox("Static render", &change_static);
			ImGui::NewLine();

			ImGui::Separator();

			ImGui::TextColored(ImVec4(0.7f, 0.0f, 0.3f, 1.0f), "BASIC INFO");
			ImGui::NewLine();

			ImGui::Text("Total buckets: %d", total_buckets);

			ImGui::Text("Bucket size: %d", bucket_size);

			ImGui::Text("Max Threads: %d", MAX_NUMBER_OF_THREADS);
			ImGui::NewLine();

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::Separator();
			ImGui::NewLine();

			if(ImGui::Button("Stop")) {
				change_run = false;
			}
			ImGui::SameLine();

			if(ImGui::Button("Run")) {
				change_run = true;
			}
			ImGui::SameLine();

			if(ImGui::Button("Clear")) {
				change_clear = true;

				max_depth  = default_max_depth;
				background = default_background;
			} else { change_clear = false; }

			ImGui::SameLine();

			if(ImGui::Button("Reset")) {
				change_default = true;

				max_depth  = default_max_depth;
				lookfrom   = default_lookfrom;
				lookat     = default_lookat;
				background = default_background;

			} else { change_default = false; }
			ImGui::SameLine();
			ImGui::End();

			// ImGui::Begin("Console log");

			// const std::string &msg = Logger::getDefaultLogger().str();

			// ImGui::InputTextMultiline("", (char*)msg.c_str(), msg.length());
			// ImGui::End();
		}

	private:
		void setStyle() {
			/* ImGui Style */
			ImVec4* colors = ImGui::GetStyle().Colors;

			ImGui::GetStyle().WindowRounding = 0.0f;
			ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f, 0.5f);

			colors[ImGuiCol_TitleBgActive]        = ImVec4(0.7f, 0.0f, 0.3f, 1.0f);
			colors[ImGuiCol_TitleBg]              = ImVec4(0.6f, 0.0f, 0.3f, 1.0f);

			colors[ImGuiCol_Button]               = ImVec4(0.7f, 0.0f, 0.3f, 1.0f);
			colors[ImGuiCol_ButtonHovered]        = ImVec4(0.6f, 0.0f, 0.3f, 1.0f);
			colors[ImGuiCol_ButtonActive]         = ImVec4(1.0f, 0.0f, 0.3f, 1.0f);

			colors[ImGuiCol_SliderGrab]           = ImVec4(0.7f, 0.0f, 0.3f, 1.0f);
			colors[ImGuiCol_SliderGrabActive]     = ImVec4(1.0f, 0.0f, 0.3f, 1.0f);

			colors[ImGuiCol_FrameBg]              = ImVec4(0.1f, 0.0f, 0.1f, 1.0f);
			colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.3f, 0.0f, 0.1f, 1.0f);
			colors[ImGuiCol_FrameBgActive]        = ImVec4(0.4f, 0.0f, 0.1f, 1.0f);

			colors[ImGuiCol_CheckMark]            = ImVec4(0.7f, 0.0f, 0.3f, 1.0f);
			colors[ImGuiCol_Separator]            = ImVec4(0.7f, 0.0f, 0.3f, 1.0f);

			colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.2f, 0.0f, 0.1f, 1.0f);
			colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.6f, 0.0f, 0.2f, 1.0f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.7f, 0.0f, 0.2f, 1.0f);
			colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.7f, 0.0f, 0.3f, 1.0f);

			colors[ImGuiCol_ResizeGrip]           = ImVec4(0.6f, 0.0f, 0.3f, 1.0f);
			colors[ImGuiCol_ResizeGripHovered]    = ImVec4(0.7f, 0.0f, 0.3f, 1.0f);
			colors[ImGuiCol_ResizeGripActive]     = ImVec4(0.7f, 0.0f, 0.3f, 1.0f);

			colors[ImGuiCol_TextSelectedBg]       = ImVec4(0.3f, 0.0f, 0.1f, 1.0f);
		}
};
