#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "AnimationHolder.h"
class Coin :
	public Entity
{
private:
	int value;																		//zmienna która przechowuje wartoœæ monety
	AnimationHolder *animation;														
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;	//funkcja nadpisuj¹ca biblioteczn¹ funkcjê draw
public:
	Coin(sf::Vector2f _position, sf::Vector2f _size);								
	Coin(sf::Vector2f _position, sf::Vector2f _size, int _value);
	~Coin();

	void addAnimation(sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);//funkcja która dodaje animacje 
	void updateAnimation(sf::Time _dt);		//funkcja która aktualizuje animacje
	int getValue();							//funkcja która zwraca wartoœæ monety
};

