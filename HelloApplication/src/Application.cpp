#include "Application.h"

#include <iostream>

Application::Application()
{
	
}

void Application::SetUp()
{
	
}

void Application::Update()
{
	std::cout << "Application::Update" << std::endl;
}

void Application::Draw()
{
	std::cout << "Application::Draw" << std::endl;
}

void Application::KeyBoard()
{
	std::cout << "Application::KeyBoard" << std::endl;
}
