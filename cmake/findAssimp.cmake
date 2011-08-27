# found at http://freya3d.org/browser/CMakeFind/FindAssimp.cmake
# original license statement:

# ﻿Copyright 2007-2011 Freya 3D Team. All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
# 
# Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
# Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the distribution.
# THIS SOFTWARE IS PROVIDED BY FREYA 3D TEAM AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
# FREYA 3D TEAM OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# The views and conclusions contained in the software and documentation are those of the authors and should not be interpreted as representing
# official policies, either expressed or implied, of Freya 3D Team.


# Based on http://www.daimi.au.dk/~cgd/code/extensions/Assimp/FindAssimp.cmake
# - Try to find Assimp
# Once done this will define
#
#  ASSIMP_FOUND - system has Assimp
#  ASSIMP_INCLUDE_DIR - the Assimp include directory
#  ASSIMP_LIBRARY - Link these to use Assimp
#  ASSIMP_LIBRARIES


find_path (ASSIMP_INCLUDE_DIR NAMES assimp/assimp.h
  PATHS ENV{CPATH} $ENV{ASSIMP_DIR} $ENV{ASSIMP_DIR}/include $ENV{INCLUDE} $ENV{INCLUDE}
  /usr/include /usr/local/include /opt/local/include ENV INCLUDE/assimp
  ${ASSIMP_ROOT}/include
)
 
set (LIB_PATHS $ENV{LD_LIBRARY_PATH} $ENV{LIBRARY_PATH} $ENV{LIB}
  /usr/lib /usr/local/lib /opt/local/lib
  ${ASSIMP_INCLUDE_DIR}/../lib)

find_library (ASSIMP_LIBRARY_DEBUG NAMES assimpd PATHS ${LIB_PATHS})
find_library (ASSIMP_LIBRARY_RELEASE NAMES assimp PATHS ${LIB_PATHS})

if (ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY_DEBUG AND ASSIMP_LIBRARY_RELEASE)
  set(ASSIMP_FOUND TRUE)
endif()

if (ASSIMP_LIBRARY_DEBUG AND ASSIMP_LIBRARY_RELEASE)
  if (CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
    set (ASSIMP_LIBRARY debug ${ASSIMP_LIBRARY_DEBUG} optimized ${ASSIMP_LIBRARY_RELEASE} )
  else()
    set (ASSIMP_LIBRARY ${ASSIMP_LIBRARY_RELEASE})
  endif()
    # FIXME: This probably should be set for both cases
    set (ASSIMP_LIBRARIES debug ${ASSIMP_LIBRARY_DEBUG} optimized ${ASSIMP_LIBRARY_RELEASE})
endif()

if (ASSIMP_FOUND)
  mark_as_advanced (ASSIMP_INCLUDE_DIR ASSIMP_LIBRARY ASSIMP_LIBRARIES)
endif()

