# cmake list for kocmoc-core src/

# set compiler flags
add_definitions(-Wall -Wextra -pedantic -Werror)
# later add  -Weffc++


# ----------------- find stuff -------------------------
# find cocoa framework
find_library(COCOA_FRAMEWORK Cocoa)
if(!COCOA_FRAMEWORK_FOUND)
	message(WARNING "Cocoa Framework not found!")
endif(!COCOA_FRAMEWORK_FOUND)

find_package(OpenGL REQUIRED)
if(!OPENGL_FOUND)
	message(WARNING "OpenGL not found!")
endif(!OPENGL_FOUND)

find_package(GLEW REQUIRED)
if(!GLEW_FOUND)
	message(WARNING "GLEW not found!")
endif(!GLEW_FOUND)

find_package(DevIL REQUIRED)
if(!DEVIL_FOUND)
	message(WARNING "DevIL not found!")
endif(!DEVIL_FOUND)

find_package(Assimp REQUIRED)
if(!ASSIMP_FOUND)
	message(WARNING "Assimp not found!")
endif(!ASSIMP_FOUND)

find_package(TinyXML REQUIRED)
if(!TINY_FOUND)
	message(WARNING "TinyXML not found!")
endif(!TINY_FOUND)



include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/external/glfw/include
	${PROJECT_BINARY_DIR}/include
	${GLEW_INCLUDE_PATH}
	${IL_INCLUDE_DIR}
	${ASSIMP_INCLUDE_DIR}
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

set (TARGET_LINK_LIBRARIES kocmoc-core
	libglfwStatic
	${COCOA_FRAMEWORK}
	${OPENGL_gl_LIBRARY}
	${GLEW_LIBRARY}
	${IL_LIBRARIES}
	${ILU_LIBRARIES}
	${ILUT_LIBRARIES}
	${ASSIMP_LIBRARY}
)

target_link_libraries(${TARGET_LINK_LIBRARIES})


# now build minimal test program
add_executable(kocmoc-core-test MACOSX_BUNDLE main.cpp)
target_link_libraries(kocmoc-core-test kocmoc-core libglfwStatic ${GLFW_LIBRARIES})





