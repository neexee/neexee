add_library (bot bot.cpp query.cpp)
target_link_libraries (bot debuglib moduleexecutor tools console message)
