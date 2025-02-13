Motorola ElfPack EM2 M*CORE SDK & Utils
=======================================

This package for Windows platform contains the following tools:

* M*CORE C/C++ GCC Compiler 3.4.6 for compiling source code.
* Elfs sources and build scripts.
* ElfLoader sources and build scripts.
* LibraryEditor, MidWay programs, some utilities by z3DD3r.
* SDK header files by theC0r3, flash.tato, z3DD3r, Chik_v, Andy51, tim_apple, Macho, G-XaD, om2804, kadukmm, fkcoder, EXL, and other developers from MotoFan.Ru forum.
* CMake build system module by EXL.

## Install

Unpack archive and copy all files to `C:\MCORE_EM2` directory, add it to `%PATH%` environment variable (optional).

## Install via Git Bash

```sh
cd /c/

git clone https://github.com/MotoFanRu/P2K-ELF-SDK-OLD.git --depth=1 -b master
git clone git@github.com:MotoFanRu/P2K-ELF-SDK-OLD.git --depth=1 -b master

cd P2K-ELF-SDK-OLD
mv ELFKIT_EM2_Windows /c/MCORE_EM2
```

## Usage SDK

Set proper paths to GCC compiler, libraries and SDK headers in `make.cmd`, `make.bat`, `build.cmd`, `compile.bat` and other build scripts.

```bat
C:\Project> make
C:\Project> build
C:\Project> compile
```

## Usage CMake and Ninja

```bat
C:\Project> cmake . -G Ninja -DELFPACK=EM2
C:\Project> ninja -v
```

## Authors

theC0r3, flash.tato, z3DD3r, Chik_v, Andy51, tim_apple, Macho, G-XaD, om2804, kadukmm, fkcoder, EXL, etc.

## Additional Information

* [SDK on z3DD3r's GitHub](https://github.com/z3DD3r/mcore-elf)
* [ELFs developing and porting](https://forum.motofan.ru/index.php?showforum=184)

© MotoFan.Ru, 2007-2023.
