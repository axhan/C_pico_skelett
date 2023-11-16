cmake_minimum_required(VERSION 3.23)

include(/usr/share/pico-sdk/pico_sdk_init.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)

#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_BUILD_TYPE "Release")


add_compile_options(-Wall -Wno-unused -Wmisleading-indentation)

#if(CMAKE_C_COMPILER STREQUAL gcc)
#    add_compile_options(-Wno-empty-body -Wno-format)
#elseif(CMAKE_C_COMPILER STREQUAL clang)
#    add_compile_options(-fcolor-diagnostics -Wno-empty-translation-unit -Wno-gnu-binary-literal)
#endif()


project(C_pico_skelett C CXX)

pico_sdk_init()

add_executable(skelett)

target_link_libraries(skelett pico_stdlib)

pico_add_extra_outputs(skelett)

target_sources(skelett	PUBLIC
							source/config.c
							source/debug.c
							source/globals.c
							source/memory.c
							source/module1.c
							source/module2.c
							source/skelett.c
							source/timer.c
)

set_source_files_properties(source/config.c		PROPERTIES COMPILE_DEFINITIONS SRC_FILE_config)
set_source_files_properties(source/debug.c		PROPERTIES COMPILE_DEFINITIONS SRC_FILE_debug)
set_source_files_properties(source/globals.c 	PROPERTIES COMPILE_DEFINITIONS SRC_FILE_globals)
set_source_files_properties(source/memory.c 	PROPERTIES COMPILE_DEFINITIONS SRC_FILE_memory)
set_source_files_properties(source/module1.c 	PROPERTIES COMPILE_DEFINITIONS SRC_FILE_module1)
set_source_files_properties(source/module2.c 	PROPERTIES COMPILE_DEFINITIONS SRC_FILE_module2)
set_source_files_properties(source/timer.c 		PROPERTIES COMPILE_DEFINITIONS SRC_FILE_timer)

target_include_directories(skelett	BEFORE	PUBLIC
												source
)

set_target_properties(skelett	PROPERTIES
									C_STANDARD 23
									C_STANDARD_REQUIRED ON
)

