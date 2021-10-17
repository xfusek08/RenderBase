
# Render Base

A simple static library for quick opengl application setup using using statically linked dependencies included as git submodules.

## Using the library
Just include this repo as submodule to your project and include it int the projects CMakeLists.txt

Add This library as git submodule:

``` shell
git submodule add https://github.com/xfusek08/RenderBase vendor/RenderBase
git submodule update --init --recursive
```

Add to jour projects in CMakeLists.txt:
``` cmake
...

add_subdirectory(vendor/RenderBase)

...

target_link_libraries(${PROJECT_NAME}
    RenderBase
)
...

```