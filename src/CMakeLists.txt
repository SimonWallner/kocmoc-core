# cmake list for kocmoc-core src/

# set compiler flags
add_definitions(-Wall -Wextra -pedantic -Werror -Winit-self -Wno-long-long)
add_definitions(-g -O0 -fstack-protector-all)
# later add  -Weffc++ -Wdouble-promotion -Wshadow -Wc++0x-compat -Wfloat-equal -Wmissing-include-dirs


# ----------------- find stuff -------------------------
# find mac related frameworks
if (APPLE)
	find_library(COCOA_FRAMEWORK Cocoa)
	find_library(IOKIT NAMES IOKit)
endif()

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
	message(WARNING "OpenGL not found!")
endif()

# -- glew --
if (WIN32)
	set(GLEW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/windows/glew/include)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8) # i.e. 64 bit
		set(GLEW_LIBRARY ${PROJECT_SOURCE_DIR}/external/windows/glew/lib/Release/x64/glew32s.lib)
	else() # 32 bit
		set(GLEW_LIBRARY ${PROJECT_SOURCE_DIR}/external/windows/glew/lib/Release/Win32/glew32s.lib)
	endif()
else(WIN32)
	find_package(GLEW REQUIRED)
	if(NOT GLEW_FOUND)
		message(WARNING "GLEW not found!")
	endif()
endif()

# -- devil --
if (WIN32)
	set(IL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/windows/devil/include)
	set(IL_LIBRARIES ${PROJECT_SOURCE_DIR}/external/windows/devil/DevIL.lib)
	set(ILU_LIBRARIES ${PROJECT_SOURCE_DIR}/external/windows/devil/ILU.lib)
	set(ILUT_LIBRARIES ${PROJECT_SOURCE_DIR}/external/windows/devil/ILUT.lib)
else()
	find_package(DevIL REQUIRED)
	if(NOT IL_FOUND)
		message(WARNING "DevIL not found!")
	endif()
endif(WIN32)

# -- freetype --
if (WIN32)
	set(FREETYPE_INCLUDE_DIR_freetype2 ${PROJECT_SOURCE_DIR}/external/windows/freetype/include)
	set(FREETYPE_LIBRARY ${PROJECT_SOURCE_DIR}/external/windows/freetype/lib/freetype2412_D.lib)
else()
	find_package(Freetype REQUIRED)
	if(NOT FREETYPE_FOUND)
		message(WARNING "Freetype not found!")
	endif()
endif(WIN32)

# -- tinyxml2 --
find_package(TinyXML REQUIRED)
if(NOT TINYXML_FOUND)
	message(WARNING "TinyXML not found!")
endif()



include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_BINARY_DIR}/include
	${PROJECT_SOURCE_DIR}/external/glfw/include
	${PROJECT_SOURCE_DIR}/external/glm
	${PROJECT_SOURCE_DIR}/external/assimp/include
	${GLEW_INCLUDE_DIR}
	${IL_INCLUDE_DIR}
	# ${PROJECT_SOURCE_DIR}/external/tinyxml2
	${TINYXML_INCLUDE_DIR}
	${FREETYPE_INCLUDE_DIR_ft2build}
	${FREETYPE_INCLUDE_DIR_freetype2}
	${PROJECT_SOURCE_DIR}/external/objectif-lune/server/include
	${PROJECT_SOURCE_DIR}/external/bullet/src
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

set(TARGET_LINK_LIBRARIES kocmoc-core
	glfw
	${OPENGL_gl_LIBRARY}
	${GLEW_LIBRARY}
	${IL_LIBRARIES}
	${ILU_LIBRARIES}
	${ILUT_LIBRARIES}
	${ASSIMP_LIBRARY_RELEASE}
	${TINYXML_LIBRARIES}
	# tinyxml2
	${FREETYPE_LIBRARY}
	objectif-lune
	BulletDynamics
	LinearMath
	BulletCollision
)

if (APPLE)
	set(TARGET_LINK_LIBRARIES ${TARGET_LINK_LIBRARIES}
		${COCOA_FRAMEWORK}
		${IOKIT}
	)
endif()

# link to assimp release right now, since the debug lib is not found
# if it is present, ASSIMP_LIBRARY should work again.

target_link_libraries(${TARGET_LINK_LIBRARIES})
