#pragma once
#include "Entity.h"
namespace Collision
{
	enum Type { NoCollision, Top, Bottom, Left, Right };	//typ wyliczeniowy który okeœla typ kolizji,
															//przyk³adowo je¿eli obiekt zde¿y³ siê z górn¹ czêœci¹ drugiego obiektu
															//to typ kolizji bêdzie równy Top
}

class Collidable :
	public Entity
{	
protected:
	sf::Vector2f velocity;	//zmienna która przechowuje aktualny wektor prêdkoœci obiektu
public:
	Collidable(sf::Vector2f _position, sf::Vector2f _size, Object::Type _objType);	
	Collision::Type isColliding(Entity other, sf::Vector2f velocity);				//funkcja która zwraca typ kolizji miêdzy tym obiektem i innym,
																					//gdy nie zajdzie kolizja zwróci NoCollision
	void setVelocity(sf::Vector2f _velocity);								
	sf::Vector2f getVelocity();
	void move(sf::Vector2f _velocity);									//funkcja która przesuwa obiekt o poddany wektor
	virtual void resolveCollision(Entity &other)=0;						//funkcja wirtualna która rozwi¹zuje kolizje
	
};

