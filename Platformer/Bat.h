#pragma once
#include "Collidable.h"
#include "AnimationHolder.h"
#include "Player.h"
class Bat :
	public Collidable
{
private:
	const static float movementSpeed;												//zmienna kt�ra przechowuje pr�dko�� poruszania si� przeciwnika
	AnimationHolder *animation;														//zmienna kt�ra przechowuje animacje przeciwnika
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;	//funkcja nadpisuj�ca biblioteczn� funkcj� draw
public:
	Bat(sf::Vector2f _position, sf::Vector2f _size);
	void addAnimation(sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);	//funkcja kt�ra dodaje animacje 
	void updateAnimation(sf::Time _dt);										//funkcja kt�ra aktualizuje animacje
	void resolveCollision(Entity &other) override;							//funckja kt�ra rozwi�zuje kolizje obiektu z innymi obiektami
	void update(sf::Time _dt);												//funkcja kt�ra aktualizuje ruch przeciwnika
	~Bat();
};

