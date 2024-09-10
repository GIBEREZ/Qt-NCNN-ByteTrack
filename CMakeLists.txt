cmake_minimum_required(VERSION 3.27)
project(WIFI_Qt)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/EnglishRuanjian/Qt6/6.7.1/msvc2019_64")

set(ncnn_DIR "D:/English/C++Lib/ncnn-20240410-windows-vs2022/x64/lib/cmake/ncnn")

set(OpenCV_DIR "D:/English/C++Lib/opencv-4.9.0/opencv/build/x64/vc16/lib")

set(Eigen3_DIR "D:/English/C++Lib/eigen-3.4.0/bulid/share/eigen3/cmake")

set(QT_INSTALL_PLUGINS "${CMAKE_PREFIX_PATH}/plugins")
set(QT_MULTIMEDIA_PLUGINS "${QT_INSTALL_PLUGINS}/multimedia")

find_package(Qt6
        COMPONENTS
        Core
        Gui
        Widgets
        Network
        Multimedia
        MultimediaWidgets
        REQUIRED
)

find_package(
        ncnn
        REQUIRED
)

find_package(OpenCV
        REQUIRED
        core
        imgproc
)
find_package(MySQL
        REQUIRED
)

find_package(Eigen3
        REQUIRED
)

include_directories("D:/English/C++Lib/ffmpeg/include")
link_directories("D:/English/C++Lib/ffmpeg/lib")

include_directories("E:\\Program Files\\MySQL\\MySQL Server 8.0\\include")
link_directories("E:\\Program Files\\MySQL\\MySQL Server 8.0\\lib")
link_libraries(libmysql)

include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARIES})

# 手动指定 Windows SDK 的头文件路径
include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um")
include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared")
# 手动指定 Windows SDK 的库文件路径
link_directories("C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64")
link_directories("C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/shared/x64")

add_executable(WIFI_Qt main.cpp
        GUI.hpp
        GUI.cpp
        ui.hpp
        ncnn_yolo.cpp
        ncnn_yolo.hpp
        TcpSocket.cpp
        TcpSocket.hpp
        ByteTrack/BYTETracker.cpp
        ByteTrack/BYTETracker.h
        ByteTrack/dataType.h
        ByteTrack/kalmanFilter.h
        ByteTrack/kalmanFilter.cpp
        ByteTrack/lapjv.h
        ByteTrack/lapjv.cpp
        ByteTrack/STrack.h
        ByteTrack/STrack.cpp
        ByteTrack/utils.cpp
)

target_link_libraries(WIFI_Qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Multimedia
        Qt::MultimediaWidgets
        ncnn
        ${OpenCV_LIBS}
        libmysql
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
        Eigen3::Eigen
        user32
        gdi32
        dwmapi
)

add_custom_command(TARGET WIFI_Qt POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${QT_MULTIMEDIA_PLUGINS}"
        "$<TARGET_FILE_DIR:WIFI_Qt>/plugins/multimedia"
        COMMENT "Copying Qt Multimedia plugins to binary directory"
        VERBATIM
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()

    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
