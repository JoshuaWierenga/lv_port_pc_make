#
# Makefile
# WARNING: relies on invocation setting current working directory to Makefile location
# This is done in .vscode/task.json
#
PROJECT   ?= lvgl-sdl
SRC_EXT   := c
OBJ_EXT   := o
ifeq ($(OS),Windows_NT)
MAKEFLAGS := -j $(NUMBER_OF_PROCESSORS)
else
MAKEFLAGS := -j $(shell nproc)
endif

WIN32DRVTARGETS := win64drv smallwin64drv
SDLTARGETS := unixsdl win64sdl

UNIXTARGETS := unixsdl
WIN64TARGETS := win64sdl win64drv smallwin64drv

$(UNIXTARGETS):  CC := gcc
ifeq ($(OS),Windows_NT)
$(WIN64TARGETS): CC := x86_64-w64-mingw32-gcc.exe
else
$(WIN64TARGETS): CC := x86_64-w64-mingw32-gcc
endif

SRC_DIR     := ./
WORKING_DIR := ./build
BUILD_DIR   := $(WORKING_DIR)/obj
BIN_DIR     := $(WORKING_DIR)/bin
UI_DIR      := ui

WARNINGS := -Wall -Wextra \
            -Wshadow -Wundef -Wmaybe-uninitialized -Wmissing-prototypes -Wno-discarded-qualifiers \
            -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized \
            -Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default  \
            -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated  \
            -Wempty-body -Wshift-negative-value -Wstack-usage=2048 \
            -Wtype-limits -Wsizeof-pointer-memaccess -Wpointer-arith

CFLAGS := -O0 -g $(WARNINGS)
$(WIN64TARGETS): BUILDCCFLAGS := -mwindows
win64sdl:        LDFLAGS := -L./ui/simulator/dlls
smallwin64drv:   LDFLAGS := -Wl,--gc-sections

# Add simulator define to allow modification of source
build:              DEFINES += -D SIMULATOR=1 -D LV_BUILD_TEST=0 -D LV_CONF_INCLUDE_SIMPLE=1 -D LV_USE_DEMO_WIDGETS=1
$(WIN64TARGETS):    DEFINES += -D __WIN64__ -D LV_PRId32=PRId32 -D LV_PRIu32=PRIu32
$(SDLTARGETS):      DEFINES += -D USE_SDL=1
# Setting WINVER to windows 7 as win32drv needs it for touch support
$(WIN32DRVTARGETS): DEFINES += -D USE_WIN32DRV=1 -D WINVER=_WIN32_WINNT_WIN7 -D _WIN32_WINNT=_WIN32_WINNT_WIN7

# Include simulator inc folder first so lv_conf.h from custom UI can be used instead
INC += -I./ui/simulator/inc -I. -I./lvgl
BIN := $(BIN_DIR)/demo
$(SDLTARGETS): LDLIBS := -lSDL2 -lm
ifneq ($(OS),Windows_NT)
INC += -I./winfix
endif

COMPILE = $(CC) $(CFLAGS) $(INC) $(DEFINES)

# Automatically include all source files
SRCS    := $(shell find $(SRC_DIR) -type f -name '*.c' -not -path '*/\.*')
OBJECTS := $(patsubst $(SRC_DIR)%,$(BUILD_DIR)/%,$(SRCS:.$(SRC_EXT)=.$(OBJ_EXT)))

$(BUILD_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	@echo 'Building project file: $<'
	@mkdir -p $(dir $@)
	@$(COMPILE) -c -o "$@" "$<"

build: $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN) $(OBJECTS) $(BUILDCCFLAGS) $(LDFLAGS) ${LDLIBS}

clean:
	rm -rf $(WORKING_DIR)

install: ${BIN}
	install -d ${DESTDIR}/usr/lib/${PROJECT}/bin
	install $< ${DESTDIR}/usr/lib/${PROJECT}/bin/

# TODO: Fix seg fault on linux with LV_USE_THEME_MONO enabled
# TODO: Fix keyboard support with win32drv hal
# TODO: Fix performance issues with win32drv hal(just animations?)
# TODO: Add x11 support, original repo without windows support had it so shouldn't be hard
# TODO: Update to a newer lvgl version

# Use these full target names to ensure build variables are set correctly
unixsdl win64sdl win64drv smallwin64drv: build

# Reduce output size
smallwin64drv:
	strip $(BIN).exe