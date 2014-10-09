file (GLOB SOURCE_FILE_LIST src/*.cpp)
file (GLOB HEADER_FILE_LIST src/*.h)

add_executable (DrumMachine ${SOURCE_FILE_LIST} ${HEADER_FILE_LIST})

include_directories (${SFML_INC})
include_directories (${OPENCV_INC})

target_link_libraries (DrumMachine PUBLIC Common)
target_link_libraries (DrumMachine PUBLIC ${SFML_LIB}/*.lib)
target_link_libraries (DrumMachine PUBLIC ${OPENCV_LIB}/*.lib)
