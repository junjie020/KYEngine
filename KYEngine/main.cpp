////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System/System.h"
#include "System/SampleTest.h"

#include "Scene/Actor.h"
#include "Scene/Scene.h"

#include "Graphic/Graphic.h"

#include "Graphic/Resource/Buffer/VertexBuffer.h"
#include "Graphic/Resource/Shader/Shader.h"
#include "Graphic/Resource/Shader/ShaderResourceView.h"
#include "Graphic/Resource/State/StateHelper.h"
#include "Graphic/Resource/Buffer/ConstBufferDef.h"
#include "Graphic/Resource/ResourceManager.h"
#include "Graphic/Resource/Texture/TextureAssertLoader.h"
#include "Graphic/Resource/Texture/Texture.h"
#include "Graphic/Resource/Texture/Texture.inl"
#include "Graphic/Resource/Texture/TextureTypeTraits.inl"

#include "Graphic/Render/RenderOperation.h"
#include "Graphic/Render/RenderBatch.h"

#include "Graphic/Render/Viewport.h"



#include "Math/Vector4.h"
#include "Math/Color.h"
#include "Math/Color.inl"
#include "Math/Matrix.h"
#include "Math/MathUtils.h"

#include "DebugUtils/TraceUtils.h"

#include "Common/FileSystem/FileSystem.h"

#include "Scene/Model/Model.h"

using namespace KY;

class ModelTest : public KY::SampleTest
{
public:
	bool Init(RenderTarget *rt) override
	{
		auto scene = System::Inst()->GetScene();
		
		mModel = new Model(scene->GetRootActor());
		scene->AddActor(mModel);

		auto modelPath = FileSystem::Inst()->FindFromSubPath("model");

		return mModel->InitFromFile(rt, modelPath / fs::path("test_cube_text.x"));
	}
private:
	Model *mModel;
};

class SimpleTriangleTest : public KY::SampleTest
{
public:
	SimpleTriangleTest() : mActor(nullptr){

	}
	~SimpleTriangleTest(){}
	bool Init(RenderTarget *) override
	{		
		auto scene = System::Inst()->GetScene();
		BOOST_ASSERT(nullptr == mActor);
		mActor = new TriangleTexActor;
		scene->AddActor(mActor);

		//Vec4f v(100.f, 0.f, 900.f, 1.0f);


		//Mat4x4F matView = ConstructViewMatrix(Vec4f(0.0f, 0.0f, -100.f, 1.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
		//Mat4x4F matProj = ConstructPrespectiveMatrix(MathUtils::ToRadian(45.f), 1.0f, 1.0f, 1000.f);

		//Mat4x4F matViewProj = matView * matProj;

		//Vec4f vView = v * matView;
		//Vec4f vViewProj0 = vView * matProj;

		//Vec4f vViewProj1 = v * matViewProj;

		//vViewProj1 /= vViewProj1.w;



		//Mat4x4F mm1 = ConstructOrthoMatrix(100.f, 100.f, 1.f, 1000.f);



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


	class TriangleTexActor : public KY::Actor
	{
	public:
		TriangleTexActor()
			: KY::Actor(nullptr)
			, mVertexShader(nullptr)
			, mPixelShader(nullptr)
			, mDynConstBuffer(ResourceType::Const)
			, mSRV(nullptr)
			, mTex2D(nullptr)
		{
			InitBufferData();
			InitShadersAndInputLayout();

			InitPSShaderResourceView();
			InitState();
		}

		void InitBufferData()
		{
			struct VertexColor {
				glm::vec4	v;
				glm::vec2	uv;
			};

			VertexColor vc[] = {
				glm::vec4(-1.0f,	-1.0f, 99.99f, 1.0f),	glm::vec2(0.f, 1.f),
				glm::vec4(0.0f,		1.0f,	99.99f, 1.0f),	glm::vec2(.5f, 0.f),
				glm::vec4(1.0f,		-1.0f,	99.99f, 1.0f),	glm::vec2(1.f, 1.f)
			};

			BufferParam param;
			param.type = ResourceType::Const;
			param.access = ResourceCPUAccess::None;
			param.usage = ResourceUsage::Immutable;
			param.sizeInBytes = sizeof(vc);

			ResourceData data = { reinterpret_cast<const uint8*>(vc), 0, 0 };

			if (mBuffer.Init(param, data))
			{
				BufferInfo info = { 0, sizeof(VertexColor), 0 };
				mRO.AddVertexBuffer(&mBuffer, info);
				DrawVertexBufferParam pp = { 3, 0 };
				mRO.SetVertexDrawInfo(pp);

				mRO.SetPrimitiveType(PrimitiveType::PT_TriList);
			}
		}

		bool InitPSShaderResourceView()
		{
			BOOST_ASSERT(nullptr == mTex2D);
			BOOST_ASSERT(nullptr == mSRV);

			mTex2D = new KY::Texture2D;

			//{@
			const uint32 width = 2, height = 2;

			//@}
			std::vector<uint8> rawBuffer(width * height * 4); // 2 x 2 rgba texture

			Color32B *clr = (Color32B*)(&rawBuffer[0]);

			*clr++ = Color32B::Red;
			*clr++ = Color32B::Green;
			*clr++ = Color32B::Blue;
			*clr++ = Color32B::Black;

			TextureMemoryLoader loader(width, height, 1, TF_R8G8B8A8_UNORM, std::move(rawBuffer));
			TextureParam tp = { 1, 1, BF_ShaderResource, ResourceCPUAccess::None, ResourceUsage::Default, TF_R8G8B8A8_UNORM, {1, 0},  0};
			BOOST_VERIFY(mTex2D->Init(tp, &loader));

			mSRV = new KY::ShaderResourceView;
			SRVParam p = { TF_R8G8B8A8_UNORM, SRVParam::SRVType::Tex2D, {0, 1} };
			mSRV->Init(p, mTex2D);

			mRO.SetPSShaderResourceView(0, mSRV);
			return true;
		}

		bool InitShadersAndInputLayout()
		{
			mVertexShader = ResourceManager::Inst()->FindAddShader("ScreenTexQuad.vs");
			BOOST_ASSERT(mVertexShader && mVertexShader->IsValid());
			mRO.SetShader(mVertexShader, KY::ShaderType::ShdrT_Vertex);

			mPixelShader = ResourceManager::Inst()->FindAddShader("ScreenTexQuad.ps");

			BOOST_ASSERT(mPixelShader && mPixelShader->IsValid());
			mRO.SetShader(mPixelShader, KY::ShaderType::ShdrT_Pixel);

			InputElemDesc desc[] =
			{
				{ "POSITION",	0, TF_R32G32B32A32_FLOAT,	0, 0,					0, false },
				{ "TEXCOORD",	0, TF_R32G32_FLOAT,			0, sizeof(float) * 4,	0, false },
			};

			for (auto beg = std::begin(desc); beg != std::end(desc); ++beg)
			{
				mInputLayout.AddElem(*beg);
			}

			if (!mInputLayout.Init(*mVertexShader))
			{
				DebugOutline("create input layout failed!");
				return false;
			}

			mRO.SetInputLayout(&mInputLayout);


			//////////////////////////////////////////////////////////////////////////
			BufferParam constParam;
			constParam.type = ResourceType::Const;
			constParam.access = ResourceCPUAccess::Write;
			constParam.usage = ResourceUsage::Dynamic;
			constParam.sizeInBytes = sizeof(GlobalDynamicConstBuffer);

			ResourceData constData = { nullptr, 0, 0 };
			if (mDynConstBuffer.Init(constParam, constData))
			{
				mVertexShader->AddConstBuffer(0, &mDynConstBuffer);
			}

			return true;
		}

		bool InitState()
		{
			KY::RasterizerState rsState;
			rsState.cullMode = CullMode::Back;
			rsState.depthClipEnable = false;

			KY::DepthStencilState dsState;
			dsState.depthEnable = false;

			KY::BlendState blendState;

			mStates.InitPipelineStateObj(&rsState, &dsState, &blendState, &mRO);

			KY::SamplerState ss;
			mStates.InitPSSamplerStateObjs(0, 1, &ss, &mRO);

			return true;
		}

		virtual void UpdateImpl(Camera *camera)
		{
			Actor::UpdateImpl(camera);
			ResourceMapParam param = { 0, ResourceMapType::ResMT_WriteDiscard, 0, 0, 0, false };
			if (mDynConstBuffer.Map(param))
			{
				GlobalDynamicConstBuffer dynBuffer;
				dynBuffer.matrix.world = mat4x4_utils::INDENTIFY;
				//mMatBuffer.matView = KY::ConstructViewMatrix(Vec4f(0.0f, 0.0f, 100.f, 1.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f));

				//const Size2U dim = Graphic::Inst()->GetBackBufferSize();
				//mMatBuffer.matProj = KY::ConstructPrespectiveMatrix(MathUtils::ToRadian(45.f), float(dim.x) / dim.y, 0.1f, 1000.f);

				dynBuffer.matrix.view = camera->GetViewMat();
				dynBuffer.matrix.proj = camera->GetProjMat();
				dynBuffer.eyePos = camera->GetPostion();

				BOOST_ASSERT(param.mapData.data);
				BOOST_ASSERT(param.mapData.rowPitch != 0);
				BOOST_ASSERT(param.mapData.rowPitch >= sizeof(dynBuffer));
				memcpy(param.mapData.data, &dynBuffer, sizeof(dynBuffer));
				mDynConstBuffer.UnMap(param.subRes);
			}
			else
			{
				KY::DebugOutline("map const buffer failed!");
			}
		}

		virtual void ExtractRenderInfo(RenderCommandQueue &q) override
		{
			q.Push(&mRO);
			//KY::Graphic::Inst()->AddRenderOperation(&mRO);
		}

	private:
		KY::RenderOperation mRO;
		//{@
		KY::VertexBuffer		mBuffer;		
		KY::Buffer				mDynConstBuffer;
		//@}

		KY::InputLayout		mInputLayout;
		KY::Shader			*mVertexShader;
		KY::Shader			*mPixelShader;

		KY::ShaderResourceView *mSRV;
		KY::Texture2D* mTex2D;

		KY::StateHelper		mStates;
	};

	class TriangleActor : public KY::Actor
	{
	public:
		TriangleActor() 
			: Actor(nullptr)
			, mVertexShader(nullptr)
			, mPixelShader(nullptr)
			, mDynConstBuffer(ResourceType::Const)
		{
			InitBufferData();
			InitShadersAndInputLayout();
			InitState();
		}

		~TriangleActor(){}

		void InitBufferData()
		{
			struct VertexColor{
				glm::vec4	v;
				Color32B	c;
			};

			VertexColor vc[] = {
				glm::vec4(-1.0f,	-1.0f, 99.99f, 1.0f),	Color32B::Red,
				glm::vec4(0.0f,		1.0f,	99.99f, 1.0f),	Color32B::Blue,
				glm::vec4(1.0f,		-1.0f,	99.99f, 1.0f),	Color32B::Green,
			};

			BufferParam param;
			param.type = ResourceType::Vertex;
			param.access = ResourceCPUAccess::None;
			param.usage = ResourceUsage::Immutable;			
			param.sizeInBytes = sizeof(vc);

			ResourceData data = { reinterpret_cast<const uint8*>(vc), 0, 0 };

			if (mBuffer.Init(param, data))
			{
				BufferInfo info = { 0, sizeof(VertexColor), 0 };
				mRO.AddVertexBuffer(&mBuffer, info);
				DrawVertexBufferParam pp = { 3, 0 };
				mRO.SetVertexDrawInfo(pp);

				mRO.SetPrimitiveType(PrimitiveType::PT_TriList);
			}
		}

		bool InitShadersAndInputLayout()
		{
			mVertexShader = ResourceManager::Inst()->FindAddShader("ScreenQuad.vs");
			BOOST_ASSERT(mVertexShader && mVertexShader->IsValid());
			mRO.SetShader(mVertexShader, KY::ShaderType::ShdrT_Vertex);

			mPixelShader = ResourceManager::Inst()->FindAddShader("ScreenQuad.ps");				

			BOOST_ASSERT(mPixelShader && mPixelShader->IsValid());
			mRO.SetShader(mPixelShader, KY::ShaderType::ShdrT_Pixel);

			InputElemDesc desc[] = 
			{
				{ "POSITION",	0, TF_R32G32B32A32_FLOAT,	0, 0,					0, false },
				{ "COLOR",		0, TF_R8G8B8A8_UNORM,		0, sizeof(float) * 4,	0, false },				
			};

			for (auto beg = std::begin(desc); beg != std::end(desc); ++beg)
			{
				mInputLayout.AddElem(*beg);
			}

			if (!mInputLayout.Init(*mVertexShader))
			{
				DebugOutline("create input layout failed!");
				return false;
			}

			mRO.SetInputLayout(&mInputLayout);


			//////////////////////////////////////////////////////////////////////////
			BufferParam constParam;
			constParam.type = ResourceType::Const;
			constParam.access = ResourceCPUAccess::Write;
			constParam.usage = ResourceUsage::Dynamic;
			constParam.sizeInBytes = sizeof(GlobalDynamicConstBuffer);

			ResourceData constData = { nullptr, 0, 0 };
			if (mDynConstBuffer.Init(constParam, constData))
			{
				mVertexShader->AddConstBuffer(0, &mDynConstBuffer);
			}

			return true;
		}

		bool InitState()
		{
			KY::RasterizerState rsState;
			rsState.cullMode = CullMode::Back;
			rsState.depthClipEnable = false;

			KY::DepthStencilState dsState;
			dsState.depthEnable = false;

			KY::BlendState blendState;
			
			mStates.InitPipelineStateObj(&rsState, &dsState, &blendState, &mRO);

			return true;
		}

		virtual void UpdateImpl(Camera *camera) override
		{
			Actor::UpdateImpl(camera);
			ResourceMapParam param = { 0, ResourceMapType::ResMT_WriteDiscard, 0, 0, 0, false };
			if (mDynConstBuffer.Map(param))
			{
				GlobalDynamicConstBuffer dynBuffer;
				dynBuffer.matrix.world = mat4x4_utils::INDENTIFY;
				//mMatBuffer.matView = KY::ConstructViewMatrix(Vec4f(0.0f, 0.0f, 100.f, 1.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f));

				//const Size2U dim = Graphic::Inst()->GetBackBufferSize();
				//mMatBuffer.matProj = KY::ConstructPrespectiveMatrix(MathUtils::ToRadian(45.f), float(dim.x) / dim.y, 0.1f, 1000.f);

				dynBuffer.matrix.view = camera->GetViewMat();
				dynBuffer.matrix.proj = camera->GetProjMat();

				BOOST_ASSERT(param.mapData.data);
				BOOST_ASSERT(param.mapData.rowPitch != 0);
				BOOST_ASSERT(param.mapData.rowPitch >= sizeof(dynBuffer));
				memcpy(param.mapData.data, &dynBuffer, sizeof(dynBuffer));
				mDynConstBuffer.UnMap(param.subRes);
			}
			else
			{
				KY::DebugOutline("map const buffer failed!");
			}			
		}

		virtual void ExtractRenderInfo(RenderCommandQueue &q) override
		{
			q.Push(&mRO);
			//KY::Graphic::Inst()->AddRenderOperation(&mRO);
		}
	private:
		KY::RenderOperation mRO;
		KY::RenderBatch	mRenderBatch;
		//{@
		KY::VertexBuffer		mBuffer;		
		KY::Buffer				mDynConstBuffer;
		//@}
		
		KY::InputLayout		mInputLayout;
		KY::Shader			*mVertexShader;
		KY::Shader			*mPixelShader;

		KY::StateHelper		mStates;
	};

private:	
	KY::Actor *mActor;
};

#include "Common/FileSystem/FileSystem.h"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*pScmdline*/, int /*iCmdshow*/)
#elif defined(__APPLE__)
int MainEntry()
#else
#error define a not valid platform
#endif //_WIN32
{
//	iCmdshow;
//	pScmdline;
//	hPrevInstance;
//	hInstance;

	// Create the system object.
	KY::FileSystem::Create();
	auto curPath = fs::current_path();
	KY::FileSystem::Inst()->SetRootPath(curPath);
	KY::FileSystem::Inst()->ReigstPath("shader", KY::FileSystem::Inst()->RootPath() / fs::path("Resource/Shader"));
	KY::FileSystem::Inst()->ReigstPath("model", KY::FileSystem::Inst()->RootPath() / fs::path("Resource/Model"));

	auto system = KY::System::Create();

	Size2U dim(0, 0);
	if (system->Initialize(dim, true))
	{
		auto vp = system->GetMainVP();

		//SimpleTriangleTest tt;		

		ModelTest tt;
		auto camera = vp->GetCamera();

		const glm::vec4 cameraPos = Vec4f(5.f, 5.f, 10.f, 1.f);
		camera->SetPosition(cameraPos);
		auto direct = glm::normalize(Vec4f(0.f, 0.f, 0.f, 1.f) - cameraPos);
		camera->SetDirection(direct);
		
		tt.Init(vp);
		system->Run();
	}
	system->Shutdown();

	KY::System::Destroy();

	return 0;
}