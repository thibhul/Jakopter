CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(jakopter)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(SDL2)
FIND_PACKAGE(FFMPEG)
FIND_PACKAGE(Lua51)

# Debug : print all declared variables
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#	message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

INCLUDE_DIRECTORIES("include/")

SET(CMAKE_BUILD_TYPE DEBUG)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY build/${CMAKE_BUILD_TYPE})

SET(
	CORE_SRC_FILES
	src/drone.c
	src/navdata.c
	src/com_channel.c
)

SET(
	VIDEO_SRC_FILES
	src/video.c
	src/video_decode.c
	src/video_process.c
	src/video_display.c
)

SET(
	LUA_SRC_FILES
	src/lua_bindings.c
)

SET(
	SRC_FILES
	${CORE_SRC_FILES}
)

IF(AVCODEC_FOUND AND SDL2_FOUND)
	MESSAGE(STATUS "Compiling with libavcodec and SDL2")
	INCLUDE_DIRECTORIES(${AVCODEC_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR})
	SET(
		SRC_FILES
		${SRC_FILES}
		${VIDEO_SRC_FILES}
	)
ELSE()
	MESSAGE(WARNING "Compiling WITHOUT libavcodec and SDL2")
ENDIF()

IF(LUA51_FOUND)
	MESSAGE(STATUS "Compiling with Lua")
	INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
	SET(
		SRC_FILES
		${SRC_FILES}
		${LUA_SRC_FILES}
	)
ELSE()
	MESSAGE(WARNING "Compiling WITHOUT Lua")
ENDIF()

ADD_LIBRARY(
	jakopter SHARED 
	${SRC_FILES}	
)

TARGET_LINK_LIBRARIES(jakopter ${CMAKE_THREAD_LIBS_INIT})
IF(AVCODEC_FOUND AND SDL2_FOUND)
	TARGET_LINK_LIBRARIES(jakopter ${AVCODEC_LIBRARIES} ${SDL2_LIBRARY})
ENDIF()