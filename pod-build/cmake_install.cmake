# Install script for directory: /home/pi/Desktop/AprilTags2

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pi/Desktop/AprilTags2/build")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/pi/Desktop/AprilTags2/pod-build/lib/libapriltags.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/AprilTags" TYPE FILE FILES
    "/home/pi/Desktop/AprilTags2/AprilTags/Edge.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/FloatImage.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/GLine2D.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/GLineSegment2D.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Gaussian.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/GrayModel.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Gridder.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Homography33.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/MathUtil.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Quad.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Segment.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Tag16h5.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Tag16h5_other.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Tag25h7.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Tag25h9.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Tag36h11.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Tag36h11_other.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/Tag36h9.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/TagDetection.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/TagDetector.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/TagFamily.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/UnionFindSimple.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/XYWeight.h"
    "/home/pi/Desktop/AprilTags2/AprilTags/pch.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/pi/Desktop/AprilTags2/pod-build/lib/pkgconfig/apriltags.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/pi/Desktop/AprilTags2/pod-build/example/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/pi/Desktop/AprilTags2/pod-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
