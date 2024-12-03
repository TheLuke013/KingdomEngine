#include "KingdomEditor/EditorApplication.h"
#include "KingdomEditor/ProjectManager.h"
#include "KingdomEditor/DialogBox/SaveProjectDialogBox.h"
#include "KingdomEditor/Utils/Globals.h"

namespace Editor
{
    bool SaveProjectDialog::showSaveProjectDialog = false;

    EditorApplication::EditorApplication()
    {
        closeAfterSave = false;

        //search fonts and load default font
        KE::FontManager::Get().FindFonts(FONTS_DIR, ".ttf");

        for (const auto &font : KE::FontManager::Get().GetFonts())
        {
            if (font->properties.filePath == FONTS_DIR + "\\Roboto-Regular.ttf")
            {
                font->properties.name = "Default";
                KE::ImGuiManager::Get().LoadFont(font);
            }
            else if (font->properties.filePath == FONTS_DIR + "\\Roboto-Bold.ttf")
            {
                font->properties.name = "Default Bold";
                ;
            }
        }
    }

    EditorApplication::~EditorApplication()
    {
    }

    void EditorApplication::OnReady()
    {
        //check KE dir
        KE::Directory keDir;
        if (!keDir.DirExists(KE_DIRECTORY))
        {
            keDir.Create(KE_DIRECTORY);
            LOG_INFO("KE directory created");
        }

        //check projects dir
        KE::Directory projectsDir;
        if (!projectsDir.DirExists(KE_PROJECTS_DIRECTORY))
        {
            projectsDir.Create(KE_PROJECTS_DIRECTORY);
            LOG_INFO("Projects directory created");
        }

        //open and load projects data file
        ProjectManager::Get().OpenProjectsFile();

        ONREADY_ALL_IM_WINDOW();
    }

    void EditorApplication::OnUpdate()
    {
        if (ProjectManager::Get().GetLoadedProject())
        {
            std::string newTitle = "Kingdom Engine - " + ProjectManager::Get().GetLoadedProject()->properties.name;
            GetWindow().SetTitle(newTitle);
        }

        if (!ProjectManager::Get().GetLoadedProject())
        {
            GetWindow().SetTitle("Kingdom Engine - No Project Loaded");
        }
    }

    void EditorApplication::OnEvent(KE::Event e)
    {
        if (e.type_ == KE::EventType::CLOSE_APPLICATION)
        {
            if (ProjectManager::Get().GetLoadedProject())
            {
                SaveProjectDialog::SetShow();
                closeAfterSave = true;
            }
            else
            {
                Quit();
            }
        }
    }

    void EditorApplication::OnImGuiRender()
    {
        UPDATE_ALL_IM_WINDOW();

        KE::DialogResult saveProjectResult = SaveProjectDialog::Show();
        if (saveProjectResult == KE::DialogResult::Save)
        {
            if (closeAfterSave)
                Quit();
        }
        else if (saveProjectResult == KE::DialogResult::DontSave)
        {
            if (closeAfterSave)
                Quit();
        }
        else if (saveProjectResult == KE::DialogResult::Cancel)
        {
            
        }
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

KE::Application *KE::CreateApplication()
{
    return new Editor::EditorApplication();
}
