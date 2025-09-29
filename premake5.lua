workspace "Carbon"
   configurations { "Debug", "Release" }

project "Carbon"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20" 
   targetdir "bin/%{cfg.buildcfg}"
   architecture "x64"
   
   pchheader "cbpch.h"
   pchsource "Carbon/src/Core/cbpch.cpp"

   files { "Carbon/src/**.h", "Carbon/src/**.cpp", "Carbon/src/**.hpp" }
   includedirs {"Dependencies/GLFW/include", "Carbon/src", "Dependencies/GLEW/include" , "Dependencies/GLFW/include", "Carbon/src/Core", "vendor/glm/glm", "vendor/include", "vendor", "Dependencies/ImGui" }

   defines {"CARBON"}

   filter "system:windows"
      defines {"PLATFORM_WINDOWS"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      optimize "Off"  

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20" 
   targetdir "x64/%{cfg.buildcfg}"

   files { "Sandbox/src/**.h", "Sandbox/src/**.cpp", "Sandbox/src/**.hpp" }
   includedirs {"Carbon/src", "Carbon/src/Core", "Sandbox/src", "vendor/glm/glm", "vendor/include", "Dependencies/GLEW/include", "Dependencies/GLFW/include", "vendor",  "Dependencies/ImGui" }
   libdirs { "bin/%{cfg.buildcfg}", "Dependencies/GLEW/lib/Release/x64", "Dependencies/ImGui/bin/ImGui/%{cfg.buildcfg}" }
   links {"Carbon", "ImGui", "glew32", "glfw3", "opengl32" }

   filter { "action:vs2022" }
      libdirs {"Dependencies/GLFW/lib-vc2022"}
      architecture "x64"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      optimize "Off"  

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"