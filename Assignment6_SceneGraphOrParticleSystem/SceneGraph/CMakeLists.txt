cmake_minimum_required(VERSION 3.8.0)

PROJECT(App)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Core Gui OpenGL)
find_package(OpenGL REQUIRED)

include_directories(
  ${QtWidget_INCLUDES}
  ${QtCore_INCLUDES}
  ${QtGui_INCLUDES}
  ${QtOpenGL_INCLUDES}
  include/renderables
  include/window
  include/
)

set(
  HEADERS
  include/renderables/Renderable.h
  include/window/App.h
  include/BasicWidget.h
  include/Camera.h
  include/ObjParser.h
  include/Rotation.h
  include/SceneNode.h
  include/Sphere.h
  include/VertexData.h
)

set(
  SOURCES
  src/renderables/Renderable.cpp
  src/window/App.cpp
  src/BasicWidget.cpp
  src/Camera.cpp
  src/ObjParser.cpp
  src/Rotation.cpp
  src/SceneNode.cpp
  src/Sphere.cpp
  main.cpp
)

add_executable(App
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries(App Qt5::Widgets Qt5::Core Qt5::Gui Qt5::OpenGL OpenGL::GL)

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::OpenGL> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif(WIN32)
