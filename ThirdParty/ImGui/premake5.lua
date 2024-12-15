project "DearImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("build/")
	objdir ("build/obj/")

	files
	{
		"include/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"include/ImGui",
		"../SDL2/include/SDL"
	}
	
	postbuildcommands
	{
		"{COPY} %{cfg.buildtarget.abspath} ../../bin/"
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