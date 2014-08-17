# Taken from https://github.com/nathansamson/Bacsy-DBus/blob/master/cmake/FindDBusCpp.cmake

# Written by Nathan Samson <nathansamson@gmail.com>, 2011
#
# License: Public domain.
#
# Defines
#
#  DBUSCPP_INCLUDE_DIRS
#     which contains the include directory for dbus-c++/dbus.h
#
#  DBUSCPP_LIBRARIES
#     which contains the library directory for libdbus-c++-1
#

# Modificated by Grzegorz Rynkowski <grzegorz.rynkowski@gmail.com>, 2014
	
find_path(DBUSCPP_INCLUDE_DIR dbus-c++/dbus.h
                 PATH_SUFFIXES include/dbus-c++-1)

find_library(DBUSCPP_LIBRARY dbus-c++-1
                 PATH_SUFFIXES lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DBusCpp DEFAULT_MSG DBUSCPP_LIBRARY DBUSCPP_INCLUDE_DIR)

# Copy the results to the output variables.
IF(DBUSCPP_FOUND)
  SET(DBUSCPP_LIBRARIES ${DBUSCPP_LIBRARY})
  SET(DBUSCPP_INCLUDE_DIRS ${DBUSCPP_INCLUDE_DIR})
ELSE(DBUSCPP_FOUND)
  SET(DBUSCPP_LIBRARIES)
  SET(DBUSCPP_INCLUDE_DIRS)
ENDIF(DBUSCPP_FOUND)

MARK_AS_ADVANCED(DBUSCPP_INCLUDE_DIR DBUSCPP_LIBRARY)
