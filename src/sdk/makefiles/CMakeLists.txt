cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(TestOpenCV)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps
	  ${PROJECT_SOURCE_DIR}/include)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	      set (CMAKE_INSTALL_PREFIX "/usr/local/cppjieba" CACHE PATH "default install path" FORCE )
endif()

 ADD_DEFINITIONS(-O3 -Wall -g)
 IF(APPLE) # mac os
	 ADD_DEFINITIONS(-std=c++0x)
 endif()

ADD_SUBDIRECTORY(deps)
ADD_SUBDIRECTORY(test)

#ENABLE_TESTING()
#ADD_TEST(NAME ./test/test.run COMMAND ./test/test.run)
#ADD_TEST(NAME ./load_test COMMAND ./load_test)
#ADD_TEST(NAME ./demo COMMAND ./demo)


#find_package(FFMPEG REQUIRED)
#find_package(X264 REQUIRED)
find_package(OpenCV REQUIRED)

set(OPENCV_ROOT "${PROJECT_SOURCE_DIR}/3rd_party/opencv_3_3_1")
set(OpenCV_INCLUDE_DIR "${OPENCV_ROOT}/include")
set(OpenCV_LIBRARY_DIR "${OPENCV_ROOT}/lib")
set(OpenCV_3RDPARTY_DIR "${OPENCV_ROOT}/3rdparty")
message(STATUS "cv 3rd ................"${OpenCV_3RDPARTY_DIR})


set(OpenCV_LIBS
                "${OpenCV_LIBRARY_DIR}/libopencv_highgui.a"
                "${OpenCV_LIBRARY_DIR}/libopencv_imgcodecs.a"
                "${OpenCV_LIBRARY_DIR}/libopencv_imgproc.a"
                "${OpenCV_LIBRARY_DIR}/libopencv_core.a"
                "${OpenCV_3RDPARTY_DIR}/liblibjasper.a"
                "${OpenCV_3RDPARTY_DIR}/liblibjpeg.a"
                "${OpenCV_3RDPARTY_DIR}/liblibpng.a"
                "${OpenCV_3RDPARTY_DIR}/liblibtiff.a"
                "${OpenCV_3RDPARTY_DIR}/libzlib.a"             
)

set(DEPLOY_DEMO_SRCS
    kmeans.cpp
)

add_executable(Demo ${DEPLOY_DEMO_SRCS})

target_link_libraries(Demo
    #${FFMPEG_LIBRARIES}
    #${X264_LIBRARIES}
    ${OpenCV_LIBS}
    #${OpenCV_LIBRARY_DIR}
    pthread
)
include_directories(
    ${FFMPEG_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIR}
    #${X264_INCLUDE_DIR}
)
