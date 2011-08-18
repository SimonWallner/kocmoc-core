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

# get git revision number (SHA1)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC KOCMOC_CORE_GIT_SHA1)

message(STATUS "KOCMOC-CORE revision hash is: ${KOCMOC_CORE_GIT_SHA1}")

add_subdirectory(external/glfw)
add_subdirectory(src)