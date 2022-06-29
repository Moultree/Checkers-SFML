# Checkers
- Checkers project which was using to understand some OOP principles.
- Using SFML lib.
# How to install SFML:

- Download SFML https://www.sfml-dev.org/ (Windows) or install (Mac OS) 'brew install sfml'
- Compile it
- Change path to your path in "main.cpp"
- Compiling (Mac OS):

  g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_1/include -o output_filename -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -std=c++20
- Compiling (Windows):

  g++ -c main.cpp -o output_filename.o -I"install_SFML_PATH\include" -DSFML_STATIC
g++ output_filename.o -o output_filename -L"sfml-install-path\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s

# Preview of game
![Preview](https://user-images.githubusercontent.com/86831845/176343926-f181b8cf-6b69-47e4-b8b2-48c0f0ee77ba.png)

