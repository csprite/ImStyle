# ImGooeyStyles
A Small C++ 11 Library To Save &amp; Load ImGui UI Configuration (Colors, Sizes, Etc).

---
## Setup

just drag and crop [imgui_styles.cpp](./imgui_styles.cpp) && [imgui_styles.h](imgui_styles.h) in your project, add `imgui_styles.cpp` to your build system so it compiles & links, finally #include `imgui_styles.h` in your code and start using the functions!

---
## API

**Save Configuration**: to save the styles to a file with data structured in ini format

```c++
IMGUI_API void ImGui::SaveStylesTo(const char* fileName);
```

**Load Configuration**: to load the styles from a file with data structured in ini format

```c++
IMGUI_API void ImGui::LoadStyleFrom(const char* fileName);
```

---
# Building Demo

if you want to see the demo of the library in action, i've provided a demo which you can build & run, it can be used as a tool to modify imgui styles and save them for use later.

1. Clone The Repository Using Git: `git clone https://github.com/pegvin/ImGooeyStyles`
2. cd into the newly created directory: `cd ImGooeyStyles/`
3. Build The Demo Using `make`: `make all`

---
## Thanks
