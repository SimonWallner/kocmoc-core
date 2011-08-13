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


add_subdirectory(src)