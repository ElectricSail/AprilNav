# Install script for directory: /home/tristan/Desktop/AprilTags

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/tristan/Desktop/AprilTags/build")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/tristan/Desktop/AprilTags/pod-build/lib/libapriltags.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/AprilTags" TYPE FILE FILES
    "/home/tristan/Desktop/AprilTags/AprilTags/GLineSegment2D.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/TagFamily.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Tag36h11.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Tag36h9.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/TagOptimization.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/XYWeight.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/FloatImage.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Tag16h5_other.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Homography33.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Tag25h9.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Quad.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Segment.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/TagDetector.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/GLine2D.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/pch.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Tag25h7.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Tag36h11_other.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Gaussian.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/UnionFindSimple.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Edge.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/TagDetection.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/MathUtil.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Tag16h5.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/Gridder.h"
    "/home/tristan/Desktop/AprilTags/AprilTags/GrayModel.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/tristan/Desktop/AprilTags/pod-build/lib/pkgconfig/apriltags.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/tristan/Desktop/AprilTags/pod-build/StarTracker/cmake_install.cmake")
  include("/home/tristan/Desktop/AprilTags/pod-build/example/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/tristan/Desktop/AprilTags/pod-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
