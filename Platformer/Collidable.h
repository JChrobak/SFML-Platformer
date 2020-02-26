#pragma once
#include "Entity.h"
namespace Collision
{
	enum Type { NoCollision, Top, Bottom, Left, Right };	//typ wyliczeniowy kt�ry oke�la typ kolizji,
															//przyk�adowo je�eli obiekt zde�y� si� z g�rn� cz�ci� drugiego obiektu
															//to typ kolizji b�dzie r�wny Top
}

class Collidable :
	public Entity
{	
protected:
	sf::Vector2f velocity;	//zmienna kt�ra przechowuje aktualny wektor pr�dko�ci obiektu
public:
	Collidable(sf::Vector2f _position, sf::Vector2f _size, Object::Type _objType);	
	Collision::Type isColliding(Entity other, sf::Vector2f velocity);				//funkcja kt�ra zwraca typ kolizji mi�dzy tym obiektem i innym,
																					//gdy nie zajdzie kolizja zwr�ci NoCollision
	void setVelocity(sf::Vector2f _velocity);								
	sf::Vector2f getVelocity();
	void move(sf::Vector2f _velocity);									//funkcja kt�ra przesuwa obiekt o poddany wektor
	virtual void resolveCollision(Entity &other)=0;						//funkcja wirtualna kt�ra rozwi�zuje kolizje
	
};

