# cmake list for kocmoc-core src/

# set compiler flags
add_definitions(-Wall -Wextra -pedantic -Werror)

include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/external/glfw/include
	${PROJECT_SOURCE_DIR}/external/gl3w/include
	${PROJECT_BINARY_DIR}/include
)

link_directories(
#    ${PROJECT_SOURCE_DIR}/external/glfw/lib
)

# collect the files
file(GLOB_RECURSE INCLUDE_C_HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE INCLUDE_HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

# git revision number magic
# configure header file and append it to the other header files
configure_file("${PROJECT_SOURCE_DIR}/include/kocmoc-core/version.hpp.in" "${PROJECT_BINARY_DIR}/include/kocmoc-core/version.hpp")
list(APPEND INCLUDE_C_HEADER_FILES "${PROJECT_BINARY_DIR}/include/kocmoc-core/version.hpp")

add_library(kocmoc-core ${SOURCE_FILES} ${HEADER_FILES} ${INCLUDE_C_HEADER_FILES} ${INCLUDE_HEADER_FILES})


# find cocoa framework
find_library(COCOA_FRAMEWORK Cocoa)
message(STATUS "cocoa fw: ${COCOA_FRAMEWORK}")

# find Opengl
find_package(OpenGL REQUIRED)
message(STATUS "Open GL lib: ${OPENGL_gl_LIBRARY}")

set (TARGET_LINK_LIBRARIES kocmoc-core
	libglfwStatic
	gl3w
	${COCOA_FRAMEWORK}
	${OPENGL_gl_LIBRARY}
)

target_link_libraries(${TARGET_LINK_LIBRARIES})


# now build minimal test program
add_executable(kocmoc-core-test MACOSX_BUNDLE main.cpp)
target_link_libraries(kocmoc-core-test kocmoc-core libglfwStatic ${GLFW_LIBRARIES})





