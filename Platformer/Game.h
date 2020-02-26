#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "World.h"

using namespace std;
class Game
{
	
private:
	enum GameState { Menu, PlayGame, Finished };	//typ wyliczeniowy kt�ry okre�la aktualny stan aplikacji
	
	GameState currGameState;						//zmienna kt�ra przechowuje aktualny stan aplikacji

	bool resized;									//zmienna kt�ra przechowuje warto�� czy zosta�a zmieniona warto�� okna od ostatniej aktualizacji
	sf::Font fontNormal, fontTitle;					//zmienne przechowuj�ce czcionki u�ywane w grze					
	sf::Text gameText[2], menuText[2], gameTitle, resultText[3];	//zmienne przechowuj�ce tekst wykorzystywany w grze

	World mWorld;								//zmienna kt�ra przechowuje aktualny poziom w grze oraz wszystkie obiekty w nim zawarte
	sf::RenderWindow mWindow;					//zmienna kt�ra przechowuje okno aplikacji
	float mapTop, mapBottom, mapLeft, mapRight; //zmienne przechowuj�ce pozycje kraw�dzi mapy
	static const sf::Time timePerFrame;			//zmienna kt�ra przechowuje czas przeznaczony na jedn� klatk�
	bool keyPressed[6] = { false };				//zmienna kt�ra przechowuje kt�ry z przycisk�w zosta� naci�niety
	
	void menu();								//funkcja obs�uguj�ca menu gry
	void handleEvents();						//funkcja kt�ra obs�uguje klawiature oraz zamykanie i zmienianie wielko�ci okna
	void handlePlayerInput(sf::Keyboard::Key keyCode, bool isPressed);	//funkcja kt�ra ustawia warto�ci tabeli keyPressed w zale�no�ci od wci�ni�tego przycisku
	void updateView();							//funkcja kt�ra obs�uguje kamer� w grze
	void renderGame();							//funkcja kt�ra wy�wietla gr� na ekran
	void updateGameText();						//funkcja kt�ra aktualaizuje tekst wy�wietlany podczas gry
	void openLevel(string levelName);			//funkcja otwieraj�ca poziom zawarty w pliku .lvl
	void run();									//funkcja obs�uguj�ca rozgrywk� w danym poziomie
	void gameResult(bool levelComplete, int score);//funkcja ob�suguj�ca ekran wynik�w po grze
public:
	Game(sf::VideoMode _resolution, string _title);
	void start();	//funkcja kt�ra uruchamia gr�
};

