workspace "OpenGL"
  configurations { "Debug", "Release" }

project "OpenGL"
  kind "WindowedApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  
  files { "src/**.h", "src/**.cpp" }
  includedirs { "src/vendor" }

  filter "system:linux"
      links {"GL", "glfw", "GLEW", "imgui" }

  filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
