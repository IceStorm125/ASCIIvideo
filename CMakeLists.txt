cmake_minimum_required(VERSION 3.4.0)

project(ASCIIVIDEO)

set(CMAKE_BUILD_TYPE Release)

include("${CMAKE_CURRENT_BINARY_DIR}/Release/generators/conan_toolchain.cmake")

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS program_options filesystem REQUIRED)

add_executable(
	output
	main.cpp
)

target_link_libraries(output 
	${OpenCV_LIBS}
	Boost::program_options 
	Boost::filesystem
)
