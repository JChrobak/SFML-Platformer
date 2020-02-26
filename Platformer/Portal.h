#pragma once
#include "Entity.h"
#include "AnimationHolder.h"
class Portal :
	public Entity
{
private: 
	bool open;						//zmienna kt�ra przechowuj� flag� czy portal jest otwarty czy nie
	AnimationHolder *animations[2]; //zmienna kt�ra przechowuj� wszystkie animacje portalu
	Animation::Type currAnimation;	//zmienna kt�ra przechowuj� typ aktualanje animacji
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj�ca biblioteczn� funkcj� draw
public:
	Portal(sf::Vector2f _position, sf::Vector2f _size); 
	void addAnimation(Animation::Type _animType, sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);//funkcja kt�ra dodaje animacje 
	void updateAnimation(sf::Time _dt);//funkcja kt�ra aktualizuje animacje
	bool isOpen();	   //funkcja zwraca flag� true gdy portal jest otwarty
	void openPortal(); //funkcja kt�ra otwiera dany portal
	~Portal();

};

