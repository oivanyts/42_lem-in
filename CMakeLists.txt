cmake_minimum_required(VERSION 3.12)
project(LEM-IN LANGUAGES C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-Wextra -Werror -Wall")

add_subdirectory(./libft)

AUX_SOURCE_DIRECTORY(./src SOURCE_FILES)

add_executable(lemin ${SOURCE_FILES})

target_include_directories(lemin PUBLIC ./includes)

target_link_libraries(lemin LIBFT)

