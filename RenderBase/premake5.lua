
project "RenderBase"
    kind          "StaticLib"
    language      "C++"
    cppdialect    "C++20"
    staticruntime "off" -- this links "MultiThreadedDLL" in visual studio and noes nothing outsitde of windows.
    
    targetdir "bin/%{prj.name}"
    objdir    "bin-obj/%{prj.name}"
    
    -- precompiled headers?
    
    files {
        "src/%{prj.name}/**.cpp",
        "src/%{prj.name}/**.h"
    }
    
    includedirs {
        "src/%{prj.name}"
    }
    
    -- links {
    --     "GLFW",
    --     "Glad"
    -- }
    
    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        symbols "Off"
        optimize "On" -- also could try "Speed" or "Full"
        