#pragma once

#include "Application.h"
#include "CarbonTypes.h"

extern Scope<Carbon::Application> CreateApplication(const std::string name);

int main()
{
	std::cout << "Running!\n";
	Carbon::Application::instance = CreateApplication("Carbon");
	Carbon::Application::Get().Run();
	return 0;
}