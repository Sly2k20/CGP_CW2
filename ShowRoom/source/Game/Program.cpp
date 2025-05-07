#include <memory>
#include "GameException.h"
#include "RenderingGame.h"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

using namespace Library;
using namespace Rendering;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    std::unique_ptr<RenderingGame> game(new RenderingGame(instance, L"RenderingClass", L"Real-Time 3D Rendering", showCommand));

    //window

    HWND hwnd = game->WindowHandle();

    // Resize the window to 1280x720 (SLY)
    SetWindowPos(hwnd, HWND_TOP, 0, 0, 1280, 720, SWP_NOMOVE);



    try
    {
        game->Run();
    }
    catch (GameException ex)
    {
        MessageBox(game->WindowHandle(), ex.whatw().c_str(), game->WindowTitle().c_str(), MB_ABORTRETRYIGNORE);
    }

    return 0;
}