cmake_minimum_required(VERSION 3.10)
project(WCCreate)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
add_executable(WCCreate cMain.cpp cApp.cpp)
target_link_libraries(WCCreate ${wxWidgets_LIBRARIES})