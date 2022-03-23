
set(target_name HostDetector)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${target_name}
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

target_link_libraries(${target_name} Qt5::Widgets)

file(COPY ${CMAKE_SOURCE_DIR}/translations/qm/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/translations)
file(COPY ${CMAKE_SOURCE_DIR}/translations/qm/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/translations)