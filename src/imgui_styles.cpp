#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "imgui_styles.h"

#define INI_VERSION "0.1.1"
typedef struct ini_t ini_t;

ini_t*      ini_load(const char *filename);
ini_t*      ini_load_txt(const char *iniTxt);
void        ini_free(ini_t *ini);
const char* ini_get(ini_t *ini, const char *section, const char *key);
int         ini_sget(ini_t *ini, const char *section, const char *key, const char *scanfmt, void *dst);

/* Case insensitive string compare upto n */
static int strncmpci(const char* s1, const char* s2, size_t n) {
    while (n && *s1 && ( tolower(*s1) == tolower(*s2) )) {
        ++s1;
        ++s2;
        --n;
    }
    if ( n == 0 ) return 0;
    else return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
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

static int ImGuiTextToDir(const char* direction) {
	if (direction == NULL) return -1;
	if (strncmpci(direction, "None", 4) == 0)       return ImGuiDir_None;
	else if (strncmpci(direction, "Left", 4) == 0)  return ImGuiDir_Left;
	else if (strncmpci(direction, "Right", 5) == 0) return ImGuiDir_Right;
	else if (strncmpci(direction, "Up", 2) == 0)    return ImGuiDir_Up;
	else if (strncmpci(direction, "Down", 4) == 0)  return ImGuiDir_Down;
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
		if (strncmpci(AntiAliasedLines_Str, "true", 4) == 0) style.AntiAliasedLines = true;
		else if (strncmpci(AntiAliasedLines_Str, "false", 5) == 0) style.AntiAliasedLines = false;
	}

	const char* AntiAliasedLinesUseTex_Str = ini_get(ini_style, "ImGuiStyles", "AntiAliasedLinesUseTex");
	if (AntiAliasedLinesUseTex_Str != NULL) {
		if (strncmpci(AntiAliasedLinesUseTex_Str, "true", 4) == 0) style.AntiAliasedLinesUseTex = true;
		else if (strncmpci(AntiAliasedLinesUseTex_Str, "false", 5) == 0) style.AntiAliasedLinesUseTex = false;
	}

	const char* AntiAliasedFill_Str = ini_get(ini_style, "ImGuiStyles", "AntiAliasedFill");
	if (AntiAliasedFill_Str != NULL) {
		if (strncmpci(AntiAliasedFill_Str, "true", 4) == 0) style.AntiAliasedFill = true;
		else if (strncmpci(AntiAliasedFill_Str, "false", 5) == 0) style.AntiAliasedFill = false;
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

// All The Code From Here Is Modified Version Of https://github.com/rxi/ini
// It's Packed Into 1 File For "Ease" Of Use

/**
 * Copyright (c) 2016 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

struct ini_t {
  char *data;
  char *end;
};

/* Case insensitive string compare */
static int strcmpci(const char *a, const char *b) {
  for (;;) {
	int d = tolower(*a) - tolower(*b);
	if (d != 0 || !*a) {
	  return d;
	}
	a++, b++;
  }
}

/* Returns the next string in the split data */
static char* next(ini_t *ini, char *p) {
  p += strlen(p);
  while (p < ini->end && *p == '\0') {
	p++;
  }
  return p;
}

static void trim_back(ini_t *ini, char *p) {
  while (p >= ini->data && (*p == ' ' || *p == '\t' || *p == '\r')) {
	*p-- = '\0';
  }
}

static char* discard_line(ini_t *ini, char *p) {
  while (p < ini->end && *p != '\n') {
	*p++ = '\0';
  }
  return p;
}


static char *unescape_quoted_value(ini_t *ini, char *p) {
  /* Use `q` as write-head and `p` as read-head, `p` is always ahead of `q`
   * as escape sequences are always larger than their resultant data */
  char *q = p;
  p++;
  while (p < ini->end && *p != '"' && *p != '\r' && *p != '\n') {
	if (*p == '\\') {
	  /* Handle escaped char */
	  p++;
	  switch (*p) {
		default   : *q = *p;    break;
		case 'r'  : *q = '\r';  break;
		case 'n'  : *q = '\n';  break;
		case 't'  : *q = '\t';  break;
		case '\r' :
		case '\n' :
		case '\0' : goto end;
	  }

	} else {
	  /* Handle normal char */
	  *q = *p;
	}
	q++, p++;
  }
end:
  return q;
}


/* Splits data in place into strings containing section-headers, keys and
 * values using one or more '\0' as a delimiter. Unescapes quoted values */
static void split_data(ini_t *ini) {
  char *value_start, *line_start;
  char *p = ini->data;

  while (p < ini->end) {
	switch (*p) {
	  case '\r':
	  case '\n':
	  case '\t':
	  case ' ':
		*p = '\0';
		/* Fall through */

	  case '\0':
		p++;
		break;

	  case '[':
		p += strcspn(p, "]\n");
		*p = '\0';
		break;

	  case ';':
		p = discard_line(ini, p);
		break;

	  default:
		line_start = p;
		p += strcspn(p, "=\n");

		/* Is line missing a '='? */
		if (*p != '=') {
		  p = discard_line(ini, line_start);
		  break;
		}
		trim_back(ini, p - 1);

		/* Replace '=' and whitespace after it with '\0' */
		do {
		  *p++ = '\0';
		} while (*p == ' ' || *p == '\r' || *p == '\t');

		/* Is a value after '=' missing? */
		if (*p == '\n' || *p == '\0') {
		  p = discard_line(ini, line_start);
		  break;
		}

		if (*p == '"') {
		  /* Handle quoted string value */
		  value_start = p;
		  p = unescape_quoted_value(ini, p);

		  /* Was the string empty? */
		  if (p == value_start) {
			p = discard_line(ini, line_start);
			break;
		  }

		  /* Discard the rest of the line after the string value */
		  p = discard_line(ini, p);

		} else {
		  /* Handle normal value */
		  p += strcspn(p, "\n");
		  trim_back(ini, p - 1);
		}
		break;
	}
  }
}


ini_t* ini_load_txt(const char *iniTxt) {
  ini_t *ini = NULL;
  int len = 0;

  if (iniTxt == NULL) goto fail;
  len = strlen(iniTxt);

  /* Init ini struct */
  ini = (ini_t*)malloc(sizeof(ini_t));
  if (!ini) goto fail;
  memset(ini, 0, sizeof(*ini));

  /* Load file content into memory, null terminate, init end var */
  ini->data = (char*)malloc(len + 1);
  ini->data[len] = '\0';
  ini->end = ini->data + len;
  strncpy(ini->data, iniTxt, len);

  /* Prepare data */
  split_data(ini);

  return ini;

fail:
  if (ini) ini_free(ini);
  return NULL;
}

ini_t* ini_load(const char *filename) {
  ini_t *ini = NULL;
  FILE *fp = NULL;
  int n, sz;

  /* Init ini struct */
  ini = (ini_t*)malloc(sizeof(ini_t));
  if (!ini) {
	goto fail;
  }
  memset(ini, 0, sizeof(ini_t));

  /* Open file */
  fp = fopen(filename, "rb");
  if (!fp) {
	goto fail;
  }

  /* Get file size */
  fseek(fp, 0, SEEK_END);
  sz = ftell(fp);
  rewind(fp);

  /* Load file content into memory, null terminate, init end var */
  ini->data = (char*)malloc(sz + 1);
  ini->data[sz] = '\0';
  ini->end = ini->data  + sz;
  n = fread(ini->data, 1, sz, fp);
  if (n != sz) {
	goto fail;
  }

  /* Prepare data */
  split_data(ini);

  /* Clean up and return */
  fclose(fp);
  return ini;

fail:
  if (fp) fclose(fp);
  if (ini) ini_free(ini);
  return NULL;
}


void ini_free(ini_t *ini) {
  free(ini->data);
  free(ini);
}


const char* ini_get(ini_t *ini, const char *section, const char *key) {
  if (ini == NULL) {
	return NULL;
  }

  char *current_section = NULL;
  char *val;
  char *p = ini->data;

  if (*p == '\0') {
	p = next(ini, p);
  }

  while (p < ini->end) {
	if (*p == '[') {
	  /* Handle section */
	  current_section = p + 1;

	} else {
	  /* Handle key */
	  val = next(ini, p);
	  if (!section || !strcmpci(section, current_section)) {
		if (!strcmpci(p, key)) {
		  return val;
		}
	  }
	  p = val;
	}

	p = next(ini, p);
  }

  return NULL;
}


int ini_sget(
  ini_t *ini, const char *section, const char *key,
  const char *scanfmt, void *dst
) {
  const char *val = ini_get(ini, section, key);
  if (!val) {
	return 0;
  }
  if (scanfmt) {
	sscanf(val, scanfmt, dst);
  } else {
	*((const char**) dst) = val;
  }
  return 1;
}

