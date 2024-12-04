#include "KingdomEditor/EditorApplication.h"
#include "KingdomEditor/Project/ProjectManager.h"
#include "KingdomEditor/DialogBox/SaveProjectDialogBox.h"
#include "KingdomEditor/DialogBox/ExcludeProjectDialogBox.h"
#include "KingdomEditor/Utils/Globals.h"
#include "KingdomEditor/Project/ProjectBuild.h"

namespace Editor
{
    bool SaveProjectDialog::showing = false;
    bool ExcludeProjectDialog::showing = false;
    std::string ExcludeProjectDialog::projectNameToRemove = "";

    EditorApplication::EditorApplication()
    {
        closeAfterSave = false;

        ActivateImGui();

        //search fonts and load default font
        KE::FontManager::Get().FindFonts(FONTS_DIR, ".ttf");

        for (const auto &font : KE::FontManager::Get().GetFonts())
        {
            if (font->properties.filePath == FONTS_DIR + "\\Roboto-Regular.ttf")
            {
                font->properties.name = "Default";
                if (KE::ImGuiManager::Get().IsEnabled())
                    KE::ImGuiManager::Get().LoadFont(font);
            }
            else if (font->properties.filePath == FONTS_DIR + "\\Roboto-Bold.ttf")
            {
                font->properties.name = "Default Bold";
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

        LOG_WARN(keDir.GetCurrentDir());

        //open and load projects data file
        ProjectManager::Get().OpenProjectsFile();
        
        if (KE::ImGuiManager::Get().IsEnabled())
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

        static float progress = 0.0f;
        if (ProjectBuild::buildStarted && !ProjectBuild::cmakeDone && progress <= 0.50f)
        {
            ProjectBuild::buildProgress = progress;
            progress += 0.001f;
        }

        if (ProjectBuild::cmakeDone)
        {
            LOG_WARN("Project build files generated");
            ProjectBuild::buildDone = true;
            ProjectBuild::buildStarted = false;
            ProjectBuild::cmakeDone = false;
            SET_IM_WINDOW_VISIBLE("BuildProgressBar", false);
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

        //process save project dialog box
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

        //process exclude project dialog box
        KE::DialogResult excludeProjectResult = ExcludeProjectDialog::Show();
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
