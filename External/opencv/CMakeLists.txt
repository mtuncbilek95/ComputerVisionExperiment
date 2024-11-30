cmake_minimum_required(VERSION 3.26)

include(FetchContent)

# Make URL variable
if(NOT DEFINED OCV_URL)
    set(OCV_URL https://github.com/opencv/opencv.git)
endif()

# GLFW Library
FetchContent_Declare(
        opencv
        EXCLUDE_FROM_ALL
        GIT_REPOSITORY ${OCV_URL}
        GIT_TAG 4.6.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(opencv)