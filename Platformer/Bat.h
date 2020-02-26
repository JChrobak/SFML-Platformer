#pragma once
#include "Collidable.h"
#include "AnimationHolder.h"
#include "Player.h"
class Bat :
	public Collidable
{
private:
	const static float movementSpeed;												//zmienna która przechowuje prêdkoœæ poruszania siê przeciwnika
	AnimationHolder *animation;														//zmienna która przechowuje animacje przeciwnika
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;	//funkcja nadpisuj¹ca biblioteczn¹ funkcjê draw
public:
	Bat(sf::Vector2f _position, sf::Vector2f _size);
	void addAnimation(sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);	//funkcja która dodaje animacje 
	void updateAnimation(sf::Time _dt);										//funkcja która aktualizuje animacje
	void resolveCollision(Entity &other) override;							//funckja która rozwi¹zuje kolizje obiektu z innymi obiektami
	void update(sf::Time _dt);												//funkcja która aktualizuje ruch przeciwnika
	~Bat();
};

