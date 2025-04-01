# ---------- #
#   OpenCV   #
# ---------- #
# Just for convenient linking
find_package(OpenCV GLOBAL REQUIRED)
add_library(Wor_OpenCV INTERFACE)
add_library(Wor::OpenCV ALIAS Wor_OpenCV)

target_link_libraries(Wor_OpenCV
        INTERFACE ${OpenCV_LIBS})

target_include_directories(Wor_OpenCV
        INTERFACE ${OpenCV_INCLUDE_DIRS})

# -------- #
#   SDL3   #
# -------- #
find_package(SDL3 REQUIRED CONFIG
        REQUIRED COMPONENTS SDL3)

# --------- #
#   ImGui   #
# --------- #
# Just for convenient linking
add_library(ImGui)
add_library(Wor::ImGui ALIAS ImGui)

target_include_directories(ImGui
        PUBLIC
        ImGui
        ImGui/backends)

target_sources(ImGui
        PRIVATE
        ImGui/imgui.cpp
        ImGui/imgui_demo.cpp
        ImGui/imgui_draw.cpp
        ImGui/imgui_tables.cpp
        ImGui/imgui_widgets.cpp
        ImGui/backends/imgui_impl_sdl3.cpp
        ImGui/backends/imgui_impl_sdlrenderer3.cpp)

target_link_libraries(ImGui
        PUBLIC SDL3::SDL3)
