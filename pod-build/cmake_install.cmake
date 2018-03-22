# Install script for directory: /Users/tristanschuler/Desktop/AprilTags

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/tristanschuler/Desktop/AprilTags/build")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/tristanschuler/Desktop/AprilTags/pod-build/lib/libapriltags.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libapriltags.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libapriltags.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libapriltags.a")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/AprilTags" TYPE FILE FILES
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Edge.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/FloatImage.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/GLine2D.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/GLineSegment2D.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Gaussian.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/GrayModel.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Gridder.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Homography33.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/MathUtil.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Quad.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Segment.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Tag16h5.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Tag16h5_other.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Tag25h7.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Tag25h9.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Tag36h11.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Tag36h11_other.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/Tag36h9.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/TagDetection.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/TagDetector.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/TagFamily.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/UnionFindSimple.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/XYWeight.h"
    "/Users/tristanschuler/Desktop/AprilTags/AprilTags/pch.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/tristanschuler/Desktop/AprilTags/pod-build/lib/pkgconfig/apriltags.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/tristanschuler/Desktop/AprilTags/pod-build/example/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/tristanschuler/Desktop/AprilTags/pod-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
