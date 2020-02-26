#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "AnimationHolder.h"
class Coin :
	public Entity
{
private:
	int value;																		//zmienna kt�ra przechowuje warto�� monety
	AnimationHolder *animation;														
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;	//funkcja nadpisuj�ca biblioteczn� funkcj� draw
public:
	Coin(sf::Vector2f _position, sf::Vector2f _size);								
	Coin(sf::Vector2f _position, sf::Vector2f _size, int _value);
	~Coin();

	void addAnimation(sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);//funkcja kt�ra dodaje animacje 
	void updateAnimation(sf::Time _dt);		//funkcja kt�ra aktualizuje animacje
	int getValue();							//funkcja kt�ra zwraca warto�� monety
};

