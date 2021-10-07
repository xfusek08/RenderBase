
project "Sandbox"
    kind       "ConsoleApp"
    language   "C++"
    cppdialect "C++20"
    
    files {
        "**.cpp",
        "**.h"
    }
    
    links {
        "RenderBase"
    }

    includedirs {
        ".",
        importLibIncludes("RenderBase")
    }
    
    filter "configurations:Debug"
        defines { "DEBUG", "NO_ASSERT" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        symbols "Off"
        optimize "On" -- also could try "Speed" or "Full"
        