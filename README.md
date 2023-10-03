# Simulator project for LVGL embedded GUI Library

The [LVGL](https://github.com/lvgl/lvgl) is written mainly for microcontrollers and embedded systems however you can run the library **on your PC** as well without any embedded hardware. The code written on PC can be simply copied when your are using an embedded system.

Using a PC simulator instead of an embedded hardware has several advantages:
* **Costs $0** because you don't have to buy or design PCB
* **Fast** because you don't have to design and manufacture PCB
* **Collaborative** because any number of developers can work in the same environment
* **Developer friendly** because much easier and faster to debug on PC

## Requirements
This project is configured for VSCode and only tested on Linux, although this may work on OSx or WSL. It requires a working version of GCC, GDB and make in your path.

To allow debugging inside VSCode you will also require a GDB [extension](https://marketplace.visualstudio.com/items?itemName=webfreak.debug) or other suitable debugger.

* **SDL** a low level driver library to use graphics, handle mouse, keyboard etc.

## Usage

### Get the PC project

Clone the PC project and the related sub modules:

```bash
git clone --recursive https://github.com/JoshuaWierenga/lv_port_pc_make
```

### Install SDL
You can download SDL from https://www.libsdl.org/

On Linux you can install it via terminal:
```bash
sudo apt-get update && sudo apt-get install -y build-essential libsdl2-dev
```

On windows with msys2 you can install it via terminal:
```
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

### Build
On Linux use the default make target. Select "g++ build and debug active file" from the VS Code "RUN AND DEBUG" drop down, or via the command line:
```
make
```

On Windows install Cygwin from https://www.cygwin.com. Select the appropriate compiler and debugger during installation (x86_64-w64-mingw32-gcc, gdb). Add the Cygwin binaries directory path ( C:\cygwin64\bin for example ) to the "Path" "System Environment Variable" via Windows Settings. Use the win64 target to build. Select "win64 build and debug active file" from the VS Code "RUN AND DEBUG" drop down, or via the command line:
```
make win64
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
INC 				:= -I./ui/simulator/inc/ -I./ -I./lvgl/ -I/usr/include/freetype2 -L/usr/local/lib
LDLIBS	 			:= -lSDL2 -lm -lfreetype -lavformat -lavcodec -lavutil -lswscale -lm -lz -lpthread
```

### Setup
To allow custom UI code an `lv_conf.h` file placed at `ui/simulator/inc` will automatically override this projects lv_conf.h file. By default code under `ui` is ignored so you can reuse this repository for multiple projects. You will need to place a call from `main.c` to your UI's entry function.

To build and debug, press F5. You should now have your UI displayed in a new window and can access all the debug features of VSCode through GDB.

To allow temporary modification between simulator and device code, a SIMULATOR=1 define is added globally.
