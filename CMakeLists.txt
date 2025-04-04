cmake_minimum_required(VERSION 3.18)

project(CameraChessCalibration
        LANGUAGES CXX
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(ThirdParty)

# ---------------------------- #
#   Camera chess calibration   #
# ---------------------------- #
add_executable(CameraChessCalibration)

file(GLOB_RECURSE Sources Src/*)

target_include_directories(CameraChessCalibration
        PRIVATE Include)

target_sources(CameraChessCalibration
        PRIVATE
        ${Sources}
        main.cpp)

target_link_libraries(CameraChessCalibration
        PRIVATE
        Wor::OpenCV
        Wor::ImGui
        Wor::Wrappers)

target_compile_definitions(CameraChessCalibration
        PRIVATE SDL_MAIN_USE_CALLBACKS)
