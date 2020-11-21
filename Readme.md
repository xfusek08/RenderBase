# RenderBase

## About
This is simple platform for personal use to setup graphics project easily.
It abstracts necessary duties as window setups, OpenGL initiation.
It provides simple `draw()` - `update()` functions wrapped in `Application` class to allow writing small OpenGL apps right away.

This projects is developed as various apps (mainly school assignments) using it will need more functionality.

### TODO & ideas:
This is list of want-to features and known issues (later maybe moved to github issues).

* Make it easy to use include library and example use with subrepository
* Fix warning:
  ```
  [build] LINK : warning LNK4098: Výchozí knihovna MSVCRT je v konfliktu s použitím jiných knihoven. Použijte /NODEFAULTLIB:library.
  ```
* maybe migrate from CMake to [Premake](https://premake.github.io/)?
* Dynamic window size changing
* better logging (levels) and destinations
* FPS capping not working properly ...
* More accurate measurement of frame time exclude delays