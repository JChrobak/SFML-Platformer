#include "Entity.h"



void Entity::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(obj, state);
}

void Entity::setPosition(sf::Vector2f _position)
{
	obj.setPosition(_position);
}

void Entity::setXPosition(float _x)
{
	obj.setPosition(sf::Vector2f{ _x,obj.getPosition().y });
}

void Entity::setYPosition(float _y)
{
	obj.setPosition(sf::Vector2f{ obj.getPosition().x, _y });
}

bool Entity::isDestroyed()
{
	return destructionFlag;
}

void Entity::destroy()
{
	destructionFlag=true;
}

sf::Vector2f Entity::getPosition()
{
	return obj.getPosition();
}



sf::FloatRect Entity::getBoundingRect()
{
	return obj.getGlobalBounds();
}

sf::RectangleShape Entity::getRectangle()
{
	return obj;
}

float Entity::getLeft()
{
	return obj.getGlobalBounds().left;
}

float Entity::getRight()
{
	return obj.getGlobalBounds().left+obj.getSize().x;
}

float Entity::getTop()
{
	return obj.getGlobalBounds().top;
}

float Entity::getBottom()
{
	return obj.getGlobalBounds().top+obj.getSize().y;
}

sf::Vector2f Entity::getSize()
{
	return obj.getSize();
}

sf::Vector2f Entity::getOrigin()
{
	return obj.getOrigin();
}

void Entity::setTexture(sf::Texture & _texture, bool _repeated)
{
	_texture.setRepeated(_repeated);

	obj.setTexture(&_texture);
	obj.setTextureRect(sf::IntRect(0,0,obj.getSize().x,obj.getSize().y));


}

void Entity::setColor(sf::Color _color)
{
	obj.setFillColor(_color);
}

bool Entity::onScreen(sf::View _currView)
{
	if (this->getBottom() < _currView.getCenter().y - _currView.getSize().y / 2)
		return false;
	else if (this->getTop() > _currView.getCenter().y + _currView.getSize().y / 2)
		return false;
	else if (this->getRight() < _currView.getCenter().x - _currView.getSize().x / 2)
		return false;
	else if (this->getLeft() > _currView.getCenter().x + _currView.getSize().x / 2)
		return false;
	else
		return true;
}

Entity::Entity(sf::Vector2f _position, sf::Vector2f _size, Object::Type _objType): destructionFlag(false), objType(_objType)
{
	//obj.setFillColor(sf::Color::Green);
	obj.setSize(_size);
	obj.setOrigin(_size / 2.f);
	obj.setPosition(_position);
		
}
Object::Type Entity::getType()
{
	return objType;
}



