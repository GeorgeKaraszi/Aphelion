set(EXE_NAME ApGame)

file(GLOB_RECURSE APGAME_FILES "*.h" "*.hpp" "*.cpp")

add_library(${EXE_NAME} STATIC ${APGAME_FILES})
target_include_directories(${EXE_NAME} PUBLIC ../)
target_include_directories(${EXE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
