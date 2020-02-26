#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include "Player.h"
#include "Collidable.h"
#include "Entity.h"
#include "TextureHolder.h"
#include "Bat.h"
#include "Coin.h"
#include "Portal.h"

class World:
	public sf::Drawable
{
private:
	const static int pointTreshold;		//zmienna przechowuj�ca ilo�� monet potrzebn� do otwarcia portalu
	sf::View currView;					//zmienna przechowuj�ca aktualny widok kamery
	TextureHolder textures;				//zmienna przechowuj�ca wszystkie tekstury w grze
	sf::Sprite background;				//zmienna przechowuj�ca t�o gry
	Player *mPlayer;					//zmienna przechowuj�ca wska�nik na gracza
	std::vector<Entity*> mBlocks;		//zmienna przechowuj�ca wektor wska�nik�w na wszystkie statyczne obiekty
	std::vector<SpawnPoint*> mSpawnPoints; //zmienna przechowuj�ca wektor wska�nik�w na wszystkie spawny 
	std::vector<Bat*> mEnemies;			//zmienna przechowuj�ca wektor wska�nik�w na wszystkich przeciwnik�w
	std::vector<Coin*> mCoins;			//zmienna przechowuj�ca wektor wska�nik�w na wszystkie monety
	Portal *mPortal;					//zmienna przechowuj�ca wska�nik na portal



	void multithreadEnemyCollisions(std::vector<Bat*> enemies, int firstIndex, int n); //funkcja kt�ra rozwi�zuje kolzij� przeciwnik�w u�ywaj�c wielow�tkowo�ci
	void handleBetterEnemyCollisions();	//funkcja kt�ra wywo�uje wieolow�tkow� funkcj� rozwi�zywania kolizi przeciwnik�w 
	void updateEnemies(sf::Time _dt);	//funkcja kt�ra aktualizuje ruch wszystkich przeciwnik�w
	void handlePlayerCollisions();		//funkcja kt�ra rozwi�zuje kolizje gracza
	void updateAnimations(sf::Time _dt);//funkcja kt�ra aktualizuje wszystkie animacje obiekt�w w grze
	void cleanCoins();					//funkcja kt�ra usuwa zebrane monety
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj�ca biblioteczn� funkcj� draw
	void updateBackground();			//funckja kt�ra tworzy t�o

public:

	World();
	~World();

	bool update(sf::Time _dt, bool keyPressed[5]);
	sf::Vector2f getPlayerPostition();
	void loadTextures();				//funkcja kt�ra �aduje wszystkei potrzebne tekstury
	void addObject(Player *newPlayer);	//funkcja kt�ra dodaje do �wiata gracza
	void addObject(Entity *newBlock);	//funkcja kt�ra dodaje do �wiata statyczny obiekt
	void addObject(SpawnPoint *newSpawnPoint); //funkcja kt�ra dodaje do �wiata spawn gracza
	void addObject(Bat *newEnemy);		//funkcja kt�ra dodaje do �wiata przeciwnika
	void addObject(Coin *newCoin);		//funkcja kt�ra dodaje do �wiata monete
	void addObject(Portal *newPortal);	//funkcja kt�ra dodaje do �wiata portal
	int playerHealth();					//funkcja kt�ra pobiera �ycie gracza i je zwraca
	int playerScore();					//funkcja kt�ra pobiera punkty gracza i je zwraca
	void setCurrView(sf::View _currView);
	int getPointTreshold();
	bool playerVictory();				//funkcja kt�ra pobiera flag� zwyci�stwa gracza i j� zwraca
	sf::Vector2f getPlayerVelocity();	//funkcja kt�ra pobiera wektor pr�dko��i gracza i go zwraca
};


