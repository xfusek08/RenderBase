
include "libUtils.lua"

workspace "RenderBase"
    location  "build"
    targetdir "bin"
    objdir    "bin"

    architecture "x64"
    
    configurations { "Debug", "Release" }
    
    include "RenderBase"
    include "Sandbox"
    -- include "Demos"
    