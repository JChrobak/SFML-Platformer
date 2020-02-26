#pragma once
#include "Entity.h"
#include "AnimationHolder.h"
class SpawnPoint :
	public Entity
{
private:
	AnimationHolder *animation;
	bool isEnabled;				//zmienna przechowuj�ca flag� czy jest to aktualnie uzywany przez gracza spawn
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj�ca biblioteczn� funkcj� draw
public:
	SpawnPoint(sf::Vector2f _position, sf::Vector2f _size);
	~SpawnPoint();
	void setEnabled(bool _isEnabled);	
	void addAnimation(sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);//funkcja kt�ra dodaje animacje 
	void updateAnimation(sf::Time _dt);//funkcja kt�ra aktualizuje animacje
};

