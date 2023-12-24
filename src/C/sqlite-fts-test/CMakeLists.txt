cmake_minimum_required(VERSION 3.23)
project(sqlite_test C)

set(CMAKE_C_STANDARD 99)

find_package (PkgConfig)
pkg_check_modules(SQLITE REQUIRED sqlite3)

add_executable(sqlite_test main.c)
target_link_libraries(sqlite_test
        PRIVATE
        PUBLIC
        ${SQLITE_LIBRARIES})