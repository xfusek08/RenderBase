
include "vendor/glad"
include "vendor/glfw"

project ("RenderBase")
    kind          "SharedLib"
    language      "C++"
    cppdialect    "C++20"
    staticruntime "off" -- this links "MultiThreadedDLL" in visual studio and noes nothing outsitde of windows.
    
    files {
        "src/**.cpp",
        "src/**.h"
    }
    
    includedirs  {
        "src",
        importLibIncludes("Glad"),
        importLibIncludes("GLFW")
    }
    
    links {
        "glad",
        "glfw"
    }
    
    exportLibIncludes ("RenderBase", {
        "src"
    })
    
    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        symbols "Off"
        optimize "On" -- also could try "Speed" or "Full"
        