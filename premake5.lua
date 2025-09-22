workspace "Carbon"
   configurations { "Debug", "Release" }

project "Carbon"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20" 
   targetdir "bin/%{cfg.buildcfg}"

   files { "Carbon/src/**.h", "Carbon/src/**.cpp", "Carbon/src/**.hpp" }
   includedirs {"Dependencies/GLFW/include", "Carbon/src", "Dependencies/GLEW/include" , "Dependencies/GLFW/include", "Carbon/src/Core", "vendor/glm/glm", "vendor/include", "vendor", "vendor/ImGUI" }
   libdirs { "Dependencies/GLFW/lib-g++", "Dependencies/GLEW/lib/Release/x64", "vendor/ImGUI/bin/ImGui" }

   pchheader "cbpch.h"
   pchsource "Carbon/src/core/cbpch.cpp"

   defines {"CARBON"}

   filter { "system:windows", "action:gmake" }
      buildoptions { "-m64" }
      linkoptions  { "-m64" }

   filter "toolset:gcc or toolset:clang"
    buildoptions { "-w", "-Wfatal-errors" }

   filter "system:linux"
      defines {"PLATFORM_LINUX"}
      libdirs { "Dependencies/GLEW-Linux" }
      links {"GLEW", "glfw", "GL", "ImGui" }

   filter "system:windows"
      defines {"PLATFORM_WINDOWS"}
      links {"glew32", "glfw3", "ImGui", "opengl32", "user32", "gdi32", "shell32", "kernel32" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      optimize "Off"  

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

