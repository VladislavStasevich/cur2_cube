// cube.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "cube.h"

#include "polygon.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND windowHandle;                              // window handle
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
CONST INT TIMER_ID_PRIMARY = 1;
BOOL DEBUG_DRAW = FALSE;
INT windowWidth = 800;
INT windowHeight = 600;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID                Render();


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CUBE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CUBE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CUBE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0; //MAKEINTRESOURCEW(IDC_CUBE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   windowHandle = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!windowHandle)
   {
      return FALSE;
   }

   ShowWindow(windowHandle, nCmdShow);
   UpdateWindow(windowHandle);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
HBITMAP hbmpWindow;
HBITMAP hbmpMemory = NULL;
HDC hdcMem;

void FreeMemoryDC() 
{
    SelectObject(hdcMem, NULL);
    DeleteObject(hbmpMemory);
    DeleteDC(hdcMem);
}

void MakeMemoryDC(HDC hdc, int width, int height) 
{
    hdcMem = CreateCompatibleDC(hdc);
    hbmpMemory = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, hbmpMemory);
}

void ClearMemoryDC(HWND hWnd)
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    SelectObject(hdcMem, GetStockObject(WHITE_BRUSH));
    Rectangle(hdcMem, 0, 0, rect.right, rect.bottom);
}

void DrawMemoryDC() 
{
    RECT rect;
    GetClientRect(windowHandle, &rect);
    HDC hdc = GetDC(windowHandle);
    BitBlt(hdc, 0, 0, rect.right, rect.right, hdcMem, 0, 0, SRCCOPY);
    ReleaseDC(windowHandle, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
            case POPUP_EXIT:
                DestroyWindow(hWnd);
                break;
            case POPUP_OPT:
                break;
            case POPUP_DEBUG_DRAW:
                DEBUG_DRAW = !DEBUG_DRAW;
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            BitBlt(hdc, 0, 0, ps.rcPaint.right, ps.rcPaint.right, hdcMem, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_SIZE:
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            windowWidth = rect.right / 2;
            windowHeight = rect.bottom / 2;
        }
        break;

    case WM_DESTROY:
        KillTimer(hWnd, TIMER_ID_PRIMARY);
        FreeMemoryDC();
        PostQuitMessage(0);
        break;

    case WM_CREATE:
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            HDC hdc = GetDC(hWnd);
            // TODO: Get native monitor resolution
            MakeMemoryDC(hdc, 1920, 1080);
            ClearMemoryDC(hWnd);
            ReleaseDC(hWnd, hdc);

            SetTimer(hWnd, TIMER_ID_PRIMARY, 30, NULL);
        }
        break;

    case WM_TIMER:
        Render();
        break;

    case WM_RBUTTONDOWN:
        {
            HMENU hPopupMenu = CreatePopupMenu();
            InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, POPUP_EXIT, TEXT("Выход"));
            InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, POPUP_OPT, TEXT("Опций"));
            InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, POPUP_DEBUG_DRAW, TEXT("Отладочная отрисока"));
            SetForegroundWindow(windowHandle);
            POINT p;
            GetCursorPos(&p);
            TrackPopupMenu(hPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, p.x, p.y, 0, windowHandle, NULL);
            DestroyMenu(hPopupMenu);
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void draw_poly(int x, int y) 
{
    cube::Polygon        poly;
    cube::Matrix         matRotX;
    cube::Matrix         matRotY;
    cube::Matrix         matTrans;
    cube::Matrix         matTransform;
    cube::Matrix         matProjection;
    static float         s_fTheta = 0.0f;

    s_fTheta += 0.1f;

    matRotX.SetRotationX(s_fTheta);
    matRotY.SetRotationY(s_fTheta);

    matTrans.SetTranslation((float)x, (float)y, 0);
    matProjection.SetProjection(500.f);

    matTransform = matTrans * matRotY * matRotX;

    poly.SetIndexBuffer();
    poly.SetVertexBuffer();
    poly.Transform(matTransform);

    poly.Projection(matProjection);
    poly.ApplyViewport(windowWidth, windowHeight);
    poly.Render(hdcMem);
    if (DEBUG_DRAW) {
        poly.DebugRender(hdcMem);
    }
}

VOID Render() 
{
    ClearMemoryDC(windowHandle);

    draw_poly(0, 0);

    DrawMemoryDC();
}
