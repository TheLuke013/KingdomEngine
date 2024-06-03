project "DearImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"include/ImGui",
		"../GLFW/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"