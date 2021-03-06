cmake_minimum_required (VERSION 2.6) 
project (NEEXEE)
IF (UNIX)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x -DDEBUG=3 -lpthread")
    SET (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--as-needed")
    SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--as-needed")
    IF (EXTRA_WARNINGS)
        SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -Wextra")
    ENDIF (EXTRA_WARNINGS)
    IF (USE_PIPE)
        SET (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pipe")
    ENDIF (USE_PIPE)
ENDIF (UNIX)

OPTION (WITH_PLUGINS "Build a somewhat standard set of plugins as well" ON)
OPTION (ENABLE_KOKO "Build koko module, which koko on lisp, haskell, etc." ${WITH_PLUGINS} )
OPTION (ENABLE_HELP "Build help module." ${WITH_PLUGINS})
OPTION (ENABLE_HISTORY "Build logger, which scan logs" ${WITH_PLUGINS})
OPTION (ENABLE_SMART "Build Turing test module" ${WITH_PLUGINS})
OPTION (ENABLE_WHO "Build module which allows to see room vCards" ${WITH_PLUGINS})

add_subdirectory (bot)
add_subdirectory (settings)
add_subdirectory (debug)
add_subdirectory (moduleexecutor)
add_subdirectory (tools)
add_subdirectory (console)
add_subdirectory (module)
add_subdirectory (message)
add_executable (neexee main.cpp)
target_link_libraries (neexee bot settings)

FIND_PATH (GLOOX_INCLUDE_DIR "gloox/gloox.h")
FIND_LIBRARY (GLOOX_LIBRARIES gloox)
if (GLOOX_LIBRARIES AND GLOOX_INCLUDE_DIR)
  message (STATUS "gloox library found")
  include_directories (${GLOOX_INCLUDE_DIR})
  target_link_libraries (neexee ${GLOOX_LIBRARIES})
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_GLOOX")
endif (GLOOX_LIBRARIES AND GLOOX_INCLUDE_DIR)

find_library(pthread "pthread.h")
if(PTHREAD_FOUND)
  message(STATUS "pthread library found " ${PTHREAD_INCLUDE_DIRS})
  include_directories(${PTHREAD_INCLUDE_DIRS})
  target_link_libraries(moduleexecutor ${PTHREAD_INCLUDE_DIRS})
endif (PTHREAD_FOUND)
