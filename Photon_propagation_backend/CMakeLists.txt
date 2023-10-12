
cmake_minimum_required(VERSION 3.5)

project(Photon_propagation_backend VERSION 0.2)

# Set Build type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Specify Plathorm type 
if (WIN32)
	set(IS_WINDOWS true)
else (WIN32)
	set(IS_WINDOWS false)
endif (WIN32)

if (UNIX)
	set(IS_UNIX true)
else (UNIX)
	set(IS_UNIX false)
endif (UNIX)

# add tests subdirectory
add_subdirectory(tests)


# Configure 
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/Config.hpp.in 
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Config.hpp)

# Add all source and headers
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/includes/Array_2D.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Defines.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Input.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Launch_photon.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Layer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Output_data.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Output_to_console.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Output_to_file.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Photon.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Rand_gen.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/includes/State.hpp)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/Input.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Launch_photon.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Layer.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Output_to_console.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Output_to_file.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Photon.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Rand_gen.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/State.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

if (UNIX)
	set(DEBUG_OPTS "-g;-O0;-fsanitize=thread")
	set(RELEASE_OPTS "-flto=auto")
	target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTS}>")
	target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTS}>")
	target_link_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTS}>")
	target_link_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTS}>")
endif (UNIX)


# Add json library
add_library(Json_lib INTERFACE)
target_include_directories(Json_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

target_link_libraries(${PROJECT_NAME} Json_lib)

# Specify C++ standart
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


