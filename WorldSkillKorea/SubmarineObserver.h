#pragma once
#include "Submarine.h"

class SubmarineObserver
{
private:
	Submarine* m_Submarine;
public:
	SubmarineObserver() = delete;
	SubmarineObserver(SubmarineObserver&) = delete;
	SubmarineObserver(Submarine* submarine) : m_Submarine(submarine) {}

	XMFLOAT3 getPosition() const { return m_Submarine->getPosition(); }
	void hit() { m_Submarine->onHitted(); }
};