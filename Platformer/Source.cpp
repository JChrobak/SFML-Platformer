#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include "Game.h"

int main()
{

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	srand(time(NULL));
	Game mGame(sf::VideoMode{ 800,600 }, "Platformer");
	mGame.start();
	
}
