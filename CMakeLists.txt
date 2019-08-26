cmake_minimum_required(VERSION 3.10)
project(pgufjf)

include_directories(src)
add_subdirectory(utils/pugixml-1.9)

find_package(OpenMP)
if(OpenMP_FOUND)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	file(GLOB_RECURSE FONTES "src/*.cpp")
	add_executable(pgufjf ${FONTES})    
	target_link_libraries(pgufjf pugixml)
 
else()
  message("ERROR: OpenMP nao encontrado.")
endif()

