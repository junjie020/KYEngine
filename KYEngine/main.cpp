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


#include <d3d11.h>

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
	class TriangleActor11 : public KY::Actor
	{
	public:
		TriangleActor11() : Actor(nullptr)
		{
			mDevice = Graphic::Inst()->GetDx11()->GetDevice();
			mContext = Graphic::Inst()->GetDx11()->GetDeviceContext();

			InitBuffer();
			InitShaderAndInputLayout();
		}

		void InitBuffer()
		{

			D3D11_BUFFER_DESC desc;
			desc
		}

		void InitShaderAndInputLayout()
		{

		}

		void UpdateImpl()
		{

		}

	private:
		//{@
		ID3D11Device *mDevice;
		ID3D11DeviceContext *mContext;
		//@}

		//{@
		ID3D11VertexShader *mVertexShader;
		ID3D11PixelShader *mPixelShader;

		ID3D11Buffer		*mVertexBuffer;
		ID3D11InputLayout	*mInputLayout;
		//@}




	};

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
				Color32B	c;
			};

			VertexColor vc[] = {
				{ Vec4f(-0.5f, 0.0f, 0.0f, 1.0f), Color32B::Red },
				{ Vec4f(0.0f, 0.5f, 0.0f, 1.0f), Color32B::Green },
				{ Vec4f(5.0f, 0.0f, 0.0f, 1.0f), Color32B::Blue },
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
				{ "COLOR",		0, TF_R8G8B8A8_UNORM,		0, sizeof(float) * 4,	0, false },
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