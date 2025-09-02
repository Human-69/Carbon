workspace "Sandbox"
   configurations { "Debug", "Release" }

project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20" 
   targetdir "bin/%{cfg.buildcfg}"

   files { "src/**.h", "src/**.cpp", "src/**.hpp" }
   includedirs {"../CarbonCore/src" , "../CarbonGL/src", "src", "../vendor/glm/glm" }
   libdirs { "lib" }

   filter { "system:windows", "action:gmake" }
      buildoptions { "-m64" }
      linkoptions  { "-m64" }

   filter "toolset:gcc or toolset:clang"
    buildoptions { "-w", "-Wfatal-errors" }

    links {"CarbonCore", "CarbonGL", "user32", "gdi32", "shell32", "kernel32" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"