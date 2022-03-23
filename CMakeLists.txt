cmake_minimum_required(VERSION 3.18)

set(target_name HostDetector)
project(HostDetector)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
   set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
   WIN32
   main.cpp
   mainwindow.h mainwindow.cpp
   hoststatuswidget.h hoststatuswidget.cpp
   hoststatusitem.h hoststatusitem.cpp
   globalsetting.h
   detectworker.h detectworker.cpp
   detectmanager.h detectmanager.cpp
   operatewidget.h operatewidget.cpp
   colorbutton.h colorbutton.cpp
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)