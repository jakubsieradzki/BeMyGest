cmake_minimum_required (VERSION 2.8)
project (BeMyGest)

set (OPENNI_INC "C:/Program Files (x86)/OpenNI/Include")
set (OPENNI_LIB "C:/Program Files (x86)/OpenNI/Lib")
set (SFML_INC "D:/Programowanie/Biblioteki/Tidy/SFML-2.1_vc2010_x86/include")
set (SFML_LIB "D:/Programowanie/Biblioteki/Tidy/SFML-2.1_vc2010_x86/lib")
set (BOOST_PATH "D:/Programowanie/Biblioteki/Tidy/boost_1_55_0_vc2010")
set (OPENCV_INC "D:/Programowanie/Biblioteki/Tidy/opencv/build/include")
set (OPENCV_LIB "D:/Programowanie/Biblioteki/Tidy/opencv/build/x86/vc10/lib")

add_subdirectory (Common)
add_subdirectory (Samples_OpenNI_Cpp/DisplayRawData)
add_subdirectory (Samples_OpenNI_Cpp/TrackHand)
add_subdirectory (Samples_OpenNI_Cpp/TrackHuman)
add_subdirectory (Electricus)
add_subdirectory (DrumMachine)
add_subdirectory (External/stk)
add_subdirectory (SoundBoard)