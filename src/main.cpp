#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

const int HEIGHT = 350;
const int WIDTH  = 250;

ULONG_PTR gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;
Image* img;
GUID dimension = FrameDimensionTime;
UINT frameCount;
UINT currentFrame = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Alyacup";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOPMOST, // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Alyacup",    // Window text
        WS_POPUP | WS_VISIBLE,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        nullptr,       // Parent window
        nullptr,       // Menu
        hInstance,  // Instance handle
        nullptr        // Additional application data
        );

    if (hwnd == nullptr)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            img = new Image(L"../../images/teto/teto_2.gif");
            frameCount = img->GetFrameCount(&dimension);
            if (frameCount == 0) {
                frameCount  = 1;
            }
            SetLayeredWindowAttributes(hwnd, 0, 76, LWA_ALPHA);
            MoveWindow(hwnd, 800, 270, WIDTH, HEIGHT, TRUE);
            SetTimer(hwnd, 1, 100, nullptr);
            return 0;
        }

        case WM_DESTROY:
        {
            KillTimer(hwnd, 1);
            delete img;
            GdiplusShutdown(gdiplusToken);
            PostQuitMessage(0);
            return 0;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            Graphics graphics(hdc);

            Bitmap buffer(WIDTH, HEIGHT);
            Graphics g_buf(&buffer);

            g_buf.Clear(Color::Black);
            g_buf.DrawImage(img, Rect(0, 0, WIDTH, HEIGHT));

            graphics.DrawImage(&buffer, 0, 0);
            EndPaint(hwnd, &ps);
            return 0;
        }


        case WM_TIMER:
        {
            if (wParam == 1) {
                currentFrame = (currentFrame + 1) % frameCount;
                img->SelectActiveFrame(&FrameDimensionTime, currentFrame);

                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}