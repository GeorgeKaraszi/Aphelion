cmake_minimum_required(VERSION 3.28)

set(VCPKG_LIBRARY_LINKAGE           static)
set(VCPKG_TARGET_TRIPLET            x64-windows-static)
set(Boost_USE_STATIC_LIBS           ON)
set(Boost_USE_MULTITHREADED         ON)
set(Boost_USE_STATIC_RUNTIME        ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MSVC_RUNTIME_LIBRARY      "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(EXE_NAME                        Aphelion)

project(${EXE_NAME})

add_definitions(-D_WIN32_WINNT=0x0602)
add_definitions(-DUNICODE)

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

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})


find_library(DirectX_D3D11_LIBRARY d3d11)
add_compile_options(/bigobj)

include_directories(Resources)

include(cmake/CorePackages.cmake)
FindCoreSystemPackages()

add_subdirectory_and_link_libs(ApTools)
add_subdirectory_and_link_libs(ApWindow)
add_subdirectory_and_link_libs(ApUI)
add_subdirectory_and_link_libs(ApCore)
add_subdirectory_and_link_libs(ApGame)
add_subdirectory_and_link_libs(ApData)

file(GLOB MAIN_FILES "*.h" "*.hpp" "*.cpp" "Resources/*.rc")
add_executable(${EXE_NAME} WIN32 ${MAIN_FILES})

target_link_libraries(
    ${EXE_NAME}
    ApWindow
    ApUI
    ApGame
    ApCore
    ApData
    ${DirectX_D3D11_LIBRARY}
    ${AP_LIBRARIES}
)

set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS "/ignore:4099")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/api_key.txt DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Roboto-Medium.ttf DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
