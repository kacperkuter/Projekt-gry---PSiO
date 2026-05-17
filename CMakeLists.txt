cmake_minimum_required(VERSION 3.16)

project(Projekt-gry---PSiO)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- SFML ----
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# ---- pliki źródłowe ----
add_executable(Projekt-gry---PSiO
    src/main.cpp
    .gitignore
)

# ---- include ----
target_include_directories(Projekt-gry---PSiO PRIVATE include)

# ---- linkowanie SFML ----
target_link_libraries(Projekt-gry---PSiO
    sfml-graphics
    sfml-window
    sfml-system
)