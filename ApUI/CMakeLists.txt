set(EXE_NAME ApUI)

file(GLOB_RECURSE APUI_FILES "*.h" "*.hpp" "*.cpp")

add_library(${EXE_NAME} STATIC ${APUI_FILES})
target_link_libraries(${EXE_NAME} PUBLIC ${AP_LIBRARIES})

target_include_directories(${EXE_NAME} PUBLIC ../)
target_include_directories(${EXE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
