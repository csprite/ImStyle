#include <stdio.h>
#include <stdlib.h>

#include "imgui_styles.h"
#include "ini.h"

IMGUI_API void ImGui::LoadStyleFrom(const char* fileName) {
}

static const char* ImGuiDirToText(int direction) {
	switch (direction) {
	    case ImGuiDir_None:   return "None";
	    case ImGuiDir_Left:   return "Left";
	    case ImGuiDir_Right:  return "Right";
	    case ImGuiDir_Up:     return "Up";
	    case ImGuiDir_Down:   return "Down";
	    default:              return "Invalid";
	}
}

IMGUI_API void ImGui::SaveStylesTo(const char* fileName) {
	ImGuiStyle& style = ImGui::GetStyle();

	FILE* fp = fopen(fileName, "w");

	// Header
	fprintf(fp, "[ImGuiStyles]\n");

	// Floats
    fprintf(fp, "Alpha = %f\n",                      style.Alpha);
    fprintf(fp, "DisabledAlpha = %f\n",              style.DisabledAlpha);
    fprintf(fp, "WindowRounding = %f\n",             style.WindowRounding);
    fprintf(fp, "WindowBorderSize = %f\n",           style.WindowBorderSize);
    fprintf(fp, "ChildRounding = %f\n",              style.ChildRounding);
    fprintf(fp, "ChildBorderSize = %f\n",            style.ChildBorderSize);
    fprintf(fp, "PopupRounding = %f\n",              style.PopupRounding);
    fprintf(fp, "PopupBorderSize = %f\n",            style.PopupBorderSize);
    fprintf(fp, "FrameRounding = %f\n",              style.FrameRounding);
    fprintf(fp, "FrameBorderSize = %f\n",            style.FrameBorderSize);
    fprintf(fp, "IndentSpacing = %f\n",              style.IndentSpacing);
    fprintf(fp, "ColumnsMinSpacing = %f\n",          style.ColumnsMinSpacing);
    fprintf(fp, "ScrollbarSize = %f\n",              style.ScrollbarSize);
    fprintf(fp, "ScrollbarRounding = %f\n",          style.ScrollbarRounding);
    fprintf(fp, "GrabMinSize = %f\n",                style.GrabMinSize);
    fprintf(fp, "GrabRounding = %f\n",               style.GrabRounding);
    fprintf(fp, "LogSliderDeadzone = %f\n",          style.LogSliderDeadzone);
    fprintf(fp, "TabRounding = %f\n",                style.TabRounding);
    fprintf(fp, "TabBorderSize = %f\n",              style.TabBorderSize);
    fprintf(fp, "TabMinWidthForCloseButton = %f\n",  style.TabMinWidthForCloseButton);
    fprintf(fp, "MouseCursorScale = %f\n",           style.MouseCursorScale);
    fprintf(fp, "CurveTessellationTol = %f\n",       style.CurveTessellationTol);
    fprintf(fp, "CircleTessellationMaxError = %f\n", style.CircleTessellationMaxError);

    // Directions
    fprintf(fp, "WindowMenuButtonPosition = %s\n", ImGuiDirToText(style.WindowMenuButtonPosition));
    fprintf(fp, "ColorButtonPosition = %s\n",      ImGuiDirToText(style.ColorButtonPosition));

    // Booleans
    fprintf(fp, "AntiAliasedLines = %s\n",      style.AntiAliasedLines == true ? "true" : "false");
    fprintf(fp, "AntiAliasedLinesUseTex = %s\n", style.AntiAliasedLinesUseTex == true ? "true" : "false");
    fprintf(fp, "AntiAliasedFill = %s\n",        style.AntiAliasedFill == true ? "true" : "false");

    // ImVec2s
	fprintf(fp, "WindowPadding = %f,%f\n",          style.WindowPadding.x, style.WindowPadding.y);
	fprintf(fp, "WindowMinSize = %f,%f\n",          style.WindowMinSize.x, style.WindowMinSize.y);
	fprintf(fp, "WindowTitleAlign = %f,%f\n",       style.WindowTitleAlign.x, style.WindowTitleAlign.y);
	fprintf(fp, "FramePadding = %f,%f\n",           style.FramePadding.x, style.FramePadding.y);
	fprintf(fp, "ItemSpacing = %f,%f\n",            style.ItemSpacing.x, style.ItemSpacing.y);
	fprintf(fp, "ItemInnerSpacing = %f,%f\n",       style.ItemInnerSpacing.x, style.ItemInnerSpacing.y);
	fprintf(fp, "CellPadding = %f,%f\n",            style.CellPadding.x, style.CellPadding.y);
	fprintf(fp, "TouchExtraPadding = %f,%f\n",      style.TouchExtraPadding.x, style.TouchExtraPadding.y);
	fprintf(fp, "ButtonTextAlign = %f,%f\n",        style.ButtonTextAlign.x, style.ButtonTextAlign.y);
	fprintf(fp, "SelectableTextAlign = %f,%f\n",    style.SelectableTextAlign.x, style.SelectableTextAlign.y);
	fprintf(fp, "DisplayWindowPadding = %f,%f\n",   style.DisplayWindowPadding.x, style.DisplayWindowPadding.y);
	fprintf(fp, "DisplaySafeAreaPadding = %f,%f\n", style.DisplaySafeAreaPadding.x, style.DisplaySafeAreaPadding.y);

	fclose(fp);
	fp = NULL;
}

