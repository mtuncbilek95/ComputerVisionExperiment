cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

# ----------------------- INCLUDES ---------------------------
include(SetupGLFW)
# ------------------------------------------------------------

# ---------------------- FILE ADDITION -----------------------
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SUBDIRECTORIES})
add_executable(CodeBase ${SUBDIRECTORIES})
# ------------------------------------------------------------

# ------------------- INCLUDE DIRECTORIES --------------------
target_include_directories(CodeBase PRIVATE "${CMAKE_SOURCE_DIR}/Source" "${opencv_SOURCE_DIR}/include")
target_link_libraries(CodeBase PUBLIC glfw glm::glm fmt spdlog magic_enum stb)

target_include_directories(CodeBase PRIVATE
        ${OPENCV_CONFIG_FILE_INCLUDE_DIR}
        ${OPENCV_MODULE_opencv_core_LOCATION}/include
        ${OPENCV_MODULE_opencv_highgui_LOCATION}/include
        )
target_link_libraries(CodeBase PUBLIC opencv_core opencv_highgui)

SetupGLFW(CodeBase)
DefineGlmMacros(CodeBase)
AddStbMacros(CodeBase)

if(WIN32)
	include(SetupWindows)
    SetupWin32(CodeBase)
endif()
# ------------------------------------------------------------