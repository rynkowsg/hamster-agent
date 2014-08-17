cmake_minimum_required(VERSION 2.8)
project (hamster-agent)

option(CMAKE_LOG "Print logs from CMakefiels" OFF)

# The version number.
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)
set (PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}" CACHE INTERNAL "")

set(CMAKE_BUILD_TYPE "Debug")   #TODO: Release has some problems with NDEBUG flag. Check it!


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror "
					"-pedantic -Wcast-qual -Wno-unused-parameter "
					"-Wpointer-arith -Wredundant-decls -Wwrite-strings -Wabi "
					"-Wctor-dtor-privacy -Wno-deprecated "
					"-Wno-non-template-friend -Wno-pmf-conversions "
					"-Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo")
string(REPLACE ";" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake)

# add subdirectories
add_subdirectory(source)
add_subdirectory(resources)


################################################################################
################################################################################
if(CMAKE_LOG)
	message("\n====================================================================")
	message(STATUS "PROJECT_NAME       = ${PROJECT_NAME}")
	message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
	message(STATUS "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
	message(STATUS "CMAKE_SOURCE_DIR   = ${CMAKE_SOURCE_DIR}")
	message(STATUS "CMAKE_BINARY_DIR   = ${CMAKE_BINARY_DIR}")
	message(STATUS "CMAKE_MODULE_PATH  = ${CMAKE_MODULE_PATH}")
	message(STATUS "CMAKE_LOG          = ${CMAKE_LOG}")
    message(STATUS "CMAKE_BUILD_TYPE   = ${CMAKE_BUILD_TYPE}")
    message(STATUS "CMAKE_CXX_FLAGS_DEBUG   = ${CMAKE_CXX_FLAGS_DEBUG}")
    message(STATUS "CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")
    message(STATUS "CMAKE_CXX_FLAGS         = ${CMAKE_CXX_FLAGS}")
    #message(STATUS "   = ${}")
    message(STATUS "PROJECT VERSION: ${${PROJECT_NAME}_VERSION}")
    message("====================================================================\n")
endif(CMAKE_LOG)
