cmake_minimum_required(VERSION 3.28)
project(test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -pedantic -Wextra)

add_subdirectory("external/glfw")
add_subdirectory("external/glew/build/cmake")
add_subdirectory("external/plutosvg")
add_subdirectory("external/fmt")

function(add_exe TARGET_NAME)

	file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}/*.cpp")
	add_executable(${TARGET_NAME} ${SOURCES})

	add_dependencies(${TARGET_NAME}
		fmt
		glfw
		glew
		plutosvg
	)

	target_link_directories(${TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/build/lib")

	target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/external/include"
	)

	if (WIN32)
		target_link_libraries(${TARGET_NAME} PUBLIC glew32 glfw3 opengl32 plutosvg plutovg fmt)
	endif()

endfunction()

add_exe(01_hello_window)
add_exe(02_hello_triangle)
add_exe(03_texture)
add_exe(04_trans)