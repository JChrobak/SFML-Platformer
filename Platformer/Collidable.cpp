#include "Collidable.h"
#include <iostream>

Collidable::Collidable(sf::Vector2f _position, sf::Vector2f _size, Object::Type _objType): Entity( _position,  _size, _objType)
{
}

Collision::Type Collidable::isColliding(Entity other, sf::Vector2f velocity)
{
	
	sf::FloatRect thisObj = obj.getGlobalBounds();
	sf::FloatRect otherObj = other.getBoundingRect();
	
	if (!thisObj.intersects(otherObj))
		return Collision::NoCollision;
	else
	{
		
		sf::Vector2f pos1 = obj.getPosition();
		sf::Vector2f pos2 = other.getPosition();
		sf::RectangleShape prev(obj);
		prev.move(-velocity);
		sf::FloatRect prevRect = prev.getGlobalBounds();

		sf::RectangleShape top(other.getRectangle()),bottom(other.getRectangle()),left(other.getRectangle()),right(other.getRectangle());
		
		
		top.move(sf::Vector2f{ 0.0f,-top.getSize().y });
		bottom.move(sf::Vector2f{ 0.0f,bottom.getSize().y });
		left.move(sf::Vector2f{ -left.getSize().x,0.0f});
		right.move(sf::Vector2f{ left.getSize().x,0.0f });
		
	
		if (top.getGlobalBounds().intersects(prevRect))
			return Collision::Top;
		if (bottom.getGlobalBounds().intersects(prevRect))
			return Collision::Bottom;
		if (left.getGlobalBounds().intersects(prevRect))
			return Collision::Left;
		if (right.getGlobalBounds().intersects(prevRect))
			return Collision::Right;

		float deltaX = pos1.x - pos2.x;
		float deltaY = pos1.y - pos2.y;
		
	
		
		
		if (abs( (deltaX/other.getSize().x) )> abs( (deltaY/other.getSize().y)) )
		{
			if (deltaX < 0)
				return Collision::Left;
			else
				return Collision::Right;

		}
		else
		{
			if (deltaY < 0)
				return Collision::Top;
			else
				return Collision::Bottom;
		}
		
	}
}

void Collidable::setVelocity(sf::Vector2f _velocity)
{
	velocity = _velocity;
}


sf::Vector2f Collidable::getVelocity()
{
	return velocity;
}

void Collidable::move(sf::Vector2f _velocity)
{
	obj.move(_velocity);
}


