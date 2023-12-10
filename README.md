# Checkers
- Checkers project which was using to understand some OOP principles, using SFML framework.
- Tested on Windows 10 and MacOS 11 (Big Sur) and MacOS 14 (Sonoma)

## Requirements:
- Download SFML 2.6.x latest.
- Download latest [CMake Installer](https://cmake.org/download/) for your OS
- Make sure you edit [CMakeLists.txt](CMakeLists.txt) file, line 14, change `CUSTOM_SFML_PATH` to your local path, where you installed SFML

### Windows :
- Visual Studio 2022 (select Complete Desktop C/C++ workload)
- Luckily, Visual Studio 2022 is bundled with CMake already
  
### MacOS
- Xcode latest with MacOS SDK.
- Extra Dev Build Tools. After Xcode installs, please run this in terminal:
  ```bash
  sudo xcode-select --install
  ```

## How to install SFML:
- Download SFML 2.6.x https://www.sfml-dev.org/download.php (Windows MSVC) or (Mac OS clang) **compiled binaries**.
- For Windows, chooose Visual C++ edition of SFML. (avoid MinGW or others, may cause issues!)
- For MacOS, please only keep "Frameworks" files for SFML, not "dylibs". For more details, see [official guide](https://www.sfml-dev.org/tutorials/2.6/start-osx.php#installing-sfml)
- For Windows, after downloading, simply move the SFML folder to a good location on disk, e.g `C:/SFML`
- Alternatively, you can download SFML Sources and build locally yourself.

## Building on Mac OS:

1. Open this project folder in Cmake GUI, and select build folder "out/"
2. Click **Configure** > choose "Xcode Generator" > click **Done**. Leave other settings as is.
3. Click **Generate**, after few seconds, Xcode Project will be ready. Click **Open Project in Xcode**.
4. After Xcode opens, click "Product" > "Edit Scheme" > select "Release". Click Save. Now click "Product" > "Build".
5. If you want to share your App with others, you need to _Copy SFML Frameworks_ into your APP Bundle during **Build Phase** (using XCode).

## Building on Windows:

1. Simply import this project folder in Visual Studio 2022.
2. Automatically CMake for Visual Studio will generate the project for you.
3. Select "Release" mode, then click "Build"

# Screenshot of the game
![Preview](https://user-images.githubusercontent.com/86831845/176343926-f181b8cf-6b69-47e4-b8b2-48c0f0ee77ba.png)

