#ifndef AWS_DESKTOP_IMGUI_SHIM_H
#define AWS_DESKTOP_IMGUI_SHIM_H

/**
 * Helper overrides for using vector<string> with List/Combo boxes.
 * https://eliasdaler.github.io/using-imgui-with-sfml-pt2
 */
namespace ImGui
{
  bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);

  bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values);
}

#endif
