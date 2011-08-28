# cmake list for kocmoc-core src/

# set compiler flags
add_definitions(-Wall -Wextra -pedantic -Werror)
# later add  -Weffc++


# ----------------- find stuff -------------------------
# find cocoa framework
find_library(COCOA_FRAMEWORK Cocoa)


find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
	message(WARNING "OpenGL not found!")
endif()

find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
	message(WARNING "GLEW not found!")
endif()

find_package(DevIL REQUIRED)
if(NOT IL_FOUND)
	message(WARNING "DevIL not found!")
endif()

find_package(Assimp REQUIRED)
if(NOT ASSIMP_FOUND)
	message(WARNING "Assimp not found! Install assimp as well as the debug lib.")
endif()

find_package(TinyXML REQUIRED)
if(NOT TINYXML_FOUND)
	message(WARNING "TinyXML not found!")
endif()

# find_package(Boost REQUIRED)
# if(NOT Boost_FOUND)
# 	message(WARNING "Boost not found!")
# endif()


include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/external/glfw/include
	${PROJECT_BINARY_DIR}/include
	${GLEW_INCLUDE_PATH}
	${IL_INCLUDE_DIR}
	${ASSIMP_INCLUDE_DIR}
	${TINYXML_INCLUDE_DIR}
	# ${Boost_INCLUDE_DIR}
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
	${TINYXML_LIBRARIES}
)

target_link_libraries(${TARGET_LINK_LIBRARIES})


# now build minimal test program
add_executable(kocmoc-core-test MACOSX_BUNDLE kocmoc-core-test.cpp)
target_link_libraries(kocmoc-core-test kocmoc-core libglfwStatic ${GLFW_LIBRARIES})





