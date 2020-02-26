#include "SpawnPoint.h"





void SpawnPoint::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	if (animation != nullptr)
	{
		target.draw(*animation, state);
		//target.draw(obj, state);
	}
	else
		target.draw(obj, state);
}

SpawnPoint::SpawnPoint(sf::Vector2f _position, sf::Vector2f _size): Entity(_position, _size, Object::Type::SpawnPoint), isEnabled(false)
{
}

SpawnPoint::~SpawnPoint()
{
	delete animation;
}

void SpawnPoint::setEnabled(bool _isEnabled)
{
	isEnabled = _isEnabled;
}

void SpawnPoint::addAnimation(sf::Texture & _texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat)
{
	if (animation != nullptr)
		delete(animation);
	animation = new AnimationHolder(_texture, _duration, _frameNumber, _repeat);
	animation->setPosition(this->obj.getPosition());
}

void SpawnPoint::updateAnimation(sf::Time _dt)
{
	if (isEnabled)
		animation->setColor(sf::Color::Green);
	else
		animation->setColor(sf::Color::White);
	animation->update(_dt);
}
