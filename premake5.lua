workspace "KingdomEngine"
	startproject "KingdomEditor"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "KingdomEngine"
	location "KingdomEngine"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
		"ThirdParty/GLAD/src/glad.c",
		"ThirdParty/stb/src/stb_image.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
		"GLM_ENABLE_EXPERIMENTAL"
	}

	includedirs
	{
		"%{prj.name}/include",
		"ThirdParty/spdlog/include",
		"ThirdParty/ImGui/include",
		"ThirdParty/GLAD/include",
		"ThirdParty/GLM/include",
		"ThirdParty/GLFW/include",
		"ThirdParty/stb/include"
	}

	links
	{
		"ThirdParty/GLFW/lib/glfw3.lib",
		"DearImGui",
		"opengl32.lib"
	}

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

project "KingdomEditor"
	location "KingdomEditor"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING"
	}

	includedirs
	{
		"KingdomEngine/include",
		"ThirdParty/ImGui/include",
		"ThirdParty/spdlog/include",
		"ThirdParty/GLAD/include",
		"ThirdParty/GLM/include",
		"ThirdParty/GLFW/include",
		"ThirdParty/stb/include"
	}

	links
	{
		"KingdomEngine"
	}

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

project "DearImGui"
	location "ThirdParty/ImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"ThirdParty/ImGui/include/**.h",
		"ThirdParty/ImGui/src/**.cpp"
	}

	includedirs
	{
		"ThirdParty/ImGui/include/ImGui",
		"ThirdParty/GLFW/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"