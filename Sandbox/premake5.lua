workspace "Sandbox"
   configurations { "Debug", "Release" }

project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20" 
   targetdir "../x64/%{cfg.buildcfg}"

   files { "src/**.h", "src/**.cpp", "src/**.hpp" }
   includedirs {"../Carbon/src", "../Carbon/src/Core", "src", "../vendor/glm/glm", "../vendor/include", "../Dependencies/GLEW/include", "../Dependencies/GLFW/include", "../vendor",  "../vendor/ImGUI" }
   libdirs { "lib", "../Dependencies/GLEW/lib/Release/x64", "../vendor/ImGUI/bin/ImGui" }

   filter { "system:windows", "action:gmake" }
      buildoptions { "-m64" }
      linkoptions  { "-m64" }
      libdirs {"../Dependencies/GLFW/lib-g++"}

   filter "toolset:gcc or toolset:clang"
    buildoptions { "-w", "-Wfatal-errors" }

   links {"Carbon", "glew32", "glfw3", "ImGui", "opengl32", "user32", "gdi32", "shell32", "kernel32" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      optimize "Off"  

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"