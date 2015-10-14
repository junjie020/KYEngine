#include "stdafx.h"
#include "AssimpMeshImporter.h"

#include "AssimpResourceManager.h"
#include "Scene/Model/Mesh.h"
#include "Scene/Model/Model.h"

#include "Graphic/Resource/VertexBuffer.h"
#include "Graphic/Resource/IndexBuffer.h"


//{@	assimp lib
#include "assimp/scene.h"
//@}

namespace KY
{
	AssimpMeshImporter::AssimpMeshImporter(Model *m)
		: MeshImporter(m)
	{
		
	}

	AssimpMeshImporter::~AssimpMeshImporter()
	{

	}

	static inline size_t get_slot_elem_size(SlotIndex idx)
	{
		size_t ss[] = 
		{
			sizeof(float) * 3,
			sizeof(float) * 4,
			sizeof(float) * 3,
			sizeof(float) * 3,
			sizeof(float) * 3,
			sizeof(float) * 2,
		};

		BOOST_ASSERT(_countof(ss) > idx);
		return ss[idx];
	}

	static inline uint32 get_primitive_vertex_num(aiMesh *mesh)
	{
		return mesh->mPrimitiveTypes;
	}

	static inline PrimitiveType get_primitive_type(aiMesh *mesh)
	{
		PrimitiveType pts[] = {PT_Point, PT_LineList, PT_TriList};

		BOOST_ASSERT(_countof(pts) > mesh->mPrimitiveTypes);
		return pts[mesh->mPrimitiveTypes];
	}

	template<typename Type>
	static inline void fill_index_buffer(const aiMesh *mesh, std::vector<uint32> &buf)
	{
		auto iBuf = 0U;

		Type *dstBuf = reinterpret_cast<Type*>(&buf[0]);
		for (auto iFace = 0U; iFace < mesh->mNumFaces; ++iFace)
		{
			auto face = mesh->mFaces[iFace];

			for (auto iIdx = 0U; iIdx < face.mNumIndices; ++iIdx)
			{
				dstBuf[iBuf++] = static_cast<Type>(face.mIndices[iIdx]);
			}
		}
	}

	template<class SrcBufferType>
	static void add_vb_info(SlotIndex slotIdx, const SrcBufferType* src, uint32 numElems, MeshRenderOperationHelper &meshHelper)
	{
		auto& VBs = meshHelper.GetVBs();

		VBs.push_back(VertexBuffer());
		auto& vb = VBs.back();

		const auto stride = get_slot_elem_size(slotIdx);
		BufferParam param = { ResT_Vertex, BA_None, RU_Immutable, numElems * stride, 0 };

		ResourceData data = { reinterpret_cast<const uint8 *>(src), 0, 0 };
		vb.Create(param, data);

		BufferInfo posInfo = { 0U, stride, slotIdx };
		meshHelper.GetRO().AddVertexBuffer(&vb, posInfo);
	}

	static uint32 face_vertex_num(const aiMesh *mesh)
	{
		switch (mesh->mPrimitiveTypes)
		{
		case aiPrimitiveType_POINT:
			return 1;
		case aiPrimitiveType_LINE:
			return 2;
		case aiPrimitiveType_TRIANGLE:
			return 3;
		case aiPrimitiveType_POLYGON:
			BOOST_ASSERT(false && "not support polygon!");
			return 4;
		default:
			return 0;
		}
	}

	static void extract_render_info(const aiScene *scene, const aiNode *node, Model *model)
	{
		for (auto iMesh = 0U; iMesh < node->mNumMeshes; ++iMesh)
		{
			auto meshIdx = node->mMeshes[iMesh];

			auto mesh = scene->mMeshes[meshIdx];

			auto& renderMeshVec = model->GetMeshes();
			auto renderMesh = new Mesh;
			renderMeshVec.push_back(renderMesh);

			auto &renderHelper = renderMesh->GetRenderHelper();

			add_vb_info(SI_Position, mesh->mVertices, mesh->mNumVertices, renderHelper);

			if (mesh->HasNormals())
				add_vb_info(SI_Normal, mesh->mNormals, mesh->mNumVertices, renderHelper);

			if (mesh->HasTangentsAndBitangents())
			{
				add_vb_info(SI_Tangent, mesh->mTangents, mesh->mNumVertices, renderHelper);
				add_vb_info(SI_Binormal, mesh->mBitangents, mesh->mNumVertices, renderHelper);
			}

			for (auto iC = 0U; iC < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++iC)
			{
				if (mesh->HasVertexColors(iC))
					add_vb_info(static_cast<SlotIndex>(SI_Color + iC), mesh->mColors[iC], mesh->mNumVertices, renderHelper);
			}


			for (auto iT = 0U; iT < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++iT)
			{
				if (mesh->HasTextureCoords(iT))
					add_vb_info(static_cast<SlotIndex>(SI_Texcoord + iT), mesh->mTextureCoords[iT], mesh->mNumVertices, renderHelper);
			}
		
			const uint32 idxCount = mesh->mNumFaces * face_vertex_num(mesh);

			if (idxCount != mesh->mNumVertices)
			{
				auto& ib = renderHelper.GetIB();

				const uint32 elemSize = idxCount < 65536 ? sizeof(uint16) : sizeof(uint32);
				const uint32 sizeInBytes = elemSize * idxCount;
				BufferParam ibParam = { ResT_Index, BA_None, RU_Immutable, sizeInBytes, 0};	

				std::vector<uint32>	ibData(sizeInBytes / sizeof(uint32));

				if (elemSize == sizeof(uint16))
					fill_index_buffer<uint16>(mesh, ibData);
				else
					fill_index_buffer<uint32>(mesh, ibData);

				ResourceData ibResData = {reinterpret_cast<const uint8*>(&ibData[0]), 0, 0};

				ib.Create(ibParam, ibResData);

				BufferInfo ibInfo = {0, elemSize, 0};
				renderHelper.GetRO().SetIndexBuffer(&ib, ibInfo);
			}
		}

		for (auto iChild = 0U; iChild < node->mNumChildren; ++iChild)
			extract_render_info(scene, node->mChildren[iChild], model);
	}

	bool AssimpMeshImporter::Import(const fs::path &filename)
	{
		auto scene = AssimpResourceManager::Inst()->FindRes(filename);

		if (nullptr != scene)
		{
			BOOST_ASSERT(m_Model);

			extract_render_info(scene, scene->mRootNode, m_Model);
			return true;
		}

		return false;
	}

}