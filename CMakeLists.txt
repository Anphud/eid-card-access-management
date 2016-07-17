cmake_minimum_required (VERSION 2.6)

# Project info
set(PROJ_NAME AuthorizationSystem)
project(${PROJ_NAME})

# Set an output directory for our binaries
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

# include src headers
include_directories(${PROJECT_SOURCE_DIR}/src)

# be eid includes
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/rsaref220)

# Add all cpp files
# TODO: loop over subdirectories
file(GLOB AUTHSYS_SRC
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJ_NAME} ${AUTHSYS_SRC})

# Look up SDL2 and add the include directory to our include path
IF(CMAKE_SYSTEM_NAME MATCHES Windows)
	file(GLOB SDL2_LIBRARIES ${PROJECT_SOURCE_DIR}/SDL2/lib/x86/*.lib)
	include_directories(${PROJECT_SOURCE_DIR}/SDL2/include)
	target_link_libraries(${PROJ_NAME} ${SDL2_LIBRARIES})
ELSE()
	INCLUDE(FindPkgConfig)
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(${PROJ_NAME} ${SDL2_LIBRARIES})
ENDIF()

# C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
