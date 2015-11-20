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

append_src_files(DEBUG_HEADERS "DebugUtils" TraceUtils.h)
append_src_files(DEBUG_SRC "DebugUtils" TraceUtils.cpp)

source_group("DebugUtils\\Headers" ${DEBUG_HEADERS})
source_group("DebugUtils\\Sources" ${DEBUG_SRC})

append_src_files(GRAPHIC_METAL_SRC "Graphic/Metal" Metal.h Metal.cpp)
source_group("Graphic\\Metal" ${GRAPHIC_METAL_SRC})

append_src_files(GRAPHIC_RESOURCE_SRC "Graphic/Resource" 
			Buffer.h Buffer.cpp
			IndexBuffer.h IndexBuffer.cpp
			Resource.h Resource.cpp
			Shader.h Shader.cpp
			StateHelper.h StateHelper.cpp
			StateObject.h StateObject.inl StateObject.cpp
			Texture.h Texture.cpp 
			VertexBuffer.h VertexBuffer.cpp)
source_group("Graphic\\Resource" ${GRAPHIC_RESOURCE_SRC})

append_src_files(GRAPHIC_SRC "Graphic" 
			Camera.h Camera.cpp
			Frustum.h Frustum.cpp
			Graphic.h Graphic.cpp
			GraphicDef.h
			IRenderable.h
			PipelineStage.h PipelineStage.cpp
			RenderCommandQueue.h RenderCommandQueue.cpp
			RenderOperation.h RenderOperation.cpp
			SpaceNode.h SpaceNode.cpp
			Viewport.h Viewport.cpp)
			
source_group("Graphic" ${GRAPHIC_SRC})

		
set(SRC_FILES main.cpp stdafx.cpp 
	${COMMON_HEADERS} ${COMMON_SRC}
	${DEBUG_HEADERS} ${DEBUG_SRC}
	${GRAPHIC_METAL_SRC} ${GRAPHIC_RESOURCE_SRC} ${GRAPHIC_SRC})	

#KYEngine will be a shared library for example to use, for simple, I just make it as a executable file right now
add_executable(${PROJECT_NAME} ${SRC_FILES})

#we need to add the external lib of assimp for osx
#target_link_libraries(${PROJECT_NAME} assimp)