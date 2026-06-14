cmake_minimum_required(VERSION 3.16)

project(atm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(atm main.cpp
    messaging.h messaging.cpp
    messages.h
    atm.h atm.cpp
    if.h if.cpp
    bank.h bank.cpp)

include(GNUInstallDirs)
install(TARGETS atm
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
