add_library (moduleexecutor moduleexecutor.cpp)
SET (BOT_MODULES ${BOT_MODULES} ping)
IF(ENABLE_KOKO)
    SET (BOT_MODULES ${BOT_MODULES} koko)
ENDIF(ENABLE_KOKO)
SET (BOT_MODULES ${BOT_MODULES} smart)
SET (BOT_MODULES ${BOT_MODULES} pluginexecutor)
SET (BOT_MODULES ${BOT_MODULES} help)
IF (ENABLE_WHO)
    SET (BOT_MODULES ${BOT_MODULES} who)
ENDIF (ENABLE_WHO)
include (CheckIncludeFile)
#include (CheckIncludeFiles)
check_include_file(semaphore.h HAVE_SEMAPHORE_H)
check_include_file(pthread.h HAVE_PTHREAD_H)
target_link_libraries (moduleexecutor ${BOT_MODULES})
