workspace "OpenGL"
  configurations { "Debug", "Release" }

project "OpenGL"
  kind "WindowedApp"
  language "C++" 
  targetdir "bin/%{cfg.buildcfg}" 
  
  files { "**.h", "**.cpp" }

  filter "system:linux"
      links {"GL", "glfw", "GLEW"}

  filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
