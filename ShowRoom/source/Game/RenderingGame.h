#pragma once


#include "Game.h"

using namespace Library;

namespace Library
{
    class FirstPersonCamera;
	class RenderStateHelper;
    
    //tutorial 4 (SLY)
    class Keyboard;
    class Mouse;
}

namespace Rendering
{
    class TriangleDemo;

    class RenderingGame : public Game
    {
    public:
        RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);
        ~RenderingGame();

        virtual void Initialize() override;		
        virtual void Update(const GameTime& gameTime) override;
        virtual void Draw(const GameTime& gameTime) override;

    protected:
        virtual void Shutdown() override;

    private:
		static const XMFLOAT4 BackgroundColor;
        FirstPersonCamera * mCamera;
        TriangleDemo* mDemo;

        //tutorial 4 (SLY)
        LPDIRECTINPUT8 mDirectInput;
        Keyboard* mKeyboard;
        Mouse* mMouse;
    };
}