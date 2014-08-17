find_package(Boost 1.54	COMPONENTS date_time filesystem system REQUIRED)
find_package(MsgPack REQUIRED)
find_package(DBusCpp REQUIRED)
include_directories(${Boost_INCLUDE_DIRS}
					${MsgPack_INCLUDE_DIRS}
					${DBUSCPP_INCLUDE_DIR})

set(LIBRARIES ${Boost_LIBRARIES} ${MsgPack_LIBRARIES} ${DBUSCPP_LIBRARIES})
set(DESTINATION_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE INTERNAL "")            # global variable

configure_file( "config.h.in" "config.h" )
#configure_file( ${CMAKE_SOURCE_DIR}/source/config.h.in ${CMAKE_BINARY_DIR}/source/config.h ) 
include_directories(${CMAKE_BINARY_DIR}/source)

add_executable (${PROJECT_NAME} main.cpp Daemon.cpp Data.cpp ParserXML.cpp
            Storage.cpp SignalHandler.cpp)
target_link_libraries (${PROJECT_NAME} ${LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})


################################################################################
################################################################################
if(CMAKE_LOG)
	message("\n====================================================================")
	message(STATUS "Boost_FOUND                = ${Boost_FOUND}")
	message(STATUS "Boost_INCLUDE_DIRS         = ${Boost_INCLUDE_DIRS}")
	message(STATUS "Boost_LIBRARY_DIRS         = ${Boost_LIBRARY_DIRS}")
	message(STATUS "Boost_LIBRARIES            = ${Boost_LIBRARIES}")
	message(STATUS "Boost_DATE_TIME_FOUND      = ${Boost_DATE_TIME_FOUND}")
	message(STATUS "Boost_DATE_TIME_LIBRARY    = ${Boost_DATE_TIME_LIBRARY}")
	message(STATUS "Boost_FILESYSTEM_FOUND     = ${Boost_FILESYSTEM_FOUND}")
	message(STATUS "Boost_FILESYSTEM_LIBRARY   = ${Boost_FILESYSTEM_LIBRARY}")
	message(STATUS "Boost_SYSTEM_FOUND         = ${Boost_SYSTEM_FOUND}")
	message(STATUS "Boost_SYSTEM_LIBRARY       = ${Boost_SYSTEM_LIBRARY}")
	message(STATUS "")
	message(STATUS "MSGPACK_FOUND              = ${MSGPACK_FOUND}")
	message(STATUS "MsgPack_INCLUDE_DIRS       = ${MsgPack_INCLUDE_DIRS}")
	message(STATUS "MsgPack_LIBRARIES          = ${MsgPack_LIBRARIES}")
	message(STATUS "MsgPack_INCLUDE_DIR        = ${MsgPack_INCLUDE_DIR}")
	message(STATUS "MsgPack_LIBRARY            = ${MsgPack_LIBRARY}")
	message(STATUS "")
	message(STATUS "DBUSCPP_FOUND              = ${DBUSCPP_FOUND}")
	message(STATUS "DBUSCPP_INCLUDE_DIR        = ${DBUSCPP_INCLUDE_DIR}")
	message(STATUS "DBUSCPP_LIBRARIES          = ${DBUSCPP_LIBRARIES}")
	message(STATUS "")
	message(STATUS "INCLUDE_DIRECTORIES:")
	get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
	foreach(dir ${dirs})
	  message(STATUS "dir='${dir}'")
	endforeach()
	message(STATUS "")
	message(STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
	message("====================================================================\n")
endif(CMAKE_LOG)
