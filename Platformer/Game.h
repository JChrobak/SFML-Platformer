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
	enum GameState { Menu, PlayGame, Finished };	//typ wyliczeniowy który okreœla aktualny stan aplikacji
	
	GameState currGameState;						//zmienna która przechowuje aktualny stan aplikacji

	bool resized;									//zmienna która przechowuje wartoœæ czy zosta³a zmieniona wartoœæ okna od ostatniej aktualizacji
	sf::Font fontNormal, fontTitle;					//zmienne przechowuj¹ce czcionki u¿ywane w grze					
	sf::Text gameText[2], menuText[2], gameTitle, resultText[3];	//zmienne przechowuj¹ce tekst wykorzystywany w grze

	World mWorld;								//zmienna która przechowuje aktualny poziom w grze oraz wszystkie obiekty w nim zawarte
	sf::RenderWindow mWindow;					//zmienna która przechowuje okno aplikacji
	float mapTop, mapBottom, mapLeft, mapRight; //zmienne przechowuj¹ce pozycje krawêdzi mapy
	static const sf::Time timePerFrame;			//zmienna która przechowuje czas przeznaczony na jedn¹ klatkê
	bool keyPressed[6] = { false };				//zmienna która przechowuje który z przycisków zosta³ naciœniety
	
	void menu();								//funkcja obs³uguj¹ca menu gry
	void handleEvents();						//funkcja która obs³uguje klawiature oraz zamykanie i zmienianie wielkoœci okna
	void handlePlayerInput(sf::Keyboard::Key keyCode, bool isPressed);	//funkcja która ustawia wartoœci tabeli keyPressed w zale¿noœci od wciœniêtego przycisku
	void updateView();							//funkcja która obs³uguje kamerê w grze
	void renderGame();							//funkcja która wyœwietla grê na ekran
	void updateGameText();						//funkcja która aktualaizuje tekst wyœwietlany podczas gry
	void openLevel(string levelName);			//funkcja otwieraj¹ca poziom zawarty w pliku .lvl
	void run();									//funkcja obs³uguj¹ca rozgrywkê w danym poziomie
	void gameResult(bool levelComplete, int score);//funkcja ob³suguj¹ca ekran wyników po grze
public:
	Game(sf::VideoMode _resolution, string _title);
	void start();	//funkcja która uruchamia grê
};

