
if (UNIX)

include(CTest)

add_executable(rand_gen rand_gen_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/Rand_gen.cpp)

target_include_directories(rand_gen PRIVATE ${CMAKE_SOURCE_DIR}/Photon_propagation_backend/includes)

target_compile_options(rand_gen PUBLIC "-O3;-g")

add_test(NAME rand_gen_test COMMAND rand_gen)

endif (UNIX)


