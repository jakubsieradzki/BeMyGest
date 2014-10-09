file (GLOB SOURCE_FILE_LIST src/*.cpp)
file (GLOB HEADER_FILE_LIST src/*.h)

add_executable (Electricus ${SOURCE_FILE_LIST} ${HEADER_FILE_LIST})

include_directories (${SFML_PATH}/include)
include_directories (${BOOST_PATH})

target_link_libraries (Electricus PUBLIC Common)
target_link_libraries (Electricus PUBLIC ${SFML_PATH}/lib/*.lib)
