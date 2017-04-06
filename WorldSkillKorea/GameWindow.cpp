#include "GameWindow.h"
#include "GameConstants.h"

GameWindow::GameWindow(HINSTANCE instanceHandle, int show) :
	m_WindowHandle(nullptr),
	m_ShouldClose(false)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = instanceHandle;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"GameWindow";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wc))
	{
		throw "Register Window Class Failed";
	}

	m_WindowHandle = CreateWindow(L"GameWindow", L"Game", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		GameConstants::width, GameConstants::height, 0, 0, instanceHandle, 0);
	if (m_WindowHandle == 0)
	{
		throw "Create Window Failed";
	}

	ShowWindow(m_WindowHandle, show);
	UpdateWindow(m_WindowHandle);
}

GameWindow::~GameWindow()
{
	DestroyWindow(m_WindowHandle);
}

void GameWindow::pollEvents()
{
	MSG msg = { 0 };

	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			m_ShouldClose = true;
		}
	}
}

bool GameWindow::windowShouldClose() const
{
	return m_ShouldClose;
}

HWND GameWindow::getWindowHandle() const
{
	return m_WindowHandle;
}

LRESULT CALLBACK WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(windowHandle, message, wParam, lParam);
	}
}