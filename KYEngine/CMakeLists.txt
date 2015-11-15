cmake_minimum_required(VERSION 2.8)

project(KYEngine)

if (NOT DEFINED ENV{BOOST_DIR})
	message(fatalerror "you need to define a env var, which contain the boost dir")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
					${CMAKE_CURRENT_SOURCE_DIR}/ImpLib/includes
					${BOOST_DIR})
					
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/ImpLib/lib)

function(append_src_files name_list local_dir arg)
	foreach(name ${ARGN})
		if ($name NOTEQUAL ${name_list} AND $name NOTEQUAL ${local_dir})
			${name_list} = ${name_list} ${local_dir}/${name}
		endif()
	endforeach()
endfunciton(append_src_files)

append_src_files(

set(SRC_FILES main.cpp stdafx.cpp)

append_src_files(SRC_FILES "Common" BaseType.h CommonUtils.h)

message("===the src files : " ${SRC_FILES})
	

#KYEngine will be a shared library for example to use, for simple, I just make it as a executable file right now
add_executable(${PROJECT_NAME} ${SRC_FILES})

#we need to add the external lib of assimp for osx
#target_link_libraries(${PROJECT_NAME} assimp)