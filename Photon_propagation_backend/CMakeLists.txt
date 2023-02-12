
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


# Configure 
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/Config.hpp.in 
	${CMAKE_CURRENT_SOURCE_DIR}/includes/Config.hpp)

# Add all source and headers
add_executable(${PROJECT_NAME} 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Input.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Launch_photon.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Layer.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Output.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Photon.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Rand_gen.cpp src/State.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

# Add json library
add_library(Json_lib INTERFACE)
target_include_directories(Json_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

target_link_libraries(${PROJECT_NAME} Json_lib)

# Specify C++ standart
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


