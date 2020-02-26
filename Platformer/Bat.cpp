#include "Bat.h"
#include <iostream>
const float Bat::movementSpeed = 120.f;

void Bat::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	if (animation != nullptr)
	{
		target.draw(*animation, state);
		//target.draw(obj, state);
	}
	else
		target.draw(obj, state);
}

Bat::Bat(sf::Vector2f _position, sf::Vector2f _size): Collidable(_position,_size,Object::Type::Enemy)
{
	velocity.y = 0;
	if(rand()%2)
		velocity.x = movementSpeed;
	else
		velocity.x = -movementSpeed;
	this->setColor(sf::Color::Yellow);
}

void Bat::addAnimation(sf::Texture & _texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat)
{
	if (animation != nullptr)
		delete(animation);
	animation = new AnimationHolder(_texture, _duration, _frameNumber, _repeat);
	animation->setPosition(this->obj.getPosition());
	animation->setColor(sf::Color::Cyan);
	if (velocity.x < 0)
		animation->swap();
}

void Bat::updateAnimation(sf::Time _dt)
{
	if(animation->getDirection()==Animation::Direction::Right)
		animation->setPosition(this->getPosition() - sf::Vector2f{5.f,-2.f});
	else
		animation->setPosition(this->getPosition() + sf::Vector2f{ 5.f,2.f });
	if(animation!=nullptr)
		animation->update(_dt);
}

void Bat::resolveCollision(Entity & other)
{
	Collision::Type cType = isColliding(other, velocity);
	if (cType == Collision::NoCollision)
	{
		return;
	}

	switch (other.getType())
	{
	case Object::Wall:
		switch (cType)
		{
		case Collision::Left: setXPosition(other.getLeft() - getSize().x / 2.0f); velocity = -velocity; animation->swap();  //std::cout << "B: Left" << std::endl;
			return;
		case Collision::Right: setXPosition(other.getRight() + getSize().x / 2.0f); velocity = -velocity; animation->swap(); //std::cout << "B: Right" << std::endl;
			return;
		case Collision::Top: setYPosition(other.getTop() - getSize().y / 2.0f); //::cout << "B: Top" << std::endl;
			return;
		case Collision::Bottom: setYPosition(other.getBottom() + getSize().y / 2.0f); //std::cout << "B: Bottom" << std::endl;
			return;
		}
		break;
	case Object::Player:
		switch (cType)
		{
		case Collision::Left:
		case Collision::Right:
		case Collision::Top:
		case Collision::Bottom:
			dynamic_cast<Player&>(other).hurt(); //std::cout << "B: Player" << std::endl;
			return;
		}
		break;
	}
}

void Bat::update(sf::Time _dt)
{
	obj.move(velocity*_dt.asSeconds());
}


Bat::~Bat()
{
}
