
local projectName = "RenderBase"
local publicIncludes = {
    "src"
}
local privateIncludes = {}

project (projectName)
    kind          "SharedLib"
    language      "C++"
    cppdialect    "C++20"
    staticruntime "off" -- this links "MultiThreadedDLL" in visual studio and noes nothing outsitde of windows.
    
    files {
        "src/**.cpp",
        "src/**.h"
    }
    
    includedirs  (publicIncludes)
    includedirs  (privateIncludes)
    
    setLibraryUsage (projectName, publicIncludes)
    
    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        symbols "Off"
        optimize "On" -- also could try "Speed" or "Full"
        