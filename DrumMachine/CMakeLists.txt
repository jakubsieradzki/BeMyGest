file (GLOB SOURCE_FILE_LIST src/*.cpp)
file (GLOB HEADER_FILE_LIST src/*.h)

add_executable (DrumMachine ${SOURCE_FILE_LIST} ${HEADER_FILE_LIST})

include_directories (${SFML_PATH}/include)
include_directories (${OPENCV_PATH}/include)

target_link_libraries (DrumMachine PUBLIC Common)
target_link_libraries (DrumMachine PUBLIC ${SFML_PATH}/lib/*.lib)
target_link_libraries (DrumMachine PUBLIC ${OPENCV_PATH}/x86/vc10/lib/*.lib)
