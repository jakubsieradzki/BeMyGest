file (GLOB SOURCE_FILE_LIST src/*.cpp)
file (GLOB HEADER_FILE_LIST include/*.h)

add_library (Common STATIC ${SOURCE_FILE_LIST} ${HEADER_FILE_LIST})
target_include_directories (Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (Common PUBLIC ${OPENNI_INC})

target_link_libraries(Common PUBLIC ${OPENNI_LIB}/openNI.lib)
