#pragma once
#include <dinput.h>
#include <Windows.h>
#include <xnamath.h>
#define DIMOUSE_LEFT 0
#define DIMOUSE_RIGHT 1
#define DIMOUSE_MIDDLE 2

const class Input
{
public:
	Input() = delete;
	Input(Input&) = delete;
	Input(HINSTANCE instanceHandle, HWND windowHandle);
	~Input();

	void pollInput();
	
	bool getKeyPressed(int key) const;
	bool getKeyReleased(int key) const;
	bool getKeyRepeated(int key) const;
	bool getKey(int key) const;

	bool getMousePressed(int button) const;
	bool getMouseReleased(int button) const;
	bool getMouseRepeated(int button) const;
	bool getMouse(int button) const;

	XMFLOAT2 getMousePosition() const;

private:
	void readKeyboard();
	void readMouse();
private:
	IDirectInput8* m_Input;
	IDirectInputDevice8* m_Keyboard;
	IDirectInputDevice8* m_Mouse;
	DIMOUSESTATE* m_CurMouseState;
	DIMOUSESTATE* m_PrevMouseState;
	unsigned char* m_CurKeyState;
	unsigned char* m_PrevKeyState;
	XMFLOAT2 m_MousePosition;
};