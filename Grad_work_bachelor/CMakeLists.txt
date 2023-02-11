
cmake_minimum_required(VERSION 3.1)

project(Monte-Carlo-simulation-of-light-propagation_backend VERSION 0.2)


add_executable(Photon_propagation_backend src/Input.cpp src/Launch_photon.cpp src/Layer.cpp src/Output.cpp 
	src/Photon.cpp src/Rand_gen.cpp src/State.cpp src/main.cpp)

target_include_directories(Photon_propagation_backend PUBLIC includes)

target_include_directories(Photon_propagation_backend PUBLIC third_party)

target_compile_features(Photon_propagation_backend PUBLIC cxx_std_20)
