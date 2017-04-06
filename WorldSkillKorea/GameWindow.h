#pragma once
#include <Windows.h>

const class GameWindow
{
public:
	GameWindow() = delete;
	GameWindow(GameWindow&) = delete;
	GameWindow(HINSTANCE instanceHandle, int show);
	~GameWindow();

	void pollEvents();
	bool windowShouldClose() const;
	HWND getWindowHandle() const;
private:
	HWND m_WindowHandle;
	bool m_ShouldClose;
};

LRESULT CALLBACK WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);