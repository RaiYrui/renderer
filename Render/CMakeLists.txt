# CMakeList.txt: Render 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(SRC ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)
set(SRC ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/src/stb.c)
set(SRC ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)  
# 将源代码添加到此项目的可执行文件。
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable (Render ${SRC})
target_link_libraries(Render IMGUI glfw3 OpenGL32)     
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Render PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
