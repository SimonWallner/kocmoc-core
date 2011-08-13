# cmake list for kocmoc-core src/


include_directories(
	../include
#   ${PROJECT_SOURCE_DIR}/external/glfw/include
)

# link_directories(
#    ${PROJECT_SOURCE_DIR}/external/glfw/lib
# )

# collect the files
file(GLOB INCLUDE_C_HEADER_FILES ../include/*.h)
file(GLOB INCLUDE_HEADER_FILES ../include/*.hpp)
file(GLOB HEADER_FILES *.hpp)
file(GLOB SOURCE_FILES *.cpp)

add_library(kocmoc-core ${SOURCE_FILES} ${HEADER_FILES} ${INCLUDE_C_HEADER_FILES} ${INCLUDE_HEADER_FILES})

set (TARGET_LINK_LIBRARIES	kocmoc-core
#    glfw
)

target_link_libraries(${TARGET_LINK_LIBRARIES})





