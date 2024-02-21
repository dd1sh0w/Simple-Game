cmake_minimum_required(VERSION 3.27)
project(Gravitation)

set(CMAKE_CXX_STANDARD 20)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
add_executable(Gravitation main.cpp
        classes/Game.cpp
        classes/Game.h
        classes/Player.cpp
        classes/Player.h
        classes/SwagBall.cpp
        classes/SwagBall.h
)
target_link_libraries(Gravitation PRIVATE sfml-graphics)
target_compile_features(Gravitation PRIVATE cxx_std_17)


if(WIN32)
    add_custom_command(
            TARGET Gravitation
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Gravitation>
            VERBATIM)
endif()

install(TARGETS Gravitation)

