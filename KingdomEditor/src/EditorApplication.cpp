#include "KingdomEditor/EditorApplication.h"
#include "KingdomEditor/ProjectManager.h"

namespace Editor
{
	EditorApplication::EditorApplication()
        : keDir(KE::IOUtils::GetUserDir() + "\\KingdomEngine")
	{
        //Search fonts and load default font
        KE::FontManager::Get().FindFonts("..\\resources\\fonts", ".ttf");

        for (const auto& font : KE::FontManager::Get().GetFonts())
        {
            if (font->properties.filePath == "..\\resources\\fonts\\Roboto-Regular.ttf")
            {
                font->properties.name = "Default";
                KE::ImGuiManager::Get().LoadFont(font);
            }
            else if (font->properties.filePath == "..\\resources\\fonts\\Roboto-Bold.ttf")
            {
                font->properties.name = "Default Bold";;
            }
        }
	}

	EditorApplication::~EditorApplication()
	{

	}

	void EditorApplication::OnReady()
	{
	    //Check KE dir
	    if (!std::filesystem::exists(keDir))
        {
            std::filesystem::create_directory(keDir);
            LOG_INFO("KE directory created");
        }

        //Open and load projects data file
        projectsFile.Open(keDir + "\\projects.json", KE::ModeFlags::READ_WRITE);
        projectsFile.Close();

        ONREADY_ALL_IM_WINDOW();
	}

	void EditorApplication::OnUpdate()
	{
        if (ProjectManager::Get().GetLoadedProject())
        {
            std::string newTitle = "Kingdom Engine - " + ProjectManager::Get().GetLoadedProject()->properties.name;
            GetWindow().SetTitle(newTitle);
        }
	}

	void EditorApplication::OnEvent(KE::Event e)
	{

	}

	void EditorApplication::OnImGuiRender()
	{
	    //ImGui::ShowMetricsWindow();
		//ImGui::ShowDemoWindow();
		UPDATE_ALL_IM_WINDOW();
	}

	void EditorApplication::OnMenuBarRender()
	{
        UPDATE_ALL_IM_MENU();
	}

	void EditorApplication::OnDockspaceUpdate()
	{
		UPDATE_ALL_IM_WINDOW_DOCKSPACE(KE::ImGuiManager::Get());
	}
}

KE::Application* KE::CreateApplication()
{
	return new Editor::EditorApplication();
}
