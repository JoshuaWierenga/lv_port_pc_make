# Simulator project for LVGL embedded GUI Library

The [LVGL](https://github.com/lvgl/lvgl) is written mainly for microcontrollers and embedded systems however you can run the library **on your PC** as well without any embedded hardware. The code written on PC can be simply copied when your are using an embedded system.

Using a PC simulator instead of an embedded hardware has several advantages:
* **Costs $0** because you don't have to buy or design PCB
* **Fast** because you don't have to design and manufacture PCB
* **Collaborative** because any number of developers can work in the same environment
* **Developer friendly** because much easier and faster to debug on PC

## Requirements
This project is configured for Make and has been tested on MSYS2, Linux and WSL, although it may work on BSDs, Cygwin and macOS among others. It requires a working version of GCC and Make in your path and optionally **SDL** or **X11** if support for oses other than Windows is desired.
Outdated but possibly still accurate Cygwin instructions exist for some steps.

The project can use **SDL**, the raw **Win32** API or **X11** as a LVGL display driver for lowlevel graphics/mouse/keyboard support. This can be selected using different make targets.
Please make sure the selected library is installed in the system (check [Install graphics driver](#install-graphics-driver)).

## Usage

### Get the PC project

Clone the PC project and the related sub modules:

```bash
git clone --recursive https://github.com/JoshuaWierenga/lv_port_pc_make
```

### Install graphics driver
The project can use **SDL**, the raw **Win32** API or **X11** as a LVGL display driver.
Please make sure the selected library is installed in the system:

#### Install SDL
You can download **SDL** from https://www.libsdl.org/ if none of the following cases cover your setup.

On Linux you can normally install it via a terminal. Below is a example for Debian based distros:
```bash
sudo apt-get update && sudo apt-get install -y libsdl2-dev
```

On Windows with MSYS2 you can install it via a terminal:
```bash
pacman -S mingw-w64-x86_64-SDL2
```
Then copy "/mingw64/bin/SDL2.dll" to either your "Windows\System32" directory or to "build\bin".
Alternatively just run the demo program from within the terminal where SDL2.dll is already accessible.

Old Windows instructions(cygwin, msvc?):
On Windows copy "SDL2.dll" to your "Windows\System32" directory and the "ui\simulator\dlls" directory. Copy the SDL2 source code "include" directory to "ui\simulator\inc" name it "SDL2", the final paths look like this:
```
C:\Windows\System32\SDL2.dll
C:\(lv_sim_vscode_sdl source directory)\ui\simulator\dlls\SDL2.dll
C:\(lv_sim_vscode_sdl source directory)\ui\simulator\inc\SDL2\*.h
```

#### Install Win32
The **Win32** Windowing APIs are automatically available on windows and can be obtained on Linux via [Wine](https://www.winehq.org/) but such a setup is currently beyond the scope of this project.

#### Install X11
The **X11** Window System was the default on Linux via Xorg for many years but is currently
being displaced by Wayland which is not currently supported however X11 applications should run
via XWayland but this is not something I have any experience with(does it ship with Wayland?).
Ideally this means that either Xorg or XWayland would be installed on all major distros and so
the only thing required are the headers for your distro which can normally be obtained via a
terminal. Below is a example for Debian based distros:
```bash
sudo apt-get update && sudo apt-get install -y libx11-dev
```

### Build
On Linux or Windows with WSL use the unixsdl or unixx11 make targets.
```bash
make unixsdl
```

On Windows with MSYS2 or WSL use the smallwin64drv, win64drv and win64sdl make targets:
```bash
make win64drv
```
Make sure to run clean before using a different target as the make targets currently don't check if any files were built for a different target before reusing them.
```bash
make clean
```

Old Windows instructions:
On Windows install Cygwin from https://www.cygwin.com. Select the appropriate compiler during installation (x86_64-w64-mingw32-gcc). Add the Cygwin binaries directory path ( C:\cygwin64\bin for example ) to the "Path" "System Environment Variable" via Windows Settings. Use the win64sdl target to build via the command line:
```
make win64sdl
```

### Optional library
There are also FreeType and FFmpeg support. You can install FreeType support with:
```bash
# FreeType support
wget https://kumisystems.dl.sourceforge.net/project/freetype/freetype2/2.13.2/freetype-2.13.2.tar.xz
tar -xf freetype-2.13.2.tar.xz
cd freetype-2.13.2
make
make install
```

The FFmpeg support can be installed with:
```bash
# FFmpeg support
git clone https://git.ffmpeg.org/ffmpeg.git ffmpeg
cd ffmpeg
git checkout release/6.0
./configure --disable-all --disable-autodetect --disable-podpages --disable-asm --enable-avcodec --enable-avformat --enable-decoders --enable-encoders --enable-demuxers --enable-parsers --enable-protocol='file' --enable-swscale --enable-zlib
make
sudo make install
```

And then remove all the comments in the `Makefile` on `INC` and `LDLIBS` lines. They should be:
```Makefile
INC    += -I./ui/simulator/inc -I. -I./lvgl -I/usr/include/freetype2 -L/usr/local/lib
LDLIBS := -lfreetype -lavformat -lavcodec -lavutil -lswscale -lz -lpthread
```

### Setup
To allow custom UI code an `lv_conf.h` file placed at `ui/simulator/inc` will automatically override this projects lv_conf.h file. By default code under `ui` is ignored so you can reuse this repository for multiple projects. You will need to place a call from `main.c` to your UI's entry function.

To allow temporary modification between simulator and device code, a SIMULATOR=1 define is added globally.
