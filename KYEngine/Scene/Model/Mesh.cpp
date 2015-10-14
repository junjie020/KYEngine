#include "stdafx.h"
#include "Mesh.h"

#include "Graphic/RenderOperation.h"

namespace KY
{
	static auto get_semantic_name(const VertexBuffer &vb, const RenderOperation &ro)
	{
		const char* semanticNames[] = 
		{
			"POSITION",
			"NORMAL",
			"TANGENT",
			"BINORMAL",
			"BLENDWEIGHT",
			"BLENDINDICES",
			"COLOR",
			"COLOR1",
			"COLOR2",
			"COLOR3",

			"TEXCOORD",
			"TEXCOORD1",
			"TEXCOORD2",
			"TEXCOORD3",
		};

		const auto& vbis = ro.GetVertexBufferInfos();

		for (const auto& vbi : vbis)
		{
			if (&vb == vbi.mVertexBuf)
			{
				uint32 semanticIdx = 0U;
				const uint32 slotIdx = vbi.mVertexInfo.slotIdx;
				if (SI_Color <= slotIdx && slotIdx < (SI_Color + MAX_SLOT_ELEM_IDX))
					semanticIdx = slotIdx - SI_Color;

				if (SI_Texcoord <= slotIdx && slotIdx < (SI_Texcoord + MAX_SLOT_ELEM_IDX))
					semanticIdx = slotIdx - SI_Texcoord;

				return std::make_pair(semanticNames[slotIdx], semanticIdx);
			}
				
		}

		return std::make_pair("", uint32(-1));
	}
	void MeshRenderOperationHelper::Update()
	{
		for (const auto& m : mVBs)
		{
			//const auto& bufParam = m.GetBufferParam();

			//const auto semanticInfo = get_semantic_name(m, mRO);
 		//	const InputElemDesc elem = 
 		//	{
			//	semanticInfo.first,
			//	semanticInfo.second,


 		//	};

		}
	}

	void Mesh::Update()
	{
		mRenderHelper.Update();
	}
}