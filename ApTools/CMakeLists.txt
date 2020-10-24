set(EXE_NAME ApTools)

file(GLOB_RECURSE APTOOL_FILES "*.h" "*.hpp" "*.ipp" "*.cpp")

add_library(${EXE_NAME} STATIC ${APTOOL_FILES})
set_target_properties(${EXE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

#target_include_directories(${EXE_NAME} PUBLIC ../)
target_include_directories(${EXE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})