# cmake list for kocmoc-core src/

# set compiler flags
add_definitions(-Wall -Wextra -pedantic -Werror -Winit-self -Wno-long-long)
add_definitions(-g -O0 -fstack-protector-all)
# later add  -Weffc++ -Wdouble-promotion -Wshadow -Wc++0x-compat -Wfloat-equal -Wmissing-include-dirs


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

find_package(Freetype REQUIRED)
if(NOT FREETYPE_FOUND)
	message(WARNING "Freetype not found!")
endif()


# find_package(Boost REQUIRED)
# if(NOT Boost_FOUND)
# 	message(WARNING "Boost not found!")
# endif()


include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_BINARY_DIR}/include
	${PROJECT_SOURCE_DIR}/external/glfw/include
	${PROJECT_SOURCE_DIR}/external/glm
	${GLEW_INCLUDE_PATH}
	${IL_INCLUDE_DIR}
	${ASSIMP_INCLUDE_DIR}
	${TINYXML_INCLUDE_DIR}
	${FREETYPE_INCLUDE_DIR_ft2build}
	${FREETYPE_INCLUDE_DIR_freetype2}
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
list(APPEND INCLUDE_HEADER_FILES "${PROJECT_BINARY_DIR}/include/kocmoc-core/version.hpp")


add_library(kocmoc-core ${SOURCE_FILES} ${HEADER_FILES} ${INCLUDE_C_HEADER_FILES} ${INCLUDE_HEADER_FILES})

set (TARGET_LINK_LIBRARIES kocmoc-core
	libglfwStatic
	${COCOA_FRAMEWORK}
	${OPENGL_gl_LIBRARY}
	${GLEW_LIBRARY}
	${IL_LIBRARIES}
	${ILU_LIBRARIES}
	${ILUT_LIBRARIES}
	${ASSIMP_LIBRARY_RELEASE}
	${TINYXML_LIBRARIES}
	${FREETYPE_LIBRARY}
)
# link to assimp release right now, since the debug lib is not found
# if it is present, ASSIMP_LIBRARY should work again.

target_link_libraries(${TARGET_LINK_LIBRARIES})
