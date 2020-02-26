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
	const static int pointTreshold;		//zmienna przechowuj¹ca iloœæ monet potrzebn¹ do otwarcia portalu
	sf::View currView;					//zmienna przechowuj¹ca aktualny widok kamery
	TextureHolder textures;				//zmienna przechowuj¹ca wszystkie tekstury w grze
	sf::Sprite background;				//zmienna przechowuj¹ca t³o gry
	Player *mPlayer;					//zmienna przechowuj¹ca wskaŸnik na gracza
	std::vector<Entity*> mBlocks;		//zmienna przechowuj¹ca wektor wskaŸników na wszystkie statyczne obiekty
	std::vector<SpawnPoint*> mSpawnPoints; //zmienna przechowuj¹ca wektor wskaŸników na wszystkie spawny 
	std::vector<Bat*> mEnemies;			//zmienna przechowuj¹ca wektor wskaŸników na wszystkich przeciwników
	std::vector<Coin*> mCoins;			//zmienna przechowuj¹ca wektor wskaŸników na wszystkie monety
	Portal *mPortal;					//zmienna przechowuj¹ca wskaŸnik na portal



	void multithreadEnemyCollisions(std::vector<Bat*> enemies, int firstIndex, int n); //funkcja która rozwi¹zuje kolzijê przeciwników u¿ywaj¹c wielow¹tkowoœci
	void handleBetterEnemyCollisions();	//funkcja która wywo³uje wieolow¹tkow¹ funkcjê rozwi¹zywania kolizi przeciwników 
	void updateEnemies(sf::Time _dt);	//funkcja która aktualizuje ruch wszystkich przeciwników
	void handlePlayerCollisions();		//funkcja która rozwi¹zuje kolizje gracza
	void updateAnimations(sf::Time _dt);//funkcja która aktualizuje wszystkie animacje obiektów w grze
	void cleanCoins();					//funkcja która usuwa zebrane monety
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj¹ca biblioteczn¹ funkcjê draw
	void updateBackground();			//funckja która tworzy t³o

public:

	World();
	~World();

	bool update(sf::Time _dt, bool keyPressed[5]);
	sf::Vector2f getPlayerPostition();
	void loadTextures();				//funkcja która ³aduje wszystkei potrzebne tekstury
	void addObject(Player *newPlayer);	//funkcja która dodaje do œwiata gracza
	void addObject(Entity *newBlock);	//funkcja która dodaje do œwiata statyczny obiekt
	void addObject(SpawnPoint *newSpawnPoint); //funkcja która dodaje do œwiata spawn gracza
	void addObject(Bat *newEnemy);		//funkcja która dodaje do œwiata przeciwnika
	void addObject(Coin *newCoin);		//funkcja która dodaje do œwiata monete
	void addObject(Portal *newPortal);	//funkcja która dodaje do œwiata portal
	int playerHealth();					//funkcja która pobiera ¿ycie gracza i je zwraca
	int playerScore();					//funkcja która pobiera punkty gracza i je zwraca
	void setCurrView(sf::View _currView);
	int getPointTreshold();
	bool playerVictory();				//funkcja która pobiera flagê zwyciêstwa gracza i j¹ zwraca
	sf::Vector2f getPlayerVelocity();	//funkcja która pobiera wektor prêdkoœæi gracza i go zwraca
};


