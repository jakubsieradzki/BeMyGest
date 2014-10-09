file (GLOB SOURCE_FILE_LIST src/*.cpp)
file (GLOB HEADER_FILE_LIST include/*.h)

add_definitions(-D__OS_WINDOWS__)
add_library (stk STATIC ${SOURCE_FILE_LIST} ${HEADER_FILE_LIST})
target_include_directories (stk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
