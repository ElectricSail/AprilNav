cmake_minimum_required (VERSION 2.6)

link_libraries(apriltags)

# Follow this format for adding new additions to the code using dependencies

add_executable(apriltags_demo apriltags_demo.cpp Serial.cpp)
pods_install_executables(apriltags_demo)

add_executable(imu imu.cpp Serial.cpp)
pods_install_executables(imu)

add_executable(apriltagscsv apriltagscsv.cpp Serial.cpp)
pods_install_executables(apriltagscsv)

add_executable(StarTracker StarTracker.cpp Serial.cpp)
pods_install_executables(StarTracker)

add_executable(StarTracker_testtags StarTracker_testtags.cpp Serial.cpp)
pods_install_executables(StarTracker_testtags)

add_executable(VideoTest VideoTest.cpp Serial.cpp)
pods_install_executables(VideoTest)

add_executable(SerialTest SerialTest.cpp Serial.cpp)
pods_install_executables(SerialTest)

add_executable(ATStripped ATStripped.cpp Serial.cpp)
pods_install_executables(ATStripped)
