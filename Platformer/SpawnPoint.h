#pragma once
#include "Entity.h"
#include "AnimationHolder.h"
class SpawnPoint :
	public Entity
{
private:
	AnimationHolder *animation;
	bool isEnabled;				//zmienna przechowuj¹ca flagê czy jest to aktualnie uzywany przez gracza spawn
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj¹ca biblioteczn¹ funkcjê draw
public:
	SpawnPoint(sf::Vector2f _position, sf::Vector2f _size);
	~SpawnPoint();
	void setEnabled(bool _isEnabled);	
	void addAnimation(sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);//funkcja która dodaje animacje 
	void updateAnimation(sf::Time _dt);//funkcja która aktualizuje animacje
};

