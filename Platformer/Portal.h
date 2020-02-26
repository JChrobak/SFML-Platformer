#pragma once
#include "Entity.h"
#include "AnimationHolder.h"
class Portal :
	public Entity
{
private: 
	bool open;						//zmienna która przechowujê flagê czy portal jest otwarty czy nie
	AnimationHolder *animations[2]; //zmienna która przechowujê wszystkie animacje portalu
	Animation::Type currAnimation;	//zmienna która przechowujê typ aktualanje animacji
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj¹ca biblioteczn¹ funkcjê draw
public:
	Portal(sf::Vector2f _position, sf::Vector2f _size); 
	void addAnimation(Animation::Type _animType, sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);//funkcja która dodaje animacje 
	void updateAnimation(sf::Time _dt);//funkcja która aktualizuje animacje
	bool isOpen();	   //funkcja zwraca flagê true gdy portal jest otwarty
	void openPortal(); //funkcja która otwiera dany portal
	~Portal();

};

