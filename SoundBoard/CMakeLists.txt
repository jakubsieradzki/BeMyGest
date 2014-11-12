file (GLOB SOURCE_FILE_LIST src/*.cpp)
file (GLOB HEADER_FILE_LIST src/*.h)

add_executable(SoundBoard ${SOURCE_FILE_LIST} ${HEADER_FILE_LIST})

include_directories (${SFML_INC})
include_directories (${BOOST_PATH})

target_link_libraries (SoundBoard PUBLIC Common)
target_link_libraries (SoundBoard PUBLIC stk)
target_link_libraries (SoundBoard PUBLIC ${SFML_LIB}/*.lib)