#include "Portal.h"



void Portal::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	if (animations[currAnimation] != nullptr)
	{
		target.draw(*animations[currAnimation], state);
		//target.draw(obj, state);
	}
	else
		target.draw(obj, state);
}

void Portal::addAnimation(Animation::Type _animType, sf::Texture & _texture, sf::Time _duration, unsigned int _frameNumber,  bool _repeat)
{
	if (_animType <= Animation::Type::Move)
	{
		if (animations[_animType] != nullptr)
			delete(animations[_animType]);
		animations[_animType] = new AnimationHolder(_texture, _duration, _frameNumber, _repeat);
		animations[_animType]->setPosition(this->obj.getPosition());
		animations[_animType]->swap();
		animations[_animType]->setColor(sf::Color::Cyan);
	}
}

void Portal::updateAnimation(sf::Time _dt)
{
	if (animations[Animation::Type::Move]->isFinished())
		currAnimation = Animation::Type::Idle;
	animations[currAnimation]->update(_dt);
}

bool Portal::isOpen()
{
	return open;
}

void Portal::openPortal()
{
	this->open = true;
}

Portal::Portal(sf::Vector2f _position, sf::Vector2f _size): Entity(_position,_size,Object::Type::Portal), open(false), currAnimation(Animation::Type::Move)
{

}


Portal::~Portal()
{
	delete animations[0];
	delete animations[1];
}
