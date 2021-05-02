cmake_minimum_required(VERSION 3.17)
set(EXE_NAME Aphelion)
project(${EXE_NAME})

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
add_definitions(-D_WIN32_WINNT=0x0602)
add_definitions(-DUNICODE)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_MODE=1)
    set(CONAN_PROFILE debug)
else()
    add_definitions(-DDEBUG_MODE=0)
    set(CONAN_PROFILE default)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_definitions(-DENVIRONMENT64)
else()
    add_definitions(-DENVIRONMENT32)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(
    REQUIRES boost/1.74.0
             openssl/1.1.1i
             nlohmann_json/3.9.1
             sqlitecpp/3.1.1
             fmt/7.1.3
    GENERATORS cmake
    OPTIONS boost:shared=False
            openssl:shared=False
            sqlitecpp:shared=False
            fmt:shared=False
    PROFILE_BUILD ${CONAN_PROFILE}
    OUTPUT_QUIET
)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conan-center
        SETTINGS ${settings}
        OUTPUT_QUIET
        )
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_library(DirectX_D3D11_LIBRARY d3d11)
add_compile_options(/bigobj)

include_directories(Resources)

add_subdirectory(ApTools)
add_subdirectory(ApWindow)
add_subdirectory(ApUI)
add_subdirectory(ApCore)
add_subdirectory(ApGame)
add_subdirectory(ApData)

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
    ${CONAN_LIBS}
)

set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS "/ignore:4099")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/api_key.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Roboto-Medium.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)