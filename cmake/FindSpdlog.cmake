message("<FindSPDLOG.cmake>")

SET(SPDLOG_SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
	${SPDLOG_PATH}
)

FIND_PATH(SPDLOG_INCLUDE_DIR spdlog
	HINTS
	$ENV{SPDLOGDIR}
	PATH_SUFFIXES include
	PATHS ${SPDLOG_SEARCH_PATHS}
)

find_library(SPDLOG_LIBRARY NAMES fmt
	HINTS
	$ENV{SPDLOGDIR}
	PATH_SUFFIXES lib64 lib
	PATHS ${SPDLOG_SEARCH_PATHS}
)

# SPDLOG may require threads on your system.
# The Apple build may not need an explicit flag because one of the
# frameworks may already provide it.
# But for non-OSX systems, I will use the CMake Threads package.
IF(NOT APPLE)
	FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)

# MinGW needs an additional library, mwindows
# It's total link flags should look like -lmingw32 -lSPDLOGmain -lSPDLOG -lmwindows
# (Actually on second look, I think it only needs one of the m* libraries.)
IF(MINGW)
	SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
ENDIF(MINGW)

message("</FindSPDLOG.cmake>")

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SPDLOG REQUIRED_VARS SPDLOG_INCLUDE_DIR SPDLOG_LIBRARY)
