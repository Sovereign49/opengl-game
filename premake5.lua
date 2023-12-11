workspace "OpenGL"
  configurations { "Debug" }

project "OpenGL"
  kind "WindowedApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  
  files { "src/**.h", "src/**.cpp" }
  includedirs { "src/vendor", "src" }

  filter "system:linux"
      links {"GL", "glfw", "GLEW" }

