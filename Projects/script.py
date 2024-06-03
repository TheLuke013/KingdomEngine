import os
import subprocess

project_name = input("Project name: ")

premake_file_content = f"""project "{project_name}"
    location "{project_name}"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{{prj.name}}")
    objdir ("bin-int/" .. outputdir .. "/%{{prj.name}}")

    files
    {{
        "%{{prj.name}}/src/**.h",
        "%{{prj.name}}/src/**.cpp"
    }}

    defines
    {{
        "_CRT_SECURE_NO_WARNINGS",
        "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
        "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING"
    }}

    includedirs
    {{
        "../KingdomEngine/include",
        "../ThirdParty/ImGui/include",
        "../ThirdParty/spdlog/include",
        "../ThirdParty/GLAD/include",
        "../ThirdParty/GLM/include",
        "../ThirdParty/GLFW/include",
        "../ThirdParty/stb/include"
    }}

    links
    {{
        "KingdomEngine"
    }}

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

    filter "configurations:Debug"
        defines "KE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "KE_DIST"
        optimize "On"
"""

main_cpp_file_content = f"""#include <KingdomEngine/KingdomEngine.h>

class {project_name} : public KE::Application
{{
public:
	{project_name}()
	{{

	}}

	~{project_name}()
	{{

	}}

	void OnReady() override
	{{
		
	}}

	void Update() override
	{{
		
	}}

	void OnEvent(KE::Event e) override
	{{

	}}
}};

KE::Application* KE::CreateApplication()
{{
	return new {project_name}();
}}"""

#create project folder and premake file
src_directory = os.path.join(project_name, "src")
os.makedirs(src_directory, exist_ok=True)

with open("premake5.lua", "a") as file:
    file.write(premake_file_content)

#create project main cpp file
main_cpp_file_path = os.path.join(project_name, f"src\\{project_name}.cpp")
with open(main_cpp_file_path, "w") as file:
    file.write(main_cpp_file_content)
    
#re-generate engine solution
os.chdir("..")
gs_file_path = "GenerateSolution.bat"
subprocess.run([gs_file_path], shell=True)

print(f"Project {project_name} Created!")