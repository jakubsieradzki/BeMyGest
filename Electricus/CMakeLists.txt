file (GLOB SOURCE_FILE_LIST src/*.cpp)
file (GLOB HEADER_FILE_LIST src/*.h)

add_executable (Electricus ${SOURCE_FILE_LIST} ${HEADER_FILE_LIST})

include_directories (${SFML_PATH}/include)
include_directories (${BOOST_PATH})

target_link_libraries (Electricus PUBLIC Common)
target_link_libraries (Electricus PUBLIC ${SFML_PATH}/lib/*.lib)

#set(BOOST_INCLUDEDIR ${BOOST_PATH})
#set(BOOST_LIBRARYDIR "${BOOST_PATH}/lib32-msvc-10.0")
#set(Boost_USE_STATIC_LIBS   ON)
#set(Boost_USE_MULTITHREADED ON)

#find_package(Boost 1.55.0 COMPONENTS system REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})
#target_link_libraries(Electricus ${Boost_LIBRARIES})

