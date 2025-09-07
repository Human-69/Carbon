#pragma once

#include "cbpch.h"

class Context
{
public:
	virtual void Init() = 0;
	virtual void SwapBuffers() = 0;
};