cmake_minimum_required(VERSION 3.5...3.27)

set(CMAKE_VERBOSE_MAKEFILE	OFF)
set(CMAKE_WARN_DEPRECATED	OFF CACHE BOOL "" FORCE)
set(PICO_SDK_PATH			~/src/pico-sdk)
set(PICO_BOARD				pico)
set(PICO_PLATFORM			rp2040)
set(PICO_STDIO_DEFAULT_CRLF	1)
set(PICO_STDIO_USB			1)


include(~/src/pico-sdk/pico_sdk_init.cmake)

add_compile_options(-Wall -Wno-unused -Wmisleading-indentation -Wno-strict-aliasing)

project(C_pico_skelett ASM C CXX)

pico_sdk_init()

add_executable(skelett)

set_target_properties(skelett	PROPERTIES	C_STANDARD 23
											C_STANDARD_REQUIRED ON
)

add_library(st7735	source/lib-st7735/src/ST7735_TFT.c
					source/lib-st7735/src/hw.c
)

#target_compile_definitions(skelett PUBLIC	PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=1000
#)

target_compile_definitions(st7735 PUBLIC	SPI_TFT_PORT=spi0
											PIN_TFT_CS=17
											PIN_TFT_DC=20
											PIN_TFT_RST=21
											TFT_ENABLE_RED
											TFT_ENABLE_BLACK
											TFT_ENABLE_GREEN
											TFT_ENABLE_GENERIC
											TFT_ENABLE_TEXT
											TFT_ENABLE_RESET
											TFT_ENABLE_SCROLL
											TFT_ENABLE_SHAPES
											TFT_ENABLE_ROTATE
)

target_link_libraries(st7735	hardware_gpio
								hardware_spi
								pico_time
)

target_link_libraries(skelett	hardware_gpio
								hardware_spi
								hardware_timer
								pico_bootsel_via_double_reset
								pico_multicore
								pico_stdio_usb
								pico_stdlib
								pico_time
								pico_util
								st7735
)

pico_add_extra_outputs(skelett)

target_sources(skelett	PUBLIC	source/config.c
								source/debug.c
								source/globals.c
								source/input.c
								source/module1.c
								source/module2.c
								source/skelett.c
)

set_source_files_properties(source/config.c		PROPERTIES COMPILE_DEFINITIONS SRC_FILE_config)
set_source_files_properties(source/debug.c		PROPERTIES COMPILE_DEFINITIONS SRC_FILE_debug)
set_source_files_properties(source/globals.c 	PROPERTIES COMPILE_DEFINITIONS SRC_FILE_globals)
set_source_files_properties(source/input.c		PROPERTIES COMPILE_DEFINITIONS SRC_FILE_input)
set_source_files_properties(source/module1.c 	PROPERTIES COMPILE_DEFINITIONS SRC_FILE_module1)
set_source_files_properties(source/module2.c 	PROPERTIES COMPILE_DEFINITIONS SRC_FILE_module2)

target_include_directories(skelett	BEFORE	PUBLIC
												source
												source/lib-st7735/include
)

target_include_directories(st7735	BEFORE	PUBLIC
												source/lib-st7735/include
)

