cmake_minimum_required(VERSION 3.16)

project(TOWER_OF_ASH)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- SFML ----
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# ---- pliki źródłowe ----
add_executable(TOWER_OF_ASH
    src/main.cpp
    src/Gra.cpp
    include/menadzer_tekstur.h src/menadzer_tekstur.cpp
    include/gra.h
    include/animatedsprite.h src/animatedsprite.cpp
    include/levelmodule.h src/levelmodule.cpp
    include/gracz.h src/gracz.cpp
    include/enemy.h src/enemy.cpp
    include/pasek_boczny.h src/pasek_boczny.cpp
    include/leaderboard.h src/leaderboard.cpp
    include/przycisk.h src/przycisk.cpp
    include/przyciskstart.h src/przyciskstart.cpp
    include/pocisk.h src/pocisk.cpp
)

# ---- include ----
target_link_libraries(TOWER_OF_ASH PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

target_include_directories(TOWER_OF_ASH PRIVATE
    include
    ${SFML_INCLUDE_DIR}
)

# Kopiowanie DLLek na Windowsie (tylko jeśli linkujesz dynamicznie)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
