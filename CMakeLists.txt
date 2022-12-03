cmake_minimum_required(VERSION 3.21)

project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(SFML_LIBS sfml-graphics sfml-audio)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

# Dear ImGui
set(IMGUI_DIR include/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)

set(IMGUI_SRC ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/imgui-SFML.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(OpenGL REQUIRED)

set(LIBRARIES "OpenGL::GL")

# define GL_SILENCE_DEPRECATION to silence deprecation warnings
add_compile_definitions(GL_SILENCE_DEPRECATION)

add_executable(app ${SRC_FILES} ${IMGUI_SRC})
target_link_libraries(app PRIVATE ${SFML_LIBS} ${LIBRARIES})
target_compile_features(app PRIVATE cxx_std_17)

install(TARGETS app)
target_compile_definitions(app PUBLIC -DImTextureID=ImU64)