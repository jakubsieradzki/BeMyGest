cmake_minimum_required (VERSION 2.8)
project (BeMyGest)

set (OPENNI_PATH "C:/Program Files (x86)/OpenNI")
set (SFML_PATH "D:/Programowanie/Biblioteki/Tidy/SFML-2.1_vc2010_x86")
set (BOOST_PATH "D:/Programowanie/Biblioteki/Tidy/boost_1_55_0_vc2010")
set (OPENCV_PATH "D:/Programowanie/Biblioteki/Tidy/opencv/build")

add_subdirectory (Common)
add_subdirectory (Samples_OpenNI_Cpp/DisplayRawData)
add_subdirectory (Samples_OpenNI_Cpp/TrackHand)
add_subdirectory (Samples_OpenNI_Cpp/TrackHuman)
add_subdirectory (Electricus)
add_subdirectory (DrumMachine)