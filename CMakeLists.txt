cmake_minimum_required(VERSION 3.17)
set(EXE_NAME Aphelion)
project(${EXE_NAME})

set(CMAKE_CXX_STANDARD 20)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
add_definitions(-D_WIN32_WINNT=0x0602)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_MODE=1)
else()
    add_definitions(-DDEBUG_MODE=0)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_definitions(-DENVIRONMENT64)
else()
    add_definitions(-DENVIRONMENT32)
endif()

find_library(DirectX_D3D11_LIBRARY d3d11)
add_compile_options(/bigobj)

add_subdirectory(ApTools)
add_subdirectory(ApWindow)
add_subdirectory(ApUI)
add_subdirectory(ApCore)
add_subdirectory(ApGame)

file(GLOB MAIN_FILES "*.h" "*.hpp" "*.cpp" "*.rc")
add_executable(${EXE_NAME} WIN32 ${MAIN_FILES})

target_link_libraries(
        ${EXE_NAME}
        ApWindow
        ApUI
        ApGame
        ApCore
        ${DirectX_D3D11_LIBRARY}
        ${CONAN_LIBS}
)