cmake_minimum_required(VERSION 2.8)

project(KYEngine)

if (NOT DEFINED ENV{BOOST_DIR})
	message(fatalerror "you need to define a env var, which contain the boost dir")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
					${CMAKE_CURRENT_SOURCE_DIR}/ImpLib/includes
					${BOOST_DIR})
					
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/ImpLib/lib)

function(append_src_files name_list local_dir)
	math(EXPR idx 2)
	set(temp_list "")
	
	while(idx LESS ${ARGC})
		list(GET ARGV ${idx} arg)
		list(APPEND temp_list ${local_dir}/${arg})
		math(EXPR idx ${idx}+1)
	endwhile()
	set(${name_list} ${temp_list} PARENT_SCOPE)
	
endfunction(append_src_files)

append_src_files(COMMON_HEADERS "Common" 
	BaseTypes.h 
	CommonUtils.h 
	HashImpl.h 
	Singleton.h 
	FileSystem.h)
	
append_src_files(COMMON_SRC "Common" FileSystem.cpp)

source_group("Common\\Headers" FILES ${COMMON_HEADERS})
source_group("Common\\Sources" FILES ${COMMON_SRC})
		
set(SRC_FILES main.cpp stdafx.cpp ${COMMON_HEADERS} ${COMMON_SRC})	

#KYEngine will be a shared library for example to use, for simple, I just make it as a executable file right now
add_executable(${PROJECT_NAME} ${SRC_FILES})

#we need to add the external lib of assimp for osx
#target_link_libraries(${PROJECT_NAME} assimp)