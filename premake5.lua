    
workspace "RenderBase"
    location "build"
    architecture "x64"
    
    startproject "HelloTriangle"
    
    configurations { "Debug", "Release" }
    
    include "RenderBase"
    include "Demos"
