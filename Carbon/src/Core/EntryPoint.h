#pragma once

#include "Application.h"
#include "CarbonTypes.h"

extern Scope<Carbon::Application> CreateApplication(const std::string name);

int main()
{
	std::cout << "Running!\n";
	Scope<Carbon::Application> Application = CreateApplication("Carbon");
	Application->Run();
	return 0;
}