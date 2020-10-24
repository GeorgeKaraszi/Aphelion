cmake_minimum_required(VERSION 3.17)
set(EXE_NAME Aphelion)
project(${EXE_NAME})

set(CMAKE_CXX_STANDARD 20)

include(CMakePackageConfigHelpers)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_MODE=1)
else()
    add_definitions(-DDEBUG_MODE=0)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VCPKG_TARGET_ARCHITECTURE x64)
    add_definitions(-DENVIRONMENT64)
else()
    set(VCPKG_TARGET_ARCHITECTURE x86)
    add_definitions(-DENVIRONMENT32)
endif()

add_definitions(-D_WIN32_WINNT=0x0602)

find_library(DirectX_D3D11_LIBRARY d3d11)
find_library(DirectXTK directxtk)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost COMPONENTS REQUIRED date_time system coroutine regex)
find_package(OpenSSL REQUIRED)
add_compile_options(/bigobj)

add_subdirectory(ApTools)
add_subdirectory(ApWindow)
add_subdirectory(ApUI)
#add_subdirectory(ApCore)
add_subdirectory(ApGame)

file(GLOB MAIN_FILES "*.h" "*.hpp" "*.cpp" "*.rc")

add_executable(${EXE_NAME} WIN32 ${MAIN_FILES})
target_link_libraries(
        ${EXE_NAME}
        ApTools
        ApWindow
        ApUI
        ApGame
        nlohmann_json::nlohmann_json
        ${DirectX_D3D11_LIBRARY}
        ${DirectXTK}
        ${Boost_LIBRARIES}
        ${OPENSSL_CRYPTO_LIBRARY}
        ${OPENSSL_LIBRARIES}
)