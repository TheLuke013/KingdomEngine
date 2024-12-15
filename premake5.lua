workspace "KingdomEngine"
	startproject "KingdomEditor"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

group "Libs"
	include "ThirdParty/ImGui"
group ""

project "KingdomEngine"
	location "KingdomEngine"
	kind "StaticLib"
	language "C++"

	targetdir ("build/")
	objdir ("build/obj/")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
		"ThirdParty/stb/src/stb_image.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
		"GLM_ENABLE_EXPERIMENTAL",
		"GLEW_STATIC"
	}

	includedirs
	{
		"%{prj.name}/include",
		"ThirdParty/spdlog/include",
		"ThirdParty/ImGui/include",
		"ThirdParty/SDL2/include",
		"ThirdParty/GLM/include",
		"ThirdParty/GLEW/include",
		"ThirdParty/stb/include",
		"ThirdParty/rapidjson/include"
	}

	links
	{
		"ThirdParty/SDL2/lib/SDL2.lib",
        "ThirdParty/GLEW/lib/glew32s.lib",
        "DearImGui",
        "opengl32.lib",
        "Winmm.lib",
        "Imm32.lib",
        "Version.lib"
	}
	
	postbuildcommands
	{
		"{COPY} %{cfg.buildtarget.abspath} ../bin/"
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

project "KingdomEditor"
	location "KingdomEditor"
	kind "ConsoleApp"
	language "C++"

	targetdir ("build/")
	objdir ("build/obj/")

	files
	{
		"%{prj.name}/include/**.h",
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
		"%{prj.name}/include",
		"KingdomEngine/include",
		"ThirdParty/ImGui/include",
		"ThirdParty/spdlog/include",
		"ThirdParty/SDL2/include",
		"ThirdParty/GLM/include",
		"ThirdParty/GLEW/include",
		"ThirdParty/stb/include",
		"ThirdParty/rapidjson/include"
	}

	links
	{
		"KingdomEngine",
		"ThirdParty/SDL2/lib/SDL2main.lib"
	}
	
	postbuildcommands
	{
		"{COPY} %{cfg.buildtarget.abspath} ../bin/"
	}
	
	postbuildcommands
	{
		"{COPY} ../ThirdParty/SDL2/lib/SDL2.dll ../bin/"
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