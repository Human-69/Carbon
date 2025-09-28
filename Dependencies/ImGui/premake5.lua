workspace "ImGui"
   configurations { "Debug", "Release" }

project "ImGui"
	kind "StaticLib"
	language "C++"
    staticruntime "off"
	architecture "x64"

	targetdir ("bin/%{prj.name}/%{cfg.buildcfg}")

	files
	{
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_demo.cpp",
		"backends/imgui_impl_glfw.cpp",
		"backends/imgui_impl_opengl3.cpp"
	}

	includedirs { "", "../../Dependencies/GLFW/include" }

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++20"

	filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      optimize "Off"  

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
