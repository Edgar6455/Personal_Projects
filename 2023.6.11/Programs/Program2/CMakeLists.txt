cmake_minimum_required(VERSION 3.10)
project(Program2)

set(CMAKE_CXX_STANDARD 20)

find_path(WINSOCK_INCLUDE_DIR WinSock2.h)
if(MSVC)
    find_library(WINSOCK_LIBRARY mswsock.lib)
    find_library(WINSOCK2_LIBRARY ws2_32.lib)
    find_library(WINSOCK2_LIBRARY bcrypt.lib)
else()
    find_library(WINSOCK_LIBRARY mswsock)
    find_library(WINSOCK2_LIBRARY ws2_32)
    find_library(WINSOCK2_LIBRARY bcrypt)
endif()

# Handle the REQUIRED argument and set WINSOCK_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WinSock DEFAULT_MSG WINSOCK_LIBRARY WINSOCK2_LIBRARY WINSOCK_INCLUDE_DIR)

mark_as_advanced(WINSOCK_INCLUDE_DIR)
mark_as_advanced(WINSOCK_LIBRARY)
mark_as_advanced(WINSOCK2_LIBRARY)

if(WINSOCK_FOUND)
    add_definitions(-DWINSOCK_SUPPORT)
    set(WINSOCK_LIBRARIES ${WINSOCK_LIBRARY} ${WINSOCK2_LIBRARY})

endif()

if(MINGW)
    set(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} -lwsock32 -lws2_32 -lbcrypt")
    set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lwsock32 -lws2_32 -lbcrypt")
    set(DCMAKE_CXX_CLANG_TIDY=/usr/bin/clang-tidy)
endif()

if(WIN32)
    add_executable(Program2 main.cpp Connection.h ConnectionWindows.cpp ConnectionWindows.h)
else()
    add_executable(Program2 main.cpp Connection.h ConnectionUnix.h ConnectionUnix.cpp)
    target_link_libraries(Program2 PRIVATE -pthread)
endif()

target_include_directories(Program2 PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/../Common)