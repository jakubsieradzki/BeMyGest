cmake_minimum_required (VERSION 2.8)
project (BeMyGest)

set(OPENNI_PATH "C:/Program Files (x86)/OpenNI")

add_subdirectory (Common)
add_subdirectory (Samples_OpenNI_Cpp/DisplayRawData)
add_subdirectory (Samples_OpenNI_Cpp/TrackHand)
add_subdirectory (Samples_OpenNI_Cpp/TrackHuman)
