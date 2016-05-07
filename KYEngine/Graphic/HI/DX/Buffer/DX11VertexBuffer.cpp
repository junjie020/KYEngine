#include "stdafx.h"
#include "DX11VertexBuffer.h"

#include "Graphic/Graphic.h"
#include "DebugUtils/TraceUtils.h"

#include "Graphic/HI/DX/Dx11.h"
#include "Graphic/HI/DX/DX11NameTranslator.h"

#include "Common/CommonUtils.h"

namespace KY
{
	namespace DX
	{
		DX11VertexBuffer::DX11VertexBuffer(const BufferParam &param, const ResourceData &resData)
			: DX11Buffer(param, resData)
		{
			
		}

		DX::DX11VertexBuffer::~DX11VertexBuffer()
		{

		}
	}
}