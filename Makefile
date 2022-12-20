CXX:=g++
CXX_STD:=c++11
CFLAGS:=
CCFLAGS+=-Isrc/ -Iimgui-1.89.1/ -Wall -MMD -MP -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1
LFLAGS:=

SRCS_CPP:=$(wildcard demo/*.cpp) $(wildcard imgui-1.89.1/*.cpp) $(wildcard src/*.cpp)
OBJS_CPP:=$(SRCS_CPP:.cpp=.o)
DEPENDS:=$(patsubst %.cpp,%.d,$(SRCS_CPP))
bin:=imgooeystyles_demo

ifeq ($(Stable),0)
	CCFLAGS+=-O0 -g
else
	CCFLAGS+=-O2
endif

ifeq ($(OS),Windows_NT)
	LFLAGS+=$(addprefix -l,glfw3 mingw32 opengl32 comdlg32 imagehlp dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid setupapi)
	LFLAGS+=-mwindows --static
	bin=imgooeystyles_demo.exe
else
	UNAME_S:=$(shell uname -s)
	_libs:=glfw GL m

	ifeq ($(UNAME_S),Linux)
		_libs+=dl
		# On POSX Use Address Sanitizers in Debug Mode
		ifeq ($(CXX),g++)
			ifeq ($(Stable),0)
				CCFLAGS+=-fsanitize=address -fsanitize=undefined
				LFLAGS+=-fsanitize=address -fsanitize=undefined -lasan -lubsan
			endif
		endif
	endif
	ifeq ($(UNAME_S),Darwin)
		LFLAGS+=$(addprefix -framework , OpenGL Cocoa)
	endif

	LFLAGS+=$(addprefix -l,$(_libs))
endif

# make all
all: $(bin)

-include $(DEPENDS)

%.o: %.cpp
	$(CXX) --std=$(CXX_STD) $(CXXFLAGS) $(CCFLAGS) -c $< -o $@

$(bin): $(OBJS_CPP)
	$(CXX) --std=$(CXX_STD) $(OBJS_CPP) $(LFLAGS) -o $@

.PHONY: run
.PHONY: clean

# make run
run: $(all)
	./$(bin)

# make clean
clean:
	$(RM) $(bin) $(OBJS_CPP) $(DEPENDS)
