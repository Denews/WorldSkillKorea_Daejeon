#include "Input.h"
#include "GameConstants.h"

Input::Input(HINSTANCE instanceHandle, HWND windowHandle) :
	m_Input(nullptr),
	m_Keyboard(nullptr),
	m_Mouse(nullptr),
	m_MousePosition({ 0.0f, 0.0f }),
	m_CurKeyState(new unsigned char[256]),
	m_PrevKeyState(new unsigned char[256]),
	m_CurMouseState(new DIMOUSESTATE()),
	m_PrevMouseState(new DIMOUSESTATE())
{
	HRESULT hr;

	hr = DirectInput8Create(instanceHandle, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void **>(&m_Input), nullptr);
	if (FAILED(hr))
	{
		throw "Create DirectInput Failed";
	}

	hr = m_Input->CreateDevice(GUID_SysKeyboard, &m_Keyboard, nullptr);
	if (FAILED(hr))
	{
		throw "Create Keyboard Device Failed";
	}

	hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		throw "Keyboard Data Set Failed";
	}

	hr = m_Keyboard->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
	{
		throw "Keyboard SetCooperativeLevel Failed";
	}

	hr = m_Keyboard->Acquire();
	if (FAILED(hr))
	{
		throw "Acquire Keyboard Failed";
	}

	hr = m_Input->CreateDevice(GUID_SysMouse, &m_Mouse, nullptr);
	if (FAILED(hr))
	{
		throw "Create Mouse Device Failed";
	}

	hr = m_Mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		throw "Mouse SetDataFormat Failed";
	}

	hr = m_Mouse->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
	{
		throw "Mouse SetCooperativeLevel Failed";
	}

	hr = m_Mouse->Acquire();
	if (FAILED(hr))
	{
		throw "Acquire Mouse Failed";
	}

	memset(static_cast<void *>(m_PrevKeyState), 0, sizeof(unsigned char) * 256);
	memset(static_cast<void *>(m_CurKeyState), 0, sizeof(unsigned char) * 256);
}

Input::~Input()
{
	delete m_CurKeyState;
	delete m_CurMouseState;
	delete m_PrevKeyState;
	delete m_PrevMouseState;

	if (m_Mouse)
	{
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = nullptr;
	}
	if (m_Keyboard)
	{
		m_Keyboard->Unacquire();
		m_Keyboard->Release();
		m_Keyboard = nullptr;
	}
	if (m_Input)
	{
		m_Input->Release();
		m_Input = nullptr;
	}
}

void Input::pollInput()
{
	unsigned char* keytemp = m_CurKeyState;
	m_CurKeyState = m_PrevKeyState;
	m_PrevKeyState = keytemp;

	DIMOUSESTATE *mousetemp = m_CurMouseState;
	m_CurMouseState = m_PrevMouseState;
	m_PrevMouseState = mousetemp;

	readKeyboard();
	readMouse();

	float x = m_MousePosition.x + m_CurMouseState->lX;
	float y = m_MousePosition.y + m_CurMouseState->lY;

	int left = -GameConstants::width / 2;
	int right = GameConstants::width / 2;
	int top = GameConstants::height / 2;
	int bottom = -GameConstants::height / 2;

	m_MousePosition.x = XMMax(XMMin(right, x), left);
	m_MousePosition.y = XMMax(XMMin(top, x), bottom);
}

bool Input::getKeyPressed(int key) const
{
	if (!(0 <= key && key < 256))
	{
		throw "Key code Error";
	}

	if (!(m_PrevKeyState[key] & 0x80) && (m_CurKeyState[key] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getKeyReleased(int key) const
{
	if (!(0 <= key && key < 256))
	{
		throw "Key code Error";
	}

	if ((m_PrevKeyState[key] & 0x80) && !(m_CurKeyState[key] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getKeyRepeated(int key) const
{
	if (!(0 <= key && key < 256))
	{
		throw "Key code Error";
	}

	if ((m_PrevKeyState[key] & 0x80) && (m_CurKeyState[key] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getKey(int key) const
{
	if (!(0 <= key && key < 256))
	{
		throw "Key code Error";
	}

	if (m_CurKeyState[key] & 0x80)
	{
		return true;
	}
	else return false;
}


bool Input::getMousePressed(int button) const
{
	if (!(0 <= button && button <= 2))
	{
		throw "Mouse code Error";
	}

	if (!(m_PrevMouseState->rgbButtons[button] & 0x80) && (m_CurMouseState->rgbButtons[button] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getMouseReleased(int button) const
{
	if (!(0 <= button && button <= 2))
	{
		throw "Mouse code Error";
	}

	if ((m_PrevMouseState->rgbButtons[button] & 0x80) && !(m_CurMouseState->rgbButtons[button] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getMouseRepeated(int button) const
{
	if (!(0 <= button && button <= 2))
	{
		throw "Mouse code Error";
	}

	if ((m_PrevMouseState->rgbButtons[button] & 0x80) && (m_CurMouseState->rgbButtons[button] & 0x80))
	{
		return true;
	}
	else return false;
}

bool Input::getMouse(int button) const
{
	if (!(0 <= button && button <= 2))
	{
		throw "Mouse code Error";
	}

	if (m_CurMouseState->rgbButtons[button] & 0x80)
	{
		return true;
	}
	else return false;
}


XMFLOAT2 Input::getMousePosition() const
{
	return m_MousePosition;
}


void Input::readKeyboard()
{
	HRESULT hr;

	hr = m_Keyboard->GetDeviceState(sizeof(unsigned char) * 256, reinterpret_cast<LPVOID>(m_CurKeyState));
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_Keyboard->Acquire();
		}
		else
		{
			throw "Get KeyboardState Failed";
		}
	}
}

void Input::readMouse()
{
	HRESULT hr;

	hr = m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), reinterpret_cast<LPVOID *>(m_CurMouseState));
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_Mouse->Acquire();
		}
		else
		{
			throw "Get MouseState Failed";
		}
	}
}
