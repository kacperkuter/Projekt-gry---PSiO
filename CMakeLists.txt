cmake_minimum_required(VERSION 3.16)

project(Projekt-gry---PSiO)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# ---- SFML ----
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# ---- pliki źródłowe ----
add_executable(Projekt-gry---PSiO
    src/main.cpp
    src/Gra.cpp
    include/menadzer_tekstur.h src/menadzer_tekstur.cpp
    include/gra.h src/gra.cpp

)

# ---- include ----
target_link_libraries(Projekt-gry---PSiO PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
target_include_directories(Projekt-gry---PSiO PRIVATE
    C:/SFML-2.6.2/include
)

# 5. Opcjonalne: Kopiowanie DLLek na Windowsie (tylko jeśli linkujesz dynamicznie)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
