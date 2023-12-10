# Checkers
- Checkers project which was using to understand some OOP principles.
- Using SFML lib.

## Requirements:
- Download SFML latest. 
- Make sure you edit [CMakeLists.txt](CMakeLists.txt) file, line 14, change CUSTOM_SFML_PATH to your local path, where you installed SFML

### Windows :
- Visual Studio 2022 (complete with c++ workload)
- Cmake 3.x latest (OPTIONAL, included in Visual Studio)

## MacOS
- Xcode latest.
- Cmake GUI (not included, IMPORTANT)

## How to install SFML:
- Download SFML 2.6.x https://www.sfml-dev.org/ (Windows) and (Mac OS as Frameworks libs) compiled binaries.
- Optionally, you can download SFML sources and build locally yourself.
- For MacOS, you can alternatively use `brew install sfml`. (Not recommended. It's best to use Frameworks, see official link above)

## Building on Mac OS:

1. Open this folder in Cmake GUI, and select build folder "out/"
2. Click **Configure** > choose Xcode Generator > click **Done**. Leave other settings as is.
3. Click **Generate**, after few seconds, Xcode Project will be ready. Click **Open Project in Xcode**.
4. After Xcode opens, click "Product" > "Edit Scheme" > select "Release". Click Save. Now click "Product" > "Build".
5. If you want to share your app with others, you may want to copy the SFML frameworks into your APP bundle during Build time. Also, have to Sign it using Apple Developer account. 

## Building on Windows:

1. Simply import this project folder in Visual Studio 2022.
2. Automatically Cmake will generate the project for you.
3. Click "Build"

# Screenshot of the game
![Preview](https://user-images.githubusercontent.com/86831845/176343926-f181b8cf-6b69-47e4-b8b2-48c0f0ee77ba.png)

