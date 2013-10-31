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
# include(GetGitRevisionDescription)
# get_git_head_revision(GIT_REFSPEC KOCMOC_CORE_GIT_SHA1)
# message(STATUS "KOCMOC-CORE revision hash is: ${GIT_REFSPEC} ${KOCMOC_CORE_GIT_SHA1}")



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

# core media file handling
# -- check xml files ---------------------------------------------------------
set (XML_FILES 
	${PROJECT_SOURCE_DIR}/media/kocmoc-core-config.xml.in
	)

foreach(f ${XML_FILES})
	if (NOT EXISTS ${f})
		message(WARNING "file: ${f} does not exist!")
	endif()
			
	execute_process(
		COMMAND xmllint ${f} --valid
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
		RESULT_VARIABLE XML_VALIDATION_RESULT
		OUTPUT_QUIET
		)

	if (XML_VALIDATION_RESULT) # 1 => error, 0 => OK
		message(WARNING "faild to validate xml file: ${f}")
	endif()
endforeach()

# -- copy and configure ------------------------------------------------------
if(NOT DEFINED KOCMOC_CORE_CONFIG_TARGET_LOCATION)
	message(WARNING "the variable KOCMOC_CORE_CONFIG_TARGET_LOCATION is not set. Now go and define it!")
endif()

# message(STATUS "configuring files...")
set(KOCMOC_CORE_MEDIA_PATH ${PROJECT_SOURCE_DIR}/media/)
configure_file(media/kocmoc-core-config.xml.in ${KOCMOC_CORE_CONFIG_TARGET_LOCATION})

set(GLFW_BUILD_EXAMPLES 'OFF')
set(GLFW_BUILD_TESTS 'OFF')
add_subdirectory(external/glfw)
add_subdirectory(external/objectif-lune/server)
add_subdirectory(src)
