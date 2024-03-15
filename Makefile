#
# Makefile
#

# TODO: Fix make's "Argument list too long" error on msys2
# TODO: Fix seg fault on linux with LV_USE_THEME_MONO enabled
# TODO: Add x11 support on windows using nano-X?
# TODO: Support GTK?
# TODO: Support Wayland?
# TODO: Support fbdev? libinput? evdev?
# TODO: Support DRM/KMS? libinput? evdev?
# TODO: Support UEFI?
# TODO: Support Legacy BIOS? Use cosmo as boot loader to 64 bit?

PROJECT   ?= lvgl-demo
SRC_EXT   := c
OBJ_EXT   := o
ifeq ($(OS),Windows_NT)
MAKEFLAGS := -j $(NUMBER_OF_PROCESSORS)
else
MAKEFLAGS := -j $(shell nproc)
endif

SDLTARGETS := posixsdl win64sdl
WINNATIVETARGETS := smallwin64native win64native
X11TARGETS := posixx11

POSIXTARGETS := posixsdl posixx11
WIN64TARGETS := smallwin64native win64native win64sdl

# See CFLAGS comment for why this is needed
#$(POSIXTARGETS): CC := c99
$(POSIXTARGETS): CC := gcc
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

CFLAGS += -O0 -g $(WARNINGS)
# This shouldn't be required and won't work on all systems
# but currently the posix and stdio fs drivers use d_type
# without first checking for _DIRENT_HAVE_D_TYPE or at least
# _BSD_SOURCE
$(POSIXTARGETS):  CFLAGS += -std=gnu99
$(WIN64TARGETS):  BUILDCCFLAGS := -mwindows
smallwin64native: LDFLAGS := -Wl,--gc-sections
win64sdl:         LDFLAGS := -L./ui/simulator/dlls

# Add simulator define to allow modification of source
build:               DEFINES += -D SIMULATOR=1 -D LV_BUILD_TEST=0 -D LV_LVGL_H_INCLUDE_SIMPLE
$(POSIXTARGETS):     DEFINES += -D LV_USE_OS=LV_OS_PTHREAD
$(WIN64TARGETS):     DEFINES += -D LV_USE_OS=LV_OS_WINDOWS -D LV_PRId32=PRId32 -D LV_PRIu32=PRIu32
# TODO: Enable LV_USE_DRAW_SDL?
$(SDLTARGETS):       DEFINES += -D LV_USE_SDL
# Setting WINVER to windows 7 as the windows driver needs it for touch support
$(WINNATIVETARGETS): DEFINES += -D LV_USE_WINDOWS -D WINVER=_WIN32_WINNT_WIN7 -D _WIN32_WINNT=_WIN32_WINNT_WIN7
$(X11TARGETS):       DEFINES += -D LV_USE_X11

# Include simulator inc folder first so lv_conf.h from custom UI can be used instead
INC    += -I./ui/simulator/inc -I. -I./lvgl #-I/usr/include/freetype2 -L/usr/local/lib
LDLIBS += #-lfreetype -lavformat -lavcodec -lavutil -lswscale -lz -lpthread
BIN    := $(BIN_DIR)/demo
$(POSIXTARGETS): LDLIBS += -lpthread
$(SDLTARGETS):   LDLIBS += -lSDL2
$(X11TARGETS):   LDLIBS += -lX11
# On linux, Mingw-w64 cares about header case and only has windows.h while lv_windows.h expects Windows.h
ifneq ($(OS),Windows_NT)
INC += -I./winfix
endif

COMPILE = $(CC) $(CFLAGS) $(INC) $(DEFINES)

# Automatically include all source files
# Filter out broken test file, https://github.com/lvgl/lvgl/issues/5581
SRCS    := $(filter-out ./lvgl/tests/src/test_assets/test_img_emoji_F617.c,$(shell find $(SRC_DIR) -type f -name '*.c' -not -path '*/\.*'))
OBJECTS := $(patsubst $(SRC_DIR)%,$(BUILD_DIR)/%,$(SRCS:.$(SRC_EXT)=.$(OBJ_EXT)))

# Fix macro error which breaks x11 build, https://github.com/lvgl/lvgl/issues/5737
$(BUILD_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) lv_conf.h Makefile
	@echo 'Building project file: $<'
	@mkdir -p $(dir $@)
	@[ '$<' != 'lvgl/src/drivers/x11/lv_x11_input.c' ] || { sed 's/OBJ(indev, MY_CLASS/NULL(indev/' '$<' > '$<'.new && mv '$<'.new '$<'; }
	@$(COMPILE) -c -o "$@" "$<"

build: $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN) $(OBJECTS) $(BUILDCCFLAGS) $(LDFLAGS) ${LDLIBS}

clean:
	rm -rf $(WORKING_DIR)

install: ${BIN}
	install -d ${DESTDIR}/usr/lib/${PROJECT}/bin
	install $< ${DESTDIR}/usr/lib/${PROJECT}/bin/

# Use these full target names to ensure build variables are set correctly
posixsdl posixx11 smallwin64native win64native win64sdl: build

# Reduce output size
smallwin64native:
	strip $(BIN).exe