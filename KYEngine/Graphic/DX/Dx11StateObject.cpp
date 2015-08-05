#include "stdafx.h"


#include "Dx11StateObject.h"

//{@
#include "Graphic/DX/DX11NameTranslator.h"
//@}

#include "Graphic/Graphic.h"
#include "Graphic/DX/Dx11.h"

#include "Graphic/GraphicDef.h"


namespace KY
{
	bool DX::Dx11RasterizerStateObj::Create(const RasterizerState &state)
	{
		auto nameTrnslor = DX11NameTranslator::Inst();
		D3D11_RASTERIZER_DESC desc = {
			nameTrnslor->ToFillMode(state.fillMode),
			nameTrnslor->ToCullMode(state.cullMode),
			state.frontCCW,			
			state.depthBias,
			state.depthBiasClamp,
			state.slopeScaledDepthBias,
			state.depthClipEnable,
			state.scissorEnable,
			state.multisampleEnable,
			state.antialiasedLineEnable,
		};

		auto device = Graphic::Inst()->GetDx11()->GetDevice();

		return SUCCEEDED(device->CreateRasterizerState(&desc, &mInternalObj));		
	}

	static inline void fill_d3d_rt_blend_desc(const BlendState::RenderTargetBlendDesc &rtDesc, D3D11_RENDER_TARGET_BLEND_DESC &d3dRTDesc)
	{
		auto dx11Trans = DX::DX11NameTranslator::Inst();

		d3dRTDesc.BlendEnable	= rtDesc.blendEnable;
		d3dRTDesc.SrcBlend		= dx11Trans->ToBlendType(rtDesc.clrOpDesc.src);
		d3dRTDesc.DestBlend		= dx11Trans->ToBlendType(rtDesc.clrOpDesc.dst);
		d3dRTDesc.BlendOp		= dx11Trans->ToBlendOperation(rtDesc.clrOpDesc.op);

		d3dRTDesc.SrcBlendAlpha = dx11Trans->ToBlendType(rtDesc.alphaOpDesc.src);
		d3dRTDesc.DestBlendAlpha= dx11Trans->ToBlendType(rtDesc.alphaOpDesc.dst);
		d3dRTDesc.BlendOpAlpha	= dx11Trans->ToBlendOperation(rtDesc.alphaOpDesc.op);

		d3dRTDesc.RenderTargetWriteMask = uint8(dx11Trans->ToColorWriteEnable(rtDesc.renderTargetWriteMask));
	}

	bool DX::Dx11BlendStateObj::Create(const BlendState &state)
	{
		auto device = Graphic::Inst()->GetDx11()->GetDevice();

		D3D11_BLEND_DESC desc;
		desc.AlphaToCoverageEnable = state.alphaToCoverageEnable;
		desc.IndependentBlendEnable = state.independentBlendEnable;

		if (state.independentBlendEnable)
		{
			fill_d3d_rt_blend_desc(state.renderTargetDesc[0], desc.RenderTarget[0]);
		}
		else
		{
			auto itD3DRT = std::begin(desc.RenderTarget);

			std::for_each(std::begin(state.renderTargetDesc), std::end(state.renderTargetDesc),
				[&itD3DRT](const BlendState::RenderTargetBlendDesc &rtDesc){
					fill_d3d_rt_blend_desc(rtDesc, *itD3DRT++);
			});		
		}

		return SUCCEEDED(device->CreateBlendState(&desc, &mInternalObj));		
	}


	bool DX::Dx11DepthStencilStateObj::Create(const DepthStencilState &state)
	{
		auto dx11Trans = DX::DX11NameTranslator::Inst();

		D3D11_DEPTH_STENCIL_DESC desc;
		desc.DepthEnable = state.depthEnable;
		desc.DepthWriteMask = state.enableDepthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = dx11Trans->ToComparisonFunc(state.depthFunc);

		desc.StencilEnable = state.stencilEnable;
		desc.StencilReadMask = state.stencilReadMask;
		desc.StencilWriteMask = state.stencilWriteMask;

		desc.FrontFace.StencilFailOp	= dx11Trans->ToStencialOp(state.frontFaceOp.stencilFailOp);
		desc.FrontFace.StencilDepthFailOp = dx11Trans->ToStencialOp(state.frontFaceOp.stencilDepthFailOp);
		desc.FrontFace.StencilPassOp	= dx11Trans->ToStencialOp(state.frontFaceOp.stencilPassOp);
		desc.FrontFace.StencilFunc = dx11Trans->ToComparisonFunc(state.frontFaceOp.stencilFunc);

		desc.BackFace.StencilFailOp = dx11Trans->ToStencialOp(state.backFaceOp.stencilFailOp);
		desc.BackFace.StencilDepthFailOp = dx11Trans->ToStencialOp(state.backFaceOp.stencilDepthFailOp);
		desc.BackFace.StencilPassOp = dx11Trans->ToStencialOp(state.backFaceOp.stencilPassOp);
		desc.BackFace.StencilFunc = dx11Trans->ToComparisonFunc(state.backFaceOp.stencilFunc);

		auto device = Graphic::Inst()->GetDx11()->GetDevice();
		return SUCCEEDED(device->CreateDepthStencilState(&desc, &mInternalObj));
	}

}