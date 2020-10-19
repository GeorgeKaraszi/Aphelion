set(EXE_NAME ApWindow)

file(GLOB_RECURSE APWIN_FILES "*.h" "*.hpp" "*.cpp")

add_library(${EXE_NAME} STATIC ${APWIN_FILES})

target_include_directories(${EXE_NAME} PUBLIC ../)
target_include_directories(${EXE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})