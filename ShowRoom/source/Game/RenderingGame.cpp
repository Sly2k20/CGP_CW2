#include "RenderingGame.h"
#include "GameException.h"
#include "FirstPersonCamera.h"
#include "TriangleDemo.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ModelFromFile.h"

namespace Rendering
{;

	const XMFLOAT4 RenderingGame::BackgroundColor = { 0.0f, 0.0f, 0.2f, 1.0f };

    RenderingGame::RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand)
        : Game(instance, windowClass, windowTitle, showCommand),

        //tutorial 4 (SLY)
        mDirectInput(nullptr),
        mKeyboard(nullptr),
        mMouse(nullptr),
        




        mDemo(nullptr)
    {
        mDepthStencilBufferEnabled = true;
        mMultiSamplingEnabled = true;
    }

    RenderingGame::~RenderingGame()
    {
    }

    void RenderingGame::Initialize()
    {
		
        //tutorial 4 (SLY)

        if (FAILED(DirectInput8Create(mInstance, DIRECTINPUT_VERSION,
            IID_IDirectInput8, (LPVOID*)&mDirectInput, nullptr)))
        {
            throw GameException("DirectInput8Create() failed");
        }
        mKeyboard = new Keyboard(*this, mDirectInput);
        mComponents.push_back(mKeyboard);
        mServices.AddService(Keyboard::TypeIdClass(), mKeyboard);
        mMouse = new Mouse(*this, mDirectInput);
        mComponents.push_back(mMouse);
        mServices.AddService(Mouse::TypeIdClass(), mMouse);

       

        //camera control

        mCamera = new FirstPersonCamera(*this);
        mComponents.push_back(mCamera);
        mServices.AddService(Camera::TypeIdClass(), mCamera);
    
        mDemo = new TriangleDemo(*this, *mCamera);
        mComponents.push_back(mDemo);

        // tutorail 5 (SLY)
        mModel = new ModelFromFile(*this, *mCamera, "Content\\Models\\bench.3ds");
        mModel->SetPosition(-1.57f, -0.0f, -0.0f, 0.005f, 0.0f, 0.6f, 0.0f);
        mComponents.push_back(mModel);

        Game::Initialize();



		mCamera->SetPosition(0.0f, 0.0f, 5.0f);

      


    }

    void RenderingGame::Shutdown()
    {
		DeleteObject(mDemo);
        DeleteObject(mCamera);
        DeleteObject(mKeyboard);
        DeleteObject(mMouse);
        DeleteObject(mDirectInput);
        DeleteObject(mModel);
        Game::Shutdown();
    }

    void RenderingGame::Update(const GameTime &gameTime)
    {

        //add this for the camera
        if (mKeyboard->WasKeyPressedThisFrame(DIK_ESCAPE))
        {
            Exit();
        }

        Game::Update(gameTime);
    }

    void RenderingGame::Draw(const GameTime &gameTime)
    {
        mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&BackgroundColor));
        mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

        Game::Draw(gameTime);
       
        HRESULT hr = mSwapChain->Present(0, 0);
        if (FAILED(hr))
        {
            throw GameException("IDXGISwapChain::Present() failed.", hr);
        }
    }
}