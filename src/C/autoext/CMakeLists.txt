cmake_minimum_required(VERSION 3.24)
project(autoext C)

set(CMAKE_C_STANDARD 11)
set(ENV{PKG_CONFIG_PATH} "/usr/local/opt/sqlite/lib/pkgconfig")

find_package(PkgConfig REQUIRED)
pkg_search_module(PKG_SQLITE3 REQUIRED IMPORTED_TARGET sqlite3)

#find_library(SQLITE_LIBRARY sqlite3 /usr/local/)
add_executable(autoext main.c)
#target_link_libraries(autoext ${SQLITE_LIBRARY})
target_link_libraries(autoext PRIVATE PkgConfig::PKG_SQLITE3)
