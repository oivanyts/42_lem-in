cmake_minimum_required(VERSION 3.12)
project(lem-in LANGUAGES C)
#set(CMAKE_C_COMPILER clang)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wextra -Werror -Wall")

add_subdirectory(./libft)

AUX_SOURCE_DIRECTORY(./src SOURCE_FILES)

add_executable(lem-in ${SOURCE_FILES})

target_include_directories(lem-in PUBLIC ./includes)

target_link_libraries(lem-in LIBFT)

