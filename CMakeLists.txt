cmake_minimum_required(VERSION 2.8)

project(simul_furuta)

set(CMAKE_C_FLAGS "-Wall")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
find_package(Allegro REQUIRED)
include_directories(${ALLEGRO_INCLUDE_DIR})

add_library(ptask STATIC IMPORTED)
set_property(TARGET ptask APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ptask PROPERTIES
	IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
	IMPORTED_LOCATION_NOCONFIG "${CMAKE_MODULE_PATH}/ptask/libptask.a"
)
include_directories("${CMAKE_MODULE_PATH}/ptask")

file(GLOB SRC
	"${CMAKE_MODULE_PATH}/src/*.h"
	"${CMAKE_MODULE_PATH}/src/*.c"
	"${CMAKE_MODULE_PATH}/src/*.cpp"
)
include_directories("${CMAKE_MODULE_PATH}/src")

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} Threads::Threads ${ALLEGRO_LIBRARY} m rt ptask)
