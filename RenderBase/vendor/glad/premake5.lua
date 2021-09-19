
project ("Glad")
    kind          "StaticLib"
    language      "C"
    staticruntime "off"
    
    files {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }
    
    includedirs  {
        "include"
    }
    
    exportLibIncludes ("Glad", {
        "include"
    })
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        runtime "Release"
        symbols "Off"
        optimize "On"
        