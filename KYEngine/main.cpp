////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System/System.h"
#include "System/SampleTest.h"

#include "Scene/Actor.h"
#include "Scene/Scene.h"

#include "Graphic/Resource/VertexBuffer.h"
#include "Graphic/RenderOperation.h"
#include "Graphic/Resource/Shader.h"

#include "Graphic/Graphic.h"

#include "Graphic/Resource/StateObject.h"
#include "Graphic/Resource/StateObject.inl"
#include "Graphic/Viewport.h"

#include "Math/Vector4.h"
#include "Math/Color.h"
#include "Math/Color.inl"

#include "DebugUtils/TraceUtils.h"

#include "Common/FileSystem.h"

using namespace KY;
class SimpleTriangleTest : public KY::SampleTest
{
public:
	SimpleTriangleTest() : mActor(nullptr){

	}
	~SimpleTriangleTest(){}
	bool Init() override
	{		
		auto scene = System::Inst()->GetScene();
		BOOST_ASSERT(nullptr == mActor);
		mActor = new TriangleActor;
		scene->AddActor(mActor);

		return true;
	}

private:
	//class TriangleActor11 : public KY::Actor
	//{
	//public:
	//	TriangleActor11() : Actor(nullptr)
	//	{
	//		mDevice = KY::Graphic::Inst()->GetDx11()->GetDevice();
	//		mContext = KY::Graphic::Inst()->GetDx11()->GetDeviceContext();

	//		InitBuffer();
	//		InitShaderAndInputLayout();
	//	}

	//	void InitBuffer()
	//	{
	//		Vec4f vv[] =
	//		{
	//			Vec4f(-1.0f, -1.0f, 0.0f, 1.0f),
	//			Vec4f(0.0f, 1.0f, 0.0f, 1.0f),
	//			Vec4f(1.0f, -1.0f, 0.0f, 1.0f),
	//		};

	//		D3D11_BUFFER_DESC desc = { 0 };
	//		desc.Usage = D3D11_USAGE_IMMUTABLE;
	//		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//		desc.ByteWidth = sizeof(vv);
	//		D3D11_SUBRESOURCE_DATA data = { vv, 0, 0 };
	//		if (mDevice->CreateBuffer(&desc, &data, &mVertexBuffer))
	//		{

	//		}
	//	}

	//	void InitShaderAndInputLayout()
	//	{
	//		auto shdrPath = KY::FileSystem::Inst()->FindFromSubPath("shader");
	//		
	//		ID3DBlob *pVSCode = nullptr;
	//		ID3DBlob *pError = nullptr;

	//		
	//		D3DCompileFromFile(L"Resource/Shader/ScreenQuad.vs", nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_DEBUG, 0, &pVSCode, &pError);

	//		if (pError)
	//		{
	//			OutputDebugStringA((const char*)pError->GetBufferPointer());
	//			return ;
	//		}

	//		if (FAILED(mDevice->CreateVertexShader(pVSCode->GetBufferPointer(), pVSCode->GetBufferSize(), nullptr, &mVertexShader)))
	//		{
	//			return;
	//		}
	//		
	//		ID3DBlob *pPSCode = nullptr;
	//		D3DCompileFromFile(L"Resource/Shader/ScreenQuad.ps", nullptr, nullptr, "main", "ps_5_0", D3DCOMPILE_DEBUG, 0, &pPSCode, &pError);

	//		if (pError)
	//		{
	//			OutputDebugStringA((const char*)pError->GetBufferPointer());
	//			return;
	//		}

	//		if (FAILED(mDevice->CreatePixelShader(pPSCode->GetBufferPointer(), pPSCode->GetBufferSize(), nullptr, &mPixelShader)))
	//		{
	//			return;
	//		}

	//		D3D11_INPUT_ELEMENT_DESC desc[] = 
	//		{
	//			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//		};

	//		if (FAILED(mDevice->CreateInputLayout(desc, _countof(desc), pVSCode->GetBufferPointer(), pVSCode->GetBufferSize(), &mInputLayout)))
	//		{
	//			return;
	//		}
	//	}

	//	void UpdateImpl()
	//	{
	//		auto mDx = Graphic::Inst()->GetDx11();
	//		if (mDx->Prepare())
	//		{
	//			
	//			mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//			UINT stride = sizeof(Vec4f);
	//			UINT offset = 0;
	//			mContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//			mContext->IASetInputLayout(mInputLayout);

	//			mContext->VSSetShader(mVertexShader, nullptr, 0);


	//			D3D11_VIEWPORT vp = { 0.0f, 0.0f, 800, 600, 0.0f, 1.0f };
	//			mContext->RSSetViewports(1, &vp);

	//			mContext->PSSetShader(mPixelShader, nullptr, 0);

	//			mContext->Draw(3, 0);

	//			mDx->Swap();
	//		}
	//	}

	//private:
	//	//{@
	//	ID3D11Device *mDevice;
	//	ID3D11DeviceContext *mContext;
	//	//@}

	//	//{@
	//	ID3D11VertexShader *mVertexShader;
	//	ID3D11PixelShader *mPixelShader;

	//	ID3D11Buffer		*mVertexBuffer;
	//	ID3D11InputLayout	*mInputLayout;
	//	//@}




	//};

	class TriangleActor : public KY::Actor
	{
	public:
		TriangleActor() 
			: Actor(nullptr)
		{
			InitBufferData();
			InitShadersAndInputLayout();
			InitState();
		}

		~TriangleActor(){}

		void InitBufferData()
		{
			struct VertexColor{
				Vec4f		v;
				//Color32B	c;
			};

			VertexColor vc[] = {
				Vec4f(-1.0f, -1.0f, 0.0f, 1.0f),
				Vec4f(0.0f, 1.0f, 0.0f, 1.0f),
				Vec4f(1.0f, -1.0f, 0.0f, 1.0f),
				//{ Vec4f(-0.5f, 0.0f, 0.0f, 1.0f), Color32B::Red },
				//{ Vec4f(0.0f, 0.5f, 0.0f, 1.0f), Color32B::Green },
				//{ Vec4f(5.0f, 0.0f, 0.0f, 1.0f), Color32B::Blue },
				//{ Vec4f(5, 8.0f, 0.0f, 1.0f), Color32B::Red },
				//{ Vec4f(1, 0.5f, 0.0f, 1.0f), Color32B::Green },
				//{ Vec4f(1, 0.0f, 0.0f, 1.0f), Color32B::Blue },

			};

			BufferParam param;
			param.type = BT_Vertex;
			param.access = BA_None;
			param.usage = RU_Immutable;
			param.elemInBytes = sizeof(VertexColor);
			param.sizeInBytes = sizeof(vc);

			ResourceData data = { reinterpret_cast<const uint8*>(vc), 0, 0 };

			if (mBuffer.Create(param, data))
			{
				BufferInfo info = { 0, sizeof(VertexColor), 0 };
				mRO.SetVertexBuffer(&mBuffer, info);
				DrawVertexBufferParam pp = { 3, 0 };
				mRO.SetVertexDrawInfo(pp);

				mRO.SetPrimitiveType(PT_TriList);
			}
		}

		bool InitShadersAndInputLayout()
		{
			auto shdrPath = KY::FileSystem::Inst()->FindFromSubPath("shader");

			if (!mVertexShader.InitFromFile(ShdrT_Vertex, shdrPath / fs::path("ScreenQuad.vs")))
				return false;

			
			BOOST_ASSERT(mVertexShader.IsValid());
			mRO.SetShader(&mVertexShader, KY::ShdrT_Vertex);
			

			if (!mPixelShader.InitFromFile(KY::ShdrT_Pixel, shdrPath / fs::path("ScreenQuad.ps")))
				return false;

			BOOST_ASSERT(mVertexShader.IsValid());
			mRO.SetShader(&mPixelShader, KY::ShdrT_Pixel);


			InputElemDesc desc[] = 
			{
				{ "POSITION",	0, TF_R32G32B32A32_FLOAT,	0, 0,					0, false },
				//{ "COLOR",		0, TF_R8G8B8A8_UNORM,		0, sizeof(float) * 4,	0, false },
			};

			for (auto beg = std::begin(desc); beg != std::end(desc); ++beg)
			{
				mInputLayout.AddElem(*beg);
			}

			if (!mInputLayout.Create(mVertexShader))
			{
				DebugOutline("create input layout failed!");
				return false;
			}

			mRO.SetInputLayout(&mInputLayout);

			return true;
		}

		bool InitState()
		{
			KY::RasterizerState rsState;
			rsState.cullMode = CM_None;
			mRSObj = new KY::RasterizerStateObj;
			if (!mRSObj->CreateObj(rsState))
			{
				KY::DebugOutline("create rs state failed!");
				delete mRSObj;
				mRSObj = nullptr;
			}
			mRO.SetRasterizerStateObj(mRSObj);

			KY::DepthStencilState dsState;
			dsState.depthEnable = false;
			mDSObj = new KY::DepthStencilStateObj;		
			if (!mDSObj->CreateObj(dsState))
			{
				KY::DebugOutline("create depth stencil state failed!");
				delete mDSObj;
				mDSObj = nullptr;
			}

			mRO.SetDepthStencilStateObj(mDSObj);

			KY::BlendState blendState;
			mBlendObj = new KY::BlendStateObj;
			if (!mBlendObj->CreateObj(blendState))
			{
				KY::DebugOutline("create blend state failed!");
				delete mBlendObj;
				mBlendObj = nullptr;
			}

			mRO.SetBlendStateObj(mBlendObj);

			const auto backBufferDim = Graphic::Inst()->GetBackBufferSize();
			mViewport.mRect = RectU(0, 0, backBufferDim.w, backBufferDim.h);
			mViewport.mDepthRange = Range2F(0, 1.0f);
			mRO.SetViewport(&mViewport);

			return true;
		}

		virtual void UpdateImpl()
		{
			KY::Graphic::Inst()->AddRenderOperation(&mRO);			
		}
	private:
		KY::RenderOperation mRO;
		KY::VertexBuffer	mBuffer;
		KY::InputLayout		mInputLayout;
		KY::Shader			mVertexShader;
		KY::Shader			mPixelShader;

		//{@	state
		KY::RasterizerStateObj*		mRSObj;
		KY::DepthStencilStateObj*	mDSObj;
		KY::BlendStateObj*			mBlendObj;
		//@}

		KY::Viewport		mViewport;
	};

private:	
	KY::Actor *mActor;
};

#include "Common/FileSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	iCmdshow;
	pScmdline;
	hPrevInstance;
	hInstance;

	// Create the system object.
	KY::FileSystem::Create();
	auto curPath = fs::current_path<fs::path>();
	KY::FileSystem::Inst()->SetRootPath(curPath);
	KY::FileSystem::Inst()->ReigstPath("shader", KY::FileSystem::Inst()->RootPath() / fs::path("Resource/Shader"));

	auto system = KY::System::Create();

	Size2U dim(0, 0);
	if (system->Initialize(dim, true))
	{
		SimpleTriangleTest tt;
		tt.Init();
		system->Run();
	}
	system->Shutdown();

	KY::System::Destroy();

	return 0;
}