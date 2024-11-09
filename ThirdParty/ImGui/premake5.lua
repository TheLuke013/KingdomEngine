project "DearImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/")
	objdir ("bin-int/")

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