#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <shobjidl.h>
#include <gdiplus.h>
#include "../include/imageController.h"
#include "../include/utils.h"

using namespace Gdiplus;
using namespace alyacup;

const int HEIGHT = 350;
const int WIDTH  = 250;

ULONG_PTR gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;

tools::ImageController* imgController;
RECT rc;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
    const wchar_t CLASS_NAME[]  = L"Alyacup";
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOPMOST,    // Optional window styles.
        CLASS_NAME,                       // Window class
        L"Alyacup",                       // Window text
        WS_POPUP | WS_VISIBLE,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // Size and position
        nullptr,       // Parent window
        nullptr,       // Menu
        hInstance,     // Instance handle
        nullptr        // Additional application data
        );

    if (hwnd == nullptr)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

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
            imgController = new tools::ImageController(L"../../images/other/girl_2.gif");  // ../../images/other/girl_1.gif
            SetLayeredWindowAttributes(hwnd, 0, 200, LWA_ALPHA);
            MoveWindow(hwnd, 800, 270, imgController->w, imgController->h,TRUE);
            SetTimer(hwnd, 1, 100, nullptr);
            return 0;
        }

        case WM_DESTROY:
        {
            KillTimer(hwnd, 1);
            delete imgController;
            GdiplusShutdown(gdiplusToken);
            PostQuitMessage(0);
            return 0;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            Graphics graphics(hdc);
            GetClientRect(hwnd, &rc);
            Bitmap buffer(rc.right, rc.bottom);
            Graphics g_buf(&buffer);

            g_buf.Clear(Color::Black);
            g_buf.DrawImage(imgController->getImage(), Rect(0, 0, rc.right, rc.bottom));

            graphics.DrawImage(&buffer, 0, 0);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_TIMER:
        {
            if (wParam == 1) {
                imgController->nextFrame();
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }

        case WM_LBUTTONDOWN:
        {
            SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
            return 0;
        }

        case WM_CONTEXTMENU:
        {
            onContextMenu(hwnd, lParam);
            return 0;
        }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void onContextMenu(HWND hwnd, LPARAM lParam) {
    HMENU hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING, tools::OPEN_ID, L"open");
    AppendMenu(hMenu, MF_STRING, tools::RESIZE_ID, L"resize");
    AppendMenu(hMenu, MF_STRING, tools::EXIT_ID, L"exit");
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    UINT option = TrackPopupMenu(hMenu, TPM_RETURNCMD, x, y, 0, hwnd, nullptr);
    if (option == tools::EXIT_ID)
    {
        PostQuitMessage(0);
    }
    else if (option == tools::RESIZE_ID)
    {
        DWORD style = GetWindowLongPtr(hwnd, GWL_STYLE);
        style ^= WS_THICKFRAME;
        SetWindowLongPtr(hwnd, GWL_STYLE, style);
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
    else if (option == tools::OPEN_ID) {
        PCWSTR path = onDialogMenu();
        delete imgController;
        imgController = new tools::ImageController(path);
    }
    DestroyMenu(hMenu);
}


PCWSTR onDialogMenu() {  // sample from winapi github
    PCWSTR path = L"";
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
    COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog *pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem *pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        path = pszFilePath;
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
    return path;
}