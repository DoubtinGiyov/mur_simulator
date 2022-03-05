cmake_minimum_required(VERSION 3.14)
project(simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

set(GSTREAMER_DIR_DLL "" CACHE PATH "Path to gstreamer libs")

find_package(Qt5 REQUIRED COMPONENTS
        Core
        Widgets
        Gui
        Xml
        Test
        Concurrent
        OpenGL
        Svg
        )

find_package(OpenCV REQUIRED)
find_package(ZeroMQ REQUIRED)

include(UrhoCommon)

if (WIN32)
    include(windeployqt)
endif ()

file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/sources/*.h
        ${PROJECT_SOURCE_DIR}/sources/*.cpp
        )

set(TARGET_NAME simulator)

setup_main_executable()

target_link_libraries(simulator
        ${OpenCV_LIBS}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::Xml
        libzmq
        opengl32
        )

add_custom_command(TARGET simulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different"${CMAKE_SOURCE_DIR}/resources/simulator.pck" $<TARGET_FILE_DIR:simulator>
    )

if (WIN32)
    set(OpenCV_DIR_DLL "${OpenCV_DIR}/bin/$<CONFIGURATION>")

    add_custom_command(TARGET simulator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenCV_DIR_DLL}/opencv_highgui430.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenCV_DIR_DLL}/opencv_imgproc430.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenCV_DIR_DLL}/opencv_core430.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenCV_DIR_DLL}/opencv_imgcodecs430.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenCV_DIR_DLL}/opencv_videoio430.dll" $<TARGET_FILE_DIR:simulator>
        #COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenCV_DIR_DLL}/zlib1.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/intl-8.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/ffi-7.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/z-1.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/orc-0.4-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gstapp-1.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gstreamer-1.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gstriff-1.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gstpbutils-1.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gstbase-1.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gsttag-1.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gstaudio-1.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gstvideo-1.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/glib-2.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gobject-2.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GSTREAMER_DIR_DLL}/gmodule-2.0-0.dll" $<TARGET_FILE_DIR:simulator>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ZeroMQ_DIR}/bin/Release/libzmq-v142-mt-4_3_4.dll" $<TARGET_FILE_DIR:simulator>
        )

    windeployqt(simulator)
endif ()
