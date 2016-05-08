#ifndef _DX11NAMETRANSLATOR_H_
#define _DX11NAMETRANSLATOR_H_

#include "Common/Singleton.h"
#include "Common/CommonUtils.h"

#include "Graphic/GraphicDef.h"
#include <d3d11.h>
namespace KY
{
	namespace DX
	{
		class DX11NameTranslator : public Singleton<DX11NameTranslator>
		{
		public:
			inline D3D11_USAGE ToUsage(ResourceUsage usage) const;
			inline DXGI_FORMAT ToDXGI_FORMAT(TexFormat ft) const;
			inline D3D11_BIND_FLAG ToBingFlag(ResourceType type) const;
			inline D3D11_BIND_FLAG ToBingFlag(BindFlag bind) const;

			inline D3D11_CPU_ACCESS_FLAG ToCPUAccessFlag(ResourceCPUAccess access) const;

			inline D3D11_FILTER ToFilterType(FilterType ft) const;
			inline D3D11_TEXTURE_ADDRESS_MODE ToAddressMode(AddressMode am) const;
			
			inline D3D11_FILL_MODE ToFillMode(FillMode fm) const;
			inline D3D11_CULL_MODE ToCullMode(CullMode cm) const;

			inline D3D11_COMPARISON_FUNC ToComparisonFunc(CompareFunc cf) const;

			inline D3D11_STENCIL_OP ToStencialOp(StencilOperation sop) const;
			inline D3D11_BLEND ToBlendType(BlendType type) const;
			inline D3D11_BLEND_OP ToBlendOperation(BlendOperation o) const;

			inline D3D11_COLOR_WRITE_ENABLE ToColorWriteEnable(RenderTargetColorWirteMask mask) const;

			inline D3D_FEATURE_LEVEL ToFeatureLevel(FeatureLevel level) const;
			inline FeatureLevel	FromeFeatureLevel(D3D_FEATURE_LEVEL level) const;

			inline D3D11_MAP TopMap(ResourceMapType type) const;

			D3D11_PRIMITIVE_TOPOLOGY ToPrimitiveTopology(PrimitiveType type) const;
		};

		inline D3D11_USAGE DX11NameTranslator::ToUsage(ResourceUsage usage) const
		{
			const D3D11_USAGE usages[] = { D3D11_USAGE_DEFAULT, D3D11_USAGE_IMMUTABLE, D3D11_USAGE_DYNAMIC, D3D11_USAGE_STAGING };

			BOOST_ASSERT(COUNT_OF(usages) > uint32(usage));

			return usages[usage];			
		}

		inline DXGI_FORMAT DX11NameTranslator::ToDXGI_FORMAT(TexFormat tf) const
		{
			return DXGI_FORMAT(tf);
		}

		inline D3D11_BIND_FLAG DX11NameTranslator::ToBingFlag(ResourceType type) const
		{
			const D3D11_BIND_FLAG flags[] = 
			{ 
				D3D11_BIND_VERTEX_BUFFER, D3D11_BIND_INDEX_BUFFER, D3D11_BIND_CONSTANT_BUFFER, 
			};
			BOOST_ASSERT(COUNT_OF(flags) > uint32(type));
			return flags[type];
		}

		inline D3D11_BIND_FLAG DX11NameTranslator::ToBingFlag(BindFlag bind) const
		{
			return D3D11_BIND_FLAG(bind);
		}
		inline D3D11_CPU_ACCESS_FLAG DX11NameTranslator::ToCPUAccessFlag(ResourceCPUAccess access) const
		{
			uint16 flag(0);
			if (QueryBit(BA_Read, access))
				flag |= D3D11_CPU_ACCESS_READ;
			if (QueryBit(BA_Write, access))
				flag |= D3D11_CPU_ACCESS_WRITE;

			return D3D11_CPU_ACCESS_FLAG(flag);
		}


		inline D3D11_FILTER DX11NameTranslator::ToFilterType(FilterType ft) const
		{
			return D3D11_FILTER(ft);
		}

		inline D3D11_TEXTURE_ADDRESS_MODE DX11NameTranslator::ToAddressMode(AddressMode am) const
		{
			return D3D11_TEXTURE_ADDRESS_MODE(am);
		}

		inline D3D11_FILL_MODE DX11NameTranslator::ToFillMode(FillMode fm) const
		{
			const D3D11_FILL_MODE modes[] = { D3D11_FILL_WIREFRAME, D3D11_FILL_SOLID, };

			BOOST_ASSERT(COUNT_OF(modes) > uint32(fm));

			return modes[fm];
		}

		inline D3D11_CULL_MODE DX11NameTranslator::ToCullMode(CullMode cm) const
		{
			const D3D11_CULL_MODE modes[] = { D3D11_CULL_NONE, D3D11_CULL_FRONT, D3D11_CULL_BACK };
			BOOST_ASSERT(COUNT_OF(modes) > uint32(cm));

			return modes[cm];
		}

		inline D3D11_COMPARISON_FUNC DX11NameTranslator::ToComparisonFunc(CompareFunc cf) const
		{
			const D3D11_COMPARISON_FUNC funcs[] =
			{
				D3D11_COMPARISON_NEVER,
				D3D11_COMPARISON_LESS,
				D3D11_COMPARISON_EQUAL,
				D3D11_COMPARISON_LESS_EQUAL,
				D3D11_COMPARISON_GREATER,
				D3D11_COMPARISON_NOT_EQUAL,
				D3D11_COMPARISON_GREATER_EQUAL,
				D3D11_COMPARISON_ALWAYS,
			};

			BOOST_ASSERT(COUNT_OF(funcs) > uint32(cf));

			return funcs[cf];

		}

		inline D3D11_STENCIL_OP DX11NameTranslator::ToStencialOp(StencilOperation op) const
		{
			const D3D11_STENCIL_OP ops[] =
			{
				D3D11_STENCIL_OP_KEEP,
				D3D11_STENCIL_OP_ZERO,
				D3D11_STENCIL_OP_REPLACE,
				D3D11_STENCIL_OP_INCR_SAT,
				D3D11_STENCIL_OP_DECR_SAT,
				D3D11_STENCIL_OP_INVERT,
				D3D11_STENCIL_OP_INCR,
				D3D11_STENCIL_OP_DECR,
			};

			BOOST_ASSERT(COUNT_OF(ops) > uint32(op));

			return ops[op];
		}

		inline D3D11_BLEND DX11NameTranslator::ToBlendType(BlendType type) const
		{
			const D3D11_BLEND blends[] =
			{
				D3D11_BLEND_ZERO,
				D3D11_BLEND_ONE,
				D3D11_BLEND_SRC_COLOR,
				D3D11_BLEND_INV_SRC_COLOR,
				D3D11_BLEND_SRC_ALPHA,
				D3D11_BLEND_INV_SRC_ALPHA,
				D3D11_BLEND_DEST_ALPHA,
				D3D11_BLEND_INV_DEST_ALPHA,
				D3D11_BLEND_DEST_COLOR,
				D3D11_BLEND_INV_DEST_COLOR,
				D3D11_BLEND_SRC_ALPHA_SAT,
				D3D11_BLEND_BLEND_FACTOR,
				D3D11_BLEND_INV_BLEND_FACTOR,
				D3D11_BLEND_SRC1_COLOR,
				D3D11_BLEND_INV_SRC1_COLOR,
				D3D11_BLEND_SRC1_ALPHA,
				D3D11_BLEND_INV_SRC1_ALPHA,
			};
			BOOST_ASSERT(COUNT_OF(blends) > uint32(type));

			return blends[type];
		}

		inline D3D11_BLEND_OP DX11NameTranslator::ToBlendOperation(BlendOperation op) const
		{
			const D3D11_BLEND_OP ops[] =
			{
				D3D11_BLEND_OP_ADD,
				D3D11_BLEND_OP_SUBTRACT,
				D3D11_BLEND_OP_REV_SUBTRACT,
				D3D11_BLEND_OP_MIN,
				D3D11_BLEND_OP_MAX,
			};

			BOOST_ASSERT(COUNT_OF(ops) > uint32(op));

			return ops[op];
		}

		inline D3D11_COLOR_WRITE_ENABLE DX11NameTranslator::ToColorWriteEnable(RenderTargetColorWirteMask mask) const
		{
			if (mask == RTCW_All)
				return D3D11_COLOR_WRITE_ENABLE_ALL;

			uint8 d3dmask = 0;
			if (QueryBit(RTCW_Red, mask))
				d3dmask |= D3D11_COLOR_WRITE_ENABLE_RED;

			if (QueryBit(RTCW_Green, mask))
				d3dmask |= D3D11_COLOR_WRITE_ENABLE_GREEN;

			if (QueryBit(RTCW_Blue, mask))
				d3dmask |= D3D11_COLOR_WRITE_ENABLE_BLUE;

			if (QueryBit(RTCW_Alpha, mask))
				d3dmask |= D3D11_COLOR_WRITE_ENABLE_ALPHA;

			return D3D11_COLOR_WRITE_ENABLE(d3dmask);

		}

		inline D3D_FEATURE_LEVEL DX11NameTranslator::ToFeatureLevel(FeatureLevel level) const
		{
			const D3D_FEATURE_LEVEL levels[] =
			{
				D3D_FEATURE_LEVEL_9_1, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_11_1,
			};

			BOOST_ASSERT(COUNT_OF(levels) > uint32(level));
			return levels[level];
		}
		inline FeatureLevel	DX11NameTranslator::FromeFeatureLevel(D3D_FEATURE_LEVEL level) const
		{
			switch (level)
			{
			case D3D_FEATURE_LEVEL_11_1: return FL_11_1;
			case D3D_FEATURE_LEVEL_11_0: return FL_11_0;
			case D3D_FEATURE_LEVEL_10_1: return FL_10_1;
			case D3D_FEATURE_LEVEL_10_0: return FL_10_0;
			case D3D_FEATURE_LEVEL_9_3:	 return FL_9_3;
			case D3D_FEATURE_LEVEL_9_2:	 return FL_9_2;
			case D3D_FEATURE_LEVEL_9_1:	 return FL_9_1;
			default:	return FL_Unknown;
			}
		}

		inline D3D11_MAP DX11NameTranslator::TopMap(ResourceMapType type) const
		{
			D3D11_MAP maps[] = {
				D3D11_MAP_READ,
				D3D11_MAP_WRITE,
				D3D11_MAP_READ_WRITE,
				D3D11_MAP_WRITE_DISCARD,
				D3D11_MAP_WRITE_NO_OVERWRITE, };
			BOOST_ASSERT(COUNT_OF(maps) > uint32(type));

			return maps[type];
		}
	}

}
#endif // _DX11NAMETRANSLATOR_H_