# Text Editor
A simple text editor (name T.B.D.) being created with sole purpose to understand the working of raylib, C and text editors.

## Download 
Downlaod the [executable](https://github.com/Ajesh2/textEditor/releases)

## Functions
ctrl + n :   New Tab<br/>ctrl + tab : Change Tab<br/>ctrl + del : Delete Tab<br/>esc : Exit the program

## Compile
(Do if you don't want to download [.exe](https://github.com/AjeshCasual/Text-Editor/releases) directly)
#### Download Compiler
1.Download latest [w64devkit](https://github.com/skeeto/w64devkit/releases) according to you PC requirements and extract.<br/>
2.Locate the bin folder in the extracted zip and remember the name.<br/>
3.Add `path/to/your/bin` to the environment variable PATH like `C:/w64devkit/bin`.<br/>

To compile textEditor use 
```
cc -o main.exe main.c -std=c99 -Wall -Iexternal -DPLATFORM_DESKTOP -lmsvcrt -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -lshell32 -luser32 -I include -L lib
```
