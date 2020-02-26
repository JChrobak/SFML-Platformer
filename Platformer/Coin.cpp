#include "Coin.h"






void Coin::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	if (animation != nullptr)
	{
		target.draw(*animation, state);
		//target.draw(obj, state);
	}
	else
		target.draw(obj, state);
}

Coin::Coin(sf::Vector2f _position, sf::Vector2f _size): Entity(_position,_size,Object::Type::Coin), value(50)
{
}

Coin::Coin(sf::Vector2f _position, sf::Vector2f _size, int _value): Entity(_position, _size, Object::Type::Coin), value(_value)
{
}

Coin::~Coin()
{
	delete animation;
}

void Coin::addAnimation(sf::Texture & _texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat)
{
	if (animation != nullptr)
		delete(animation);
	animation = new AnimationHolder(_texture, _duration, _frameNumber, _repeat);
	animation->setPosition(this->obj.getPosition());
	animation->setColor(sf::Color::Yellow);
	
}

void Coin::updateAnimation(sf::Time _dt)
{
	animation->update(_dt);
}

int Coin::getValue()
{
	return value;
}
