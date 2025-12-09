# VS Code C++ & CMake Setup Guide

This guide will help you set up Visual Studio Code for C++ development with CMake, specifically for this project.

## 1. Install Required Extensions
Open VS Code and install the following extensions (Ctrl+Shift+X):
1.  **C/C++** (by Microsoft) - IntelliSense, debugging, and code browsing.
2.  **CMake** (by twxs) - CMake language support.
3.  **CMake Tools** (by Microsoft) - Extended CMake support.

## 2. Install Build Tools
### Windows
You need a C++ compiler. The easiest way is to install **Visual Studio Community** (not just VS Code) or **MinGW**.
- **Option A: Visual Studio Build Tools (Recommended)**
    1.  Download "Build Tools for Visual Studio 2022".
    2.  Run the installer and select **"Desktop development with C++"**.
    3.  Ensure "MSVC ... C++ x64/x86 build tools" and "CMake tools for Windows" are checked.
    4.  Install.

- **Option B: MinGW (GCC)**
    1.  Install MSYS2.
    2.  Run `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make`.
    3.  Add the bin folder to your System PATH.
        -   Press **Windows Key**, type "env", and select **Edit the system environment variables**.
        -   Click **Environment Variables**.
        -   Under **System variables**, find **Path**, select it, and click **Edit**.
        -   Click **New** and paste the path to your MinGW bin folder (e.g., `C:\msys64\mingw64\bin`).
        -   Click **OK** on all windows.
        -   **Restart VS Code** for changes to take effect.

## 3. Configuring the Project in VS Code
1.  Open the `cpp-core` folder in VS Code (File > Open Folder...).
2.  You should see a prompt: "Configure project?". Click **Yes**.
3.  Select your kit (Compiler).
    - If you installed VS Build Tools, select **Visual Studio Community 2022 Release - amd64**.
    - If you installed MinGW, select **GCC**.

## 4. Building the Project
1.  Look at the bottom status bar in VS Code.
2.  Click **Build** (or press F7).
3.  CMake Tools will run `cmake build` for you.
4.  The output executable `sortgen.exe` will be in `build/` or `build/Debug/`.

## 5. Running & Debugging
1.  Open `main.cpp`.
2.  Set a breakpoint (click to the left of a line number).
3.  Press **F5** (Start Debugging).
4.  Select "C++ (Windows)" if asked.
5.  You may need to configure `launch.json` to pass arguments.
    - Go to Run and Debug sidebar.
    - Click "create a launch.json file".
    - Add `"args": ["--algorithm", "bubble", "--size", "10"]` to the configuration.

## 6. Common Issues
- **"CMake is not recognized"**: You need to install CMake and add it to your PATH. If you installed VS Build Tools, it should be there. Try restarting VS Code.
- **"cl is not recognized"**: This means the MSVC compiler is not in your terminal PATH. VS Code's CMake Tools handles this automatically, but if you run commands manually in the terminal, you need to use the "Developer Command Prompt for VS 2022".

## 7. Using the CLI manually
If you prefer the terminal:
1.  Open "Developer Command Prompt" (search in Start Menu).
2.  `cd` to your project directory.
3.  `mkdir build`
4.  `cd build`
5.  `cmake ..`
6.  `cmake --build .`
