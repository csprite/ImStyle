# ImStyle
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
## Thanks
