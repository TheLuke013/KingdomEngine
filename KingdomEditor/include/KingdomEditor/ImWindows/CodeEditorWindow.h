#ifndef CODE_EDITOR_WINDOW_H
#define CODE_EDITOR_WINDOW_H

#include <KingdomEngine/ImGui/ImWindow.h>
#include <KingdomEngine/Core/IO/File.h>
#include <ImGui/TextEditor.h>

#include "KingdomEditor/Project/ProjectManager.h"
#include "KingdomEditor/Utils/Globals.h"

namespace Editor
{
	class CodeEditorWindow : public KE::ImWindow
	{
	public:
		CodeEditorWindow() : KE::ImWindow("Code Editor", 640, 480, 1366, 98, true, false, KE::DockSide::MAIN)
		{
			properties.flags |= ImGuiWindowFlags_HorizontalScrollbar;
			fileIsLoaded = false;
			cppFile = "";
			
			auto lang = TextEditor::LanguageDefinition::CPlusPlus();
			editor.SetLanguageDefinition(lang);
		}

		void OnReady() override
		{

		}

		void OnRender() override
		{
			//load project cpp file
			if (ProjectManager::Get().GetLoadedProject() && !fileIsLoaded)
			{
				std::string projectName = ProjectManager::Get().GetLoadedProject()->properties.name;
				projectName.erase(
					std::remove(projectName.begin(), projectName.end(), ' '),
					projectName.end()
				);
				cppFile = ProjectManager::Get().GetLoadedProject()->properties.path + "\\src\\" + projectName + ".cpp";
				fileToEdit.Open(cppFile, KE::ModeFlags::READ);
				
				if (fileToEdit.IsOpen())
				{
					std::string str((std::istreambuf_iterator<char>(fileToEdit.GetFile())), std::istreambuf_iterator<char>());
					editor.SetText(str);
					fileToEdit.Close();
				}
				else
				{
					LOG_ERROR("Could not open file: " + cppFile);
					fileToEdit.Close();
					return;
				}
				
				fileIsLoaded = true;
			}
			
			//unload cpp file
			if (!ProjectManager::Get().GetLoadedProject() && fileIsLoaded)
			{
				fileIsLoaded = false;
			}
			
			//save text
			if (ProjectManager::Get().GetLoadedProject() && fileIsLoaded && Globals::CAN_SAVE_FILE)
			{
				auto textToSave = editor.GetText();
				
				fileToEdit.Open(cppFile, KE::ModeFlags::WRITE);
				LOG_INFO(cppFile);
				fileToEdit.Write(textToSave);
				fileToEdit.Close();
				
				Globals::CAN_SAVE_FILE = false;
			}
			
			if (KE::ImGuiManager::Get().GetTheme() == KE::DEFAULT)
				editor.SetPalette(TextEditor::GetDarkPalette());
			if (KE::ImGuiManager::Get().GetTheme() == KE::DARK)
				editor.SetPalette(TextEditor::GetDarkPalette());
			if (KE::ImGuiManager::Get().GetTheme() == KE::LIGHT)
				editor.SetPalette(TextEditor::GetLightPalette());
			
			auto cpos = editor.GetCursorPosition();
			
			ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
			editor.IsOverwrite() ? "Ovr" : "Ins",
			editor.CanUndo() ? "*" : " ",
			editor.GetLanguageDefinition().mName.c_str(), fileToEdit.GetFilename().c_str());

			editor.Render("TextEditor");
		}
		
	private:
		TextEditor editor;
		KE::File fileToEdit;
		bool fileIsLoaded;
		std::string cppFile;
		
	};
}

#endif
