# build file for KOCMOC-CORE
# (c) 2011, Simon Wallner
# me@simonwallner.at
# http://simonwallner.at
#
#

cmake_minimum_required(VERSION 2.8)
project(kocmoc-core CXX)

# put the libs back into the source tree.
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)  #static libraries 


# -- get git revision number (SHA1) ------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC KOCMOC_CORE_GIT_SHA1)

message(STATUS "KOCMOC-CORE revision hash is: ${KOCMOC_CORE_GIT_SHA1}")



# -- doxygen -----------------------------------------------------------------
set(KOCMOC_CORE_DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/docs)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile)
add_custom_target(doc-kocmoc-core
	${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)



add_subdirectory(external/glfw)
add_subdirectory(src)
