cmake_minimum_required(VERSION 2.8)

project(simul_furuta)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Carica pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Carica Allegro
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
find_package(Allegro REQUIRED)
include_directories(${ALLEGRO_INCLUDE_DIR})

# Carica ptask
add_library(ptask STATIC IMPORTED)
set_property(TARGET ptask APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ptask PROPERTIES
	IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
	IMPORTED_LOCATION_NOCONFIG "${CMAKE_CURRENT_LIST_DIR}/ptask/libptask.a"
)
include_directories("${CMAKE_CURRENT_LIST_DIR}/ptask")

# Compila main.c
add_compile_definitions(ALLEGRO_STATICLINK)
include_directories("${CMAKE_CURRENT_LIST_DIR}/src")
add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_LIST_DIR}/src/main.c")
target_link_libraries(${PROJECT_NAME} Threads::Threads ${ALLEGRO_LIBRARY} m rt ptask)
