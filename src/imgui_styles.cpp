#include <stdio.h>
#include <stdlib.h>

#include "imgui_styles.h"
#include "ini.h"

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

static int ImGuiTextToDir(const char* direction) {
	if (direction == NULL) return -1;
	if (strncmp(direction, "None", 4) == 0)       return ImGuiDir_None;
	else if (strncmp(direction, "Left", 4) == 0)  return ImGuiDir_Left;
	else if (strncmp(direction, "Right", 5) == 0) return ImGuiDir_Right;
	else if (strncmp(direction, "Up", 2) == 0)    return ImGuiDir_Up;
	else if (strncmp(direction, "Down", 4) == 0)  return ImGuiDir_Down;
	else return -1;
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


IMGUI_API void ImGui::LoadStyleFrom(const char* fileName) {
	ini_t* ini_style = ini_load(fileName);
	ImGuiStyle& style = ImGui::GetStyle();

	// Floats
	const char* Alpha_Str  = ini_get(ini_style, "ImGuiStyles", "Alpha");
	style.Alpha = Alpha_Str != NULL ? atof(Alpha_Str) : style.Alpha;

	const char* DisabledAlpha_Str  = ini_get(ini_style, "ImGuiStyles", "DisabledAlpha");
	style.DisabledAlpha = DisabledAlpha_Str != NULL ? atof(DisabledAlpha_Str) : style.DisabledAlpha;

	const char* WindowRounding_Str  = ini_get(ini_style, "ImGuiStyles", "WindowRounding");
	style.WindowRounding = WindowRounding_Str != NULL ? atof(WindowRounding_Str) : style.WindowRounding;

	const char* WindowBorderSize_Str  = ini_get(ini_style, "ImGuiStyles", "WindowBorderSize");
	style.WindowBorderSize = WindowBorderSize_Str != NULL ? atof(WindowBorderSize_Str) : style.WindowBorderSize;

	const char* ChildRounding_Str  = ini_get(ini_style, "ImGuiStyles", "ChildRounding");
	style.ChildRounding = ChildRounding_Str != NULL ? atof(ChildRounding_Str) : style.ChildRounding;

	const char* ChildBorderSize_Str  = ini_get(ini_style, "ImGuiStyles", "ChildBorderSize");
	style.ChildBorderSize = ChildBorderSize_Str != NULL ? atof(ChildBorderSize_Str) : style.ChildBorderSize;

	const char* PopupRounding_Str  = ini_get(ini_style, "ImGuiStyles", "PopupRounding");
	style.PopupRounding = PopupRounding_Str != NULL ? atof(PopupRounding_Str) : style.PopupRounding;

	const char* PopupBorderSize_Str  = ini_get(ini_style, "ImGuiStyles", "PopupBorderSize");
	style.PopupBorderSize = PopupBorderSize_Str != NULL ? atof(PopupBorderSize_Str) : style.PopupBorderSize;

	const char* FrameRounding_Str  = ini_get(ini_style, "ImGuiStyles", "FrameRounding");
	style.FrameRounding = FrameRounding_Str != NULL ? atof(FrameRounding_Str) : style.FrameRounding;

	const char* FrameBorderSize_Str  = ini_get(ini_style, "ImGuiStyles", "FrameBorderSize");
	style.FrameBorderSize = FrameBorderSize_Str != NULL ? atof(FrameBorderSize_Str) : style.FrameBorderSize;

	const char* IndentSpacing_Str  = ini_get(ini_style, "ImGuiStyles", "IndentSpacing");
	style.IndentSpacing = IndentSpacing_Str != NULL ? atof(IndentSpacing_Str) : style.IndentSpacing;

	const char* ColumnsMinSpacing_Str  = ini_get(ini_style, "ImGuiStyles", "ColumnsMinSpacing");
	style.ColumnsMinSpacing = ColumnsMinSpacing_Str != NULL ? atof(ColumnsMinSpacing_Str) : style.ColumnsMinSpacing;

	const char* ScrollbarSize_Str  = ini_get(ini_style, "ImGuiStyles", "ScrollbarSize");
	style.ScrollbarSize = ScrollbarSize_Str != NULL ? atof(ScrollbarSize_Str) : style.ScrollbarSize;

	const char* ScrollbarRounding_Str  = ini_get(ini_style, "ImGuiStyles", "ScrollbarRounding");
	style.ScrollbarRounding = ScrollbarRounding_Str != NULL ? atof(ScrollbarRounding_Str) : style.ScrollbarRounding;

	const char* GrabMinSize_Str  = ini_get(ini_style, "ImGuiStyles", "GrabMinSize");
	style.GrabMinSize = GrabMinSize_Str != NULL ? atof(GrabMinSize_Str) : style.GrabMinSize;

	const char* GrabRounding_Str  = ini_get(ini_style, "ImGuiStyles", "GrabRounding");
	style.GrabRounding = GrabRounding_Str != NULL ? atof(GrabRounding_Str) : style.GrabRounding;

	const char* LogSliderDeadzone_Str  = ini_get(ini_style, "ImGuiStyles", "LogSliderDeadzone");
	style.LogSliderDeadzone = LogSliderDeadzone_Str != NULL ? atof(LogSliderDeadzone_Str) : style.LogSliderDeadzone;

	const char* TabRounding_Str  = ini_get(ini_style, "ImGuiStyles", "TabRounding");
	style.TabRounding = TabRounding_Str != NULL ? atof(TabRounding_Str) : style.TabRounding;

	const char* TabBorderSize_Str  = ini_get(ini_style, "ImGuiStyles", "TabBorderSize");
	style.TabBorderSize = TabBorderSize_Str != NULL ? atof(TabBorderSize_Str) : style.TabBorderSize;

	const char* TabMinWidthForCloseButton_Str  = ini_get(ini_style, "ImGuiStyles", "TabMinWidthForCloseButton");
	style.TabMinWidthForCloseButton = TabMinWidthForCloseButton_Str != NULL ? atof(TabMinWidthForCloseButton_Str) : style.TabMinWidthForCloseButton;

	const char* MouseCursorScale_Str  = ini_get(ini_style, "ImGuiStyles", "MouseCursorScale");
	style.MouseCursorScale = MouseCursorScale_Str != NULL ? atof(MouseCursorScale_Str) : style.MouseCursorScale;

	const char* CurveTessellationTol_Str  = ini_get(ini_style, "ImGuiStyles", "CurveTessellationTol");
	style.CurveTessellationTol = CurveTessellationTol_Str != NULL ? atof(CurveTessellationTol_Str) : style.CurveTessellationTol;

	const char* CircleTessellationMaxError_Str  = ini_get(ini_style, "ImGuiStyles", "CircleTessellationMaxError");
	style.CircleTessellationMaxError = CircleTessellationMaxError_Str != NULL ? atof(CircleTessellationMaxError_Str) : style.CircleTessellationMaxError;

	// Directions
	int WindowMenuButtonPosition_Int = ImGuiTextToDir(ini_get(ini_style, "ImGuiStyles", "WindowMenuButtonPosition"));
	if (WindowMenuButtonPosition_Int >= 0) style.WindowMenuButtonPosition = WindowMenuButtonPosition_Int;

	int ColorButtonPosition_Int = ImGuiTextToDir(ini_get(ini_style, "ImGuiStyles", "ColorButtonPosition"));
	if (ColorButtonPosition_Int >= 0) style.ColorButtonPosition = ColorButtonPosition_Int;

	// Booleans
	const char* AntiAliasedLines_Str = ini_get(ini_style, "ImGuiStyles", "AntiAliasedLines");
	if (AntiAliasedLines_Str != NULL) {
		if (strncmp(AntiAliasedLines_Str, "true", 4) == 0) style.AntiAliasedLines = true;
		else if (strncmp(AntiAliasedLines_Str, "false", 5) == 0) style.AntiAliasedLines = false;
	}

	const char* AntiAliasedLinesUseTex_Str = ini_get(ini_style, "ImGuiStyles", "AntiAliasedLinesUseTex");
	if (AntiAliasedLinesUseTex_Str != NULL) {
		if (strncmp(AntiAliasedLinesUseTex_Str, "true", 4) == 0) style.AntiAliasedLinesUseTex = true;
		else if (strncmp(AntiAliasedLinesUseTex_Str, "false", 5) == 0) style.AntiAliasedLinesUseTex = false;
	}

	const char* AntiAliasedFill_Str = ini_get(ini_style, "ImGuiStyles", "AntiAliasedFill");
	if (AntiAliasedFill_Str != NULL) {
		if (strncmp(AntiAliasedFill_Str, "true", 4) == 0) style.AntiAliasedFill = true;
		else if (strncmp(AntiAliasedFill_Str, "false", 5) == 0) style.AntiAliasedFill = false;
	}

	#define MAX_BEFORE_COMMA_SIZE 512
	char* CommaOffset = NULL;
	char BeforeComma[MAX_BEFORE_COMMA_SIZE] = "";

#define LOAD_IMVEC2s(var_imvec2, str) \
	CommaOffset = str == NULL ? NULL : strchr(str, ','); \
	if (CommaOffset != NULL && CommaOffset - str > 0) { \
		strncpy(BeforeComma, str, CommaOffset - str); \
		BeforeComma[(CommaOffset - str) + 1] = '\0'; \
		var_imvec2.x = atof(BeforeComma); \
		var_imvec2.y = atof(CommaOffset + 1); \
	} \
	BeforeComma[0] = '\0'; \
	CommaOffset = NULL

	// ImVec2s
	const char* WindowPadding_Str = ini_get(ini_style, "ImGuiStyles", "WindowPadding");
	LOAD_IMVEC2s(style.WindowPadding, WindowPadding_Str);

	const char* WindowMinSize_Str = ini_get(ini_style, "ImGuiStyles", "WindowMinSize");
	LOAD_IMVEC2s(style.WindowMinSize, WindowMinSize_Str);

	const char* WindowTitleAlign_Str = ini_get(ini_style, "ImGuiStyles", "WindowTitleAlign");
	LOAD_IMVEC2s(style.WindowTitleAlign, WindowTitleAlign_Str);

	const char* FramePadding_Str = ini_get(ini_style, "ImGuiStyles", "FramePadding");
	LOAD_IMVEC2s(style.FramePadding, FramePadding_Str);

	const char* ItemSpacing_Str = ini_get(ini_style, "ImGuiStyles", "ItemSpacing");
	LOAD_IMVEC2s(style.ItemSpacing, ItemSpacing_Str);

	const char* ItemInnerSpacing_Str = ini_get(ini_style, "ImGuiStyles", "ItemInnerSpacing");
	LOAD_IMVEC2s(style.ItemInnerSpacing, ItemInnerSpacing_Str);

	const char* CellPadding_Str = ini_get(ini_style, "ImGuiStyles", "CellPadding");
	LOAD_IMVEC2s(style.CellPadding, CellPadding_Str);

	const char* TouchExtraPadding_Str = ini_get(ini_style, "ImGuiStyles", "TouchExtraPadding");
	LOAD_IMVEC2s(style.TouchExtraPadding, TouchExtraPadding_Str);

	const char* ButtonTextAlign_Str = ini_get(ini_style, "ImGuiStyles", "ButtonTextAlign");
	LOAD_IMVEC2s(style.ButtonTextAlign, ButtonTextAlign_Str);

	const char* SelectableTextAlign_Str = ini_get(ini_style, "ImGuiStyles", "SelectableTextAlign");
	LOAD_IMVEC2s(style.SelectableTextAlign, SelectableTextAlign_Str);

	const char* DisplayWindowPadding_Str = ini_get(ini_style, "ImGuiStyles", "DisplayWindowPadding");
	LOAD_IMVEC2s(style.DisplayWindowPadding, DisplayWindowPadding_Str);

	const char* DisplaySafeAreaPadding_Str = ini_get(ini_style, "ImGuiStyles", "DisplaySafeAreaPadding");
	LOAD_IMVEC2s(style.DisplaySafeAreaPadding, DisplaySafeAreaPadding_Str);

	ini_free(ini_style);
	ini_style = NULL;
}

