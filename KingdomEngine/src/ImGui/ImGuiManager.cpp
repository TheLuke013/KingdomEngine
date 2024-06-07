#include "KingdomEngine/ImGui/ImGuiManager.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
	ImGuiManager::ImGuiManager()
		: isEnabled(false), window(nullptr), newFrameIsCalled(false)
	{

	}

	ImGuiManager::~ImGuiManager()
	{
		Disable();
	}

	void ImGuiManager::Init(GLFWwindow* window)
	{
		ImGuiManager::window = window;

		if (!isEnabled)
		{
			//setup imgui context
			ImGui::CreateContext();
			ImGui::StyleColorsDark();

			io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");

			isEnabled = true;
			LOG_INFO("ImGui was enabled");
		}
	}

	void ImGuiManager::Disable()
	{
		if (isEnabled)
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

			isEnabled = false;
			newFrameIsCalled = false;
			LOG_INFO("ImGui was disabled");
		}
	}

	void ImGuiManager::Render()
	{
		if (isEnabled && newFrameIsCalled)
		{
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			newFrameIsCalled = false;
		}
	}

	void ImGuiManager::CreateNewFrame()
	{
		if (isEnabled)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			newFrameIsCalled = true;

			ImGui::ShowDemoWindow(nullptr);
		}
	}
}