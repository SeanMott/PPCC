# Power PC (Game Cube) To C++
A WIP GameCube Power PC to C++ static transcompiler.

Started as a project for renaming DTK output, turned into a attempt at turning DTK outputed assembly to C++.

There are two programs `PPCC - Power PC C++ Compiler` and `Struct Rename`

# PPCC

Power PC C++ Compiler is the namespake of the project. It takes DTK outputed assembly and converts it to C++. Each ASM file becomes a header and source C++ file. Each instruction is replaced with a C++ "macro" function that handles the implementation of the instruction.

# Struct Renaming

Struct renaming handles the process of sifting through the ASM and symbol file. Then from there renaming objects in the ASM based on their varibles inside.

### Naming Scheme

All `lbl_` objects get found and have a name generated for them and the count appended to the end.

If a object contains only .floats(s) the object will be renamed `LBL_STRUCT_FLOAT_XXX`.

If a object contains only .skip(s) the object will be renamed `LBL_STRUCT_SPACE_RESERVE_SKIP_XXX`.

If a object contains only .double(s) the object will be renamed `LBL_STRUCT_DOUBLE_XXX`.

If a object contains only .byte(s) the object will be renamed `LBL_STRUCT_BYTE_XXX`.

If a object contains only .byte4(s) the object will be renamed `LBL_STRUCT_BYTE4_XXX`.

The fallback incase a object has a mix of types or can't be deducated. The struct will be called `LBL_STRUCT_XXX`.

## PPCC Useage

In order to run PCASMToCpp.exe, it requires a few file paths.

```
-asm <path> || the directory path to the folder containing your decompiled assembly. Normally found in the build folder after DTK does it's thing.

-cout <path> || The directory where C++ code will be outputted to

```

## Struct Renaming Useage

In order to run StructRename.exe, it requires a few file paths.

```
-asm <path> || the directory path to the folder containing your decompiled assembly. Normally found in the build folder after DTK does it's thing.

-symbolFile <path> || The full path to the symbols.txt file where DTK outputs it's symbols.

```

Struct Rename will run and spit out in the console what objects it is renaming.

## Credits

- Jinxy <br>
Handled the macro function implementation and provided details on how some datatypes match to C++

- Jas <br>
Handled the compiler that lexes DTK and outputs C++ macro functions.

## How the Transcompiler works?

For the sake of a clean README it has been moved to their own READMEs.

- [PPCC Stages](README_DOCS/PPPCDetails.md)
- [Struct Renamer]()
- [PPCC AST Trees and Passes]()

## How to build?

If you want a compiled binary head to [Releases](https://github.com/SeanMott/PPCC/releases). If you actually want to build it, you're in the right place.

### Any Platform

PPCC depends on the [Bytes The Dust Standard Library](). This is a library of C++ code used in BTD projects. A python installer script will run you through set up.

[Python]() is required for build set up and DTK, but PPCC itself doesn't need it.

### Windows

In the `PythonScripts` folder run `PPCCProjectSetup.py`, the installer will walk you through getting BTDSTD if needed and update the Premake script to work on your system.

Afterwards run `GenProjects.bat` and then just open and build the visual studio project.

### Mac

### Linux