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

##################Common##################
append_src_files(COMMON_SRC "Common" 
	BaseTypes.h 
	CommonUtils.h 
	HashImpl.h 
	Singleton.h 
	FileSystem.h FileSystem.cpp)
source_group("Common" FILES ${COMMON_SRC})

##################DebugUtils##################
append_src_files(DEBUGUTILS_SRC "DebugUtils"
	TraceUtils.h TraceUtils.cpp)

source_group("DebugUtils" FILES ${DEBUGUTILS_SRC})

##################Graphic##################
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
					
source_group("Graphic" FILES ${GRAPHIC_SRC})

append_src_files(GRAPHIC_METAL "Graphic/Metal" 
	Metal.h Metal.cpp)
					
source_group("Graphic\\Metal" FILES ${GRAPHIC_METAL})

append_src_files(GRAPHIC_RESOURCE "Graphic/Resource" 
	Buffer.h Buffer.cpp
	IndexBuffer.h IndexBuffer.cpp
	Resource.h Resource.cpp
	Shader.h Shader.cpp
	StateHelper.h StateHelper.cpp
	StateObject.h StateObject.inl StateObject.cpp
	Texture.h Texture.cpp
	VertexBuffer.h VertexBuffer.cpp)
					
source_group("Graphic\\Resource" FILES ${GRAPHIC_RESOURCE})

##################Input##################
append_src_files(INPUT_SRC "Input" 
	Input.h Input.cpp)
					
source_group("Input" FILES ${INPUT_SRC})

##################Input##################
append_src_files(INPUT_SRC "Input" 
	Input.h Input.cpp)
					
source_group("Input" FILES ${INPUT_SRC})

##################Math##################
append_src_files(MATH_SRC "Math" 
	Color.h Color.inl Color.cpp
	MathUtils.h MathUtils.cpp
	Matrix.h Matrix.inl Matrix.cpp
	Plane.h Plane.cpp
	Quaternion.h Quaternion.cpp
	Rectangle.h
	Vector2.h
	Vector4.h Vector4.cpp
	)
					
source_group("Math" FILES ${MATH_SRC})

##################Platform##################
append_src_files(PLATFORM_SRC "Platform" 
	Win32DefHeader.h)
					
source_group("Platform" FILES ${PLATFORM_SRC})

##################Scene##################
append_src_files(SCENE_SRC "Scene" 
	Actor.h Actor.cpp
	Scene.h Scene.cpp)
					
source_group("Scene" FILES ${SCENE_SRC})


append_src_files(SCENE_MODEL_SRC "Scene/Model" 
	Model.h Model.cpp
	Mesh.h Mesh.cpp
	MeshImporter.h MeshImporter.cpp)
					
source_group("Scene\\Model" FILES ${SCENE_MODEL_SRC})

append_src_files(SCENE_MODEL_ASSIMP_SRC "Scene/Model/Assimp" 
	AssimpMeshImporter.h AssimpMeshImporter.cpp
	AssimpResourceManager.h AssimpResourceManager.cpp)
					
source_group("Scene\\Model\\Assimp" FILES ${SCENE_MODEL_ASSIMP_SRC})

##################Scene##################
append_src_files(SYSTEM_SRC "System" 
	System.h System.cpp
	SampleTest.h SampleTest.cpp)
					
source_group("System" FILES ${SYSTEM_SRC})


#########################################

#+++++++++++++++++++++++++++++++++++++++
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra -Werror")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra -Werror -Wno-missing-field-initializers")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
endif()
#+++++++++++++++++++++++++++++++++++++++
		
set(SRC_FILES
	main.cpp stdafx.cpp
	${COMMON_SRC}
	${DEBUGUTILS_SRC}
	${GRAPHIC_SRC} ${GRAPHIC_METAL} ${GRAPHIC_RESOURCE}
	${INPUT_SRC}
	${MATH_SRC}
	${PLATFORM_SRC}
	${SCENE_SRC} ${SCENE_MODEL_SRC} ${SCENE_MODEL_ASSIMP_SRC}
	${SYSTEM_SRC}
	)

#KYEngine will be a shared library for example to use, for simple, I just make it as a executable file right now
add_executable(${PROJECT_NAME} ${SRC_FILES})

#we need to add the external lib of assimp for osx
#target_link_libraries(${PROJECT_NAME} assimp)