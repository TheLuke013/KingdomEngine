#include "KingdomEngine/ImGui/ImGuiManager.h"
#include "KingdomEngine/Core/Log.h"
#include "KingdomEngine/Core/Event.h"

namespace KE
{
	ImGuiManager::ImGuiManager()
		: isEnabled(false), window(nullptr), newFrameIsCalled(false), loadedFont(nullptr)
	{

	}

	ImGuiManager::~ImGuiManager()
	{
		Disable();
	}

	ImGuiManager& ImGuiManager::Get()
	{
		static ImGuiManager* instance = new ImGuiManager();
		return *instance;
	}

	void ImGuiManager::Init(SDL_Window* window)
	{
		ImGuiManager::window = window;

		if (!isEnabled)
		{
			//setup imgui context
			ImGui::CreateContext();
			ImGui::StyleColorsDark();

			ImGuiIO& io = ImGui::GetIO(); (void)io;
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

			//LOAD FONT IF ANY LOADED
			if (loadedFont != nullptr)
			{
				io.Fonts->AddFontFromFileTTF(loadedFont->properties.filePath.c_str(), loadedFont->properties.size);
				io.Fonts->Build();
			}

			ImGui_ImplSDL2_InitForOpenGL(window, Renderer::GetContext());

			//detect opengl version selected
			if (DetectGLContextVersion() == 3)
			{
				ImGui_ImplOpenGL3_Init("#version 330");
			}
			else if (DetectGLContextVersion() == 2)
			{
				ImGui_ImplOpenGL2_Init();
			}

			isEnabled = true;
			LOG_INFO("ImGui was enabled");
		}
	}

	void ImGuiManager::Disable()
	{
		if (isEnabled)
		{
			if (DetectGLContextVersion() == 3)
			{
				ImGui_ImplOpenGL3_Shutdown();
			}
			else if (DetectGLContextVersion() == 2)
			{
				ImGui_ImplOpenGL2_Shutdown();
			}

			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();

			isEnabled = false;
			newFrameIsCalled = false;
			LOG_INFO("ImGui was disabled");
		}
	}

	void ImGuiManager::Restart()
	{
		Disable();
		Init(window);
	}

	void ImGuiManager::Render()
	{
		if (isEnabled && newFrameIsCalled)
		{
			ImGui::Render();

			if (DetectGLContextVersion() == 3)
			{
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			}
			else if (DetectGLContextVersion() == 2)
			{
				ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
			}

			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
				SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
			}

			newFrameIsCalled = false;
		}
	}

	void ImGuiManager::LoadFont(Font* font)
	{
		loadedFont = font;
		DISPATCH_EVENT(EventType::RESTART_IMGUI);
	}

	void ImGuiManager::BeginDockspace()
	{
		if (isEnabled)
		{
			//properties
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			ImGuiViewport* viewport = ImGui::GetMainViewport();

			//setting main window
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			//creates main window
			ImGui::Begin("MainDockSpace", nullptr, window_flags);

			dockspaceID = ImGui::GetID("MainDockSpace");
			ImGui::DockBuilderRemoveNode(dockspaceID);
			ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);

			ImGui::DockBuilderSetNodeSize(dockspaceID, ImGui::GetIO().DisplaySize);

			dockSides.dock_main = dockspaceID;
			dockSides.dock_left = ImGui::DockBuilderSplitNode(dockSides.dock_main, ImGuiDir_Left, 0.2f, nullptr, &dockSides.dock_main);
			dockSides.dock_right = ImGui::DockBuilderSplitNode(dockSides.dock_main, ImGuiDir_Right, 0.15f, nullptr, &dockSides.dock_main);
			dockSides.dock_down = ImGui::DockBuilderSplitNode(dockSides.dock_main, ImGuiDir_Down, 0.15f, nullptr, &dockSides.dock_main);
			dockSides.dock_left_top = ImGui::DockBuilderSplitNode(dockSides.dock_left, ImGuiDir_Up, 0.5f, nullptr, &dockSides.dock_left);
			dockSides.dock_left_bottom = dockSides.dock_left;
		}
	}

	void ImGuiManager::EndDockspace()
	{
		if (isEnabled)
		{
			static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

			ImGui::DockBuilderFinish(dockspaceID);
			ImGui::PopStyleVar(2);

			//setting dockspace
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

			ImGui::End();
		}
	}

	int ImGuiManager::DetectGLContextVersion()
	{
		if (Renderer::GetVersion().glVersion == OpenGL3)
		{
			return 3;
		}
		else if (Renderer::GetVersion().glVersion == OpenGL2)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

	void ImGuiManager::CreateNewFrame()
	{
		if (isEnabled)
		{
			if (DetectGLContextVersion() == 3)
			{
				ImGui_ImplOpenGL3_NewFrame();
			}
			else if (DetectGLContextVersion() == 2)
			{
				ImGui_ImplOpenGL2_NewFrame();
			}

			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			newFrameIsCalled = true;
		}
	}
}
