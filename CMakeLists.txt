cmake_minimum_required(VERSION 2.8)

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_C_COMPILER "arm-vita-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-vita-eabi-g++")

project(Test)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3 -Wno-unused-variable -Wno-unused-but-set-variable -Wno-format -Wno-strict-aliasing -Wno-attributes -std=gnu99")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

include_directories(
	~/taiHEN/
)

link_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	~/taiHEN/taihen-libs/
)

if (NOT ${RELEASE})
  add_definitions(-DENABLE_LOGGING)
endif()

add_executable(user.elf
	user.c
	font.c
	threads.c
	blit.c
)

target_link_libraries(user.elf
  	gcc
	taihen_stub
	ScePower_stub 
	SceRtc_stub
	SceDisplay_stub
	SceKernelThreadMgr_stub
	SceLibKernel_stub
	SceSysmem_stub
	SceLibc_stub
	SceIoFilemgr_stub
)


add_custom_target(test.suprx ALL
	COMMAND vita-elf-create -e ${CMAKE_SOURCE_DIR}/test.yml user.elf user.velf ~/taiHEN/taihen.json
	COMMAND vita-make-fself user.velf test.suprx
)
add_dependencies(test.suprx user.elf)
