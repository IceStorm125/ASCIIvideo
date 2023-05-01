cmake_minimum_required(VERSION 3.4.0)

project(ASCIIVIDEO)

set(CMAKE_BUILD_TYPE Release)

find_package(OpenCV REQUIRED)

if(NOT OpenCV_FOUND)
	message(SEND_ERROR "Failed to find OpenCV")
	return()
else()
	include_directories(${OpenCV_INCLUDE_DIRS})
endif()

find_package(Boost COMPONENTS system REQUIRED)

include_directories(
	include/
	include/*

)


add_executable(
	output
	main.cpp
)

target_link_libraries(output ${OpenCV_LIBS})
