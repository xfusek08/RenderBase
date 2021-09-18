    
workspace "RenderBase"
    architecture "x64"
    
    configuration {
        "Debug",
        "Release"
    }
    
    startproject "HelloTriangle"
    
    configurations { "Debug", "Release" }
    
include "RenderBase"
include "Demos"
