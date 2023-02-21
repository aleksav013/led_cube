cmake_minimum_required(VERSION 3.12)

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(led_cube C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_EXAMPLES_PATH $(PROJECT_SOURCE_DIR))

# Initalise the SDK
pico_sdk_init()

if (TARGET tinyusb_device)
	add_executable(led_cube
	        src/init.c
	        src/draw.c
	        src/tests.c
	        src/main.c
	        )

	# pull in common dependencies
	target_link_libraries(led_cube
		pico_stdlib
		pico_multicore
		)

	# enable usb output, disable uart output
	pico_enable_stdio_usb(led_cube 1)
	pico_enable_stdio_uart(led_cube 0)

	# create map/bin/hex file etc.
	pico_add_extra_outputs(led_cube)

	elseif(PICO_ON_DEVICE)
	    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()
