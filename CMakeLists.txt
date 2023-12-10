cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project("Checkers" VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
endif()

# Absolute path where you installed SFML
set(CUSTOM_SFML_HOME "/Library/Frameworks/SFML.framework/")
set(SFML_DIR ${CUSTOM_SFML_HOME}/lib/cmake/SFML)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h" "src/*.mm")
find_package(SFML REQUIRED COMPONENTS "graphics" "window" "system")

if(WIN32)
  add_executable(Checkers WIN32 ${SOURCES})
  target_link_libraries(Checkers PRIVATE sfml-main sfml-graphics sfml-window sfml-system)
elseif(APPLE)
  include(${CMAKE_SOURCE_DIR}/apple_cmake/MacBundle.cmake)
  find_library(FOUNDATION_FRAMEWORK Foundation)
  target_link_libraries(Checkers PRIVATE sfml-graphics sfml-window sfml-system
                          ${FOUNDATION_FRAMEWORK})
else()
  add_executable(Checkers ${SOURCES})
  target_link_libraries(Checkers PRIVATE sfml-graphics sfml-window sfml-system)
endif()

# include SFML headers
include_directories(${CUSTOM_SFML_HOME}/include) 

# show warnings (depending on C++ compiler)
if(MSVC)
  target_compile_options(Checkers PRIVATE /W4)
else()
  target_compile_options(Checkers PRIVATE -Wall)
endif()

# COPY resources folder to destination
if(WIN32)
  add_custom_command(
    TARGET Checkers
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources
            $<TARGET_FILE_DIR:Checkers>/resources)
endif()
