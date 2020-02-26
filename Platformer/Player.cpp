#include "Player.h"
#include <iostream>

const float Player::movementSpeed = 150.0f;
const int Player::maximalJump = 25;
const int Player::minimalJump =10;
const int Player::jumpPause = 2;
const float Player::gravityForce = 250.f;
const int Player::startingHealth = 5;
const int Player::invulnerabilityLength = 120;
void Player::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	if (animations[currAnimation] != nullptr)
	{
		if (animations[currAnimation]->getDirection() == Animation::Direction::Right)
		{
			if (!crouching)
				animations[currAnimation]->setPosition(sf::Vector2f{ obj.getPosition().x - 13.f,obj.getPosition().y - 6.5f });
			else
				animations[currAnimation]->setPosition(sf::Vector2f{ obj.getPosition().x - 13.f,obj.getPosition().y - 6.5f -obj.getSize().y/2.f});
		}
		else
		{
			if (!crouching)
				animations[currAnimation]->setPosition(sf::Vector2f{ obj.getPosition().x + 13.f,obj.getPosition().y - 6.5f });
			else
				animations[currAnimation]->setPosition(sf::Vector2f{ obj.getPosition().x + 13.f,obj.getPosition().y - 6.5f - obj.getSize().y /2.f});
		}
		

		
		target.draw(*animations[currAnimation], state);
		//target.draw(obj, state);
		
	}
	else
		target.draw(obj, state);

	
}




Player::Player(sf::Vector2f _position, sf::Vector2f _size):

Collidable(_position, _size, Object::Type::Player), 
invulnerabilityCounter(invulnerabilityLength),
jumping(false),
falling(true),
crouching(false),
finishedLevel(false),
jumpCounter(0),
health(startingHealth),
currSpawnPosition(_position)
{
	obj.setFillColor(sf::Color::Red);
}

Player::~Player()
{
	delete animations[0];
	delete animations[1];
	delete animations[2];
	delete animations[3];
	delete animations[4];

}




void Player::resolveCollision(Entity &other)
{
	Collision::Type cType=isColliding(other,velocity);
	if (cType == Collision::NoCollision)
	{
		if(onGround!=true)
			falling = true;
		return;
	}
	
	switch (other.getType())
	{
	case Object::Wall:
		switch(cType)
		{
		case Collision::Left: setXPosition(other.getLeft() - getSize().x / 2.0f);// std::cout << "Left" << std::endl;
			return;
		case Collision::Right: setXPosition(other.getRight() + getSize().x / 2.0f);//std::cout << "Right" << std::endl; 
			return;
		case Collision::Top: setYPosition(other.getTop() - getSize().y / 2.0f); onGround = true;
 			falling = false;// std::cout << "Top" << std::endl;
			return;
		case Collision::Bottom: setYPosition(other.getBottom() + getSize().y / 2.0f); jumpCounter = 0;// std::cout << "Bottom" << std::endl; 
			return;
		}
		break;
	case Object::Spikes:
		switch (cType)
		{
		case Collision::Left: setXPosition(other.getLeft() - getSize().x / 2.0f); //this->hurt(); 
			return;
		case Collision::Right: setXPosition(other.getRight() + getSize().x / 2.0f);  //this->hurt();
			return;
		case Collision::Top: this->hurt();
			return;
		case Collision::Bottom: setYPosition(other.getBottom() + getSize().y / 2.0f); jumpCounter = 0;// std::cout << "Bottom" << std::endl; 
			return;
		}
		break;
	case Object::SpawnPoint: 
		if (!destructionFlag)
		{
			if (currSpawnPoint != nullptr && currSpawnPoint != &dynamic_cast<SpawnPoint&>(other))
				currSpawnPoint->setEnabled(false);
			currSpawnPoint = &dynamic_cast<SpawnPoint&>(other);
			currSpawnPoint->setEnabled(true);
			currSpawnPosition = currSpawnPoint->getPosition();
		}
		return;
		break;
	case Object::Enemy:
		this->hurt();
		return;
		break;
	case Object::Coin:
		score += dynamic_cast<Coin&>(other).getValue();
		other.destroy();
		break;
	case Object::Portal:
		if (dynamic_cast<Portal&>(other).isOpen())
			finishedLevel = true;
		break;
	}
	
}




void Player::addAnimation(Animation::Type _type, sf::Texture & _texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat)
{
	if (animations[_type] != nullptr)
		delete(animations[_type]);
	animations[_type] = new AnimationHolder(_texture, _duration, _frameNumber, _repeat);
	

}
void Player::update(sf::Time elapsedTime, bool keyPressed[6])
{
	if (invulnerabilityCounter > 0)
		invulnerabilityCounter--;
	velocity = sf::Vector2f{ 0.f,0.f };
	previousPosition = this->getPosition();
	if (!destructionFlag)
	{

		if (keyPressed[Key::Left])
		{
			velocity.x -= movementSpeed;
			invulnerabilityCounter=0;
		}
		if (keyPressed[Key::Right])
		{
			velocity.x += movementSpeed;
			invulnerabilityCounter = 0;
		}
		if (keyPressed[Key::Down])
		{
			this->crouch();
			invulnerabilityCounter = 0;
		}
		else
		{
			this->stand();
		}
		if (keyPressed[Key::Up])
		{
			this->jump();
			invulnerabilityCounter = 0;
		}
		else
			this->allowNextJump();


		if (this->isJumping())
		{
			velocity.y -= gravityForce*1.3f;
		}
		else if (falling)
		{
			if (jumpCounter == 0)
				velocity.y += gravityForce;
		}
	}
	else
		velocity.y += gravityForce;
	if (velocity != sf::Vector2f{ 0.f,0.f })
	{
		onGround = false;
		velocity *= elapsedTime.asSeconds();
		this->obj.move(velocity);
	}

}
void Player::updateAnimation(sf::Time _dt)
{
	sf::Vector2f diffVector = this->getPosition() - previousPosition;
	Animation::Type nextAnimation;
	Animation::Direction nextDirection;
	if (destructionFlag)
	{
		nextDirection = animations[currAnimation]->getDirection();
		nextAnimation = Animation::Type::Death;

	}
	else
	{
		if (diffVector.x != 0)
		{
			if (onGround)
				nextAnimation = Animation::Type::Move;
			else
				nextAnimation = currAnimation;

			if (diffVector.x > 0)
				nextDirection = Animation::Direction::Right;
			else
				nextDirection = Animation::Direction::Left;
		}

		else if (currAnimation != Animation::Type::Jump)
			nextAnimation = Animation::Type::Idle;
		else
			nextAnimation = currAnimation;

		

		if (diffVector.y > 0 && !onGround)
			nextAnimation = Animation::Type::Fall;
		if (diffVector.y < 0&& !onGround &&velocity.y<0)
			nextAnimation = Animation::Type::Jump;
		if (crouching)
			nextAnimation = Animation::Type::Crouch;
		if (diffVector.x == 0)
			nextDirection = animations[currAnimation]->getDirection();

		
	}

	if (nextAnimation != currAnimation)
		animations[nextAnimation]->restart();
	currAnimation = nextAnimation;
	
	

	if (animations[currAnimation]->getDirection() != nextDirection)
	{
		animations[currAnimation]->swap();
	}
	if (invulnerabilityCounter > 0)
		animations[currAnimation]->setColor(sf::Color::Yellow);
	else if(currAnimation==Animation::Death)
		animations[currAnimation]->setColor(sf::Color::Red);
	else
		animations[currAnimation]->setColor(sf::Color::White);
	animations[currAnimation]->update(_dt);
}

void Player::crouch()
{
	if (onGround)
	{
		if (!crouching)
		{
			crouching = true;
			this->setYPosition(obj.getPosition().y+obj.getSize().y/3.f);
			obj.setSize(sf::Vector2f{ obj.getSize().x, obj.getSize().y / 1.5f });

		}

		velocity.x = 0;
	}
}

void Player::stand()
{
	if (crouching)
	{
		crouching = false;
		obj.setSize(sf::Vector2f{ obj.getSize().x, obj.getSize().y * 1.5f });
		this->setYPosition(obj.getPosition().y - obj.getSize().y / 3.f);
	}
}


void Player::jump()
{
	if (!falling&&!jumping&&!crouching)
	{
		jumping = true;
		jumpCounter = minimalJump;
		totalJumpCounter = jumpCounter;

	}
	else if (jumpCounter!=0)
	{
		if (totalJumpCounter < maximalJump)
		{
			jumpCounter++;
			totalJumpCounter++;
			if (totalJumpCounter > maximalJump)
			{
				jumpCounter -= totalJumpCounter - maximalJump;
				totalJumpCounter = maximalJump;
			}
		}
	}
	return;
}

bool Player::isJumping()
{
	if(jumpCounter>0)
	{
		if (--jumpCounter > jumpPause)
			return true;
	}
		return false;
}




void Player::checkGround()
{
	onGround = false;
}

void Player::allowNextJump()
{
	jumping = false;
}


int Player::remainingLives()
{
	return health;
}

void Player::hurt()
{
	if (!this->destructionFlag&&invulnerabilityCounter==0)
	{
		health--;
		this->stand();
		destructionFlag = true;
	}
}

bool Player::respawn()
{
	if (destructionFlag && animations[Animation::Type::Death]->isFinished() && health > 0)
	{
		this->setPosition(currSpawnPosition + sf::Vector2f{0,this->getSize().y/2});
		this->destructionFlag = false;
		this->falling = true;
		this->jumpCounter = 0;
		this->onGround = false;
		this->invulnerabilityCounter = invulnerabilityLength;
	}
	if (health <= 0)
		return !animations[Animation::Type::Death]->isFinished();
	else
		return true;
}

bool Player::hasMoved()
{
	return!(previousPosition - this->getPosition() == sf::Vector2f{ 0,0 })||falling;
}

int Player::getScore()
{
	return score;
}

void Player::addScore(int points)
{
	score += points;
}

bool Player::finishedCurrLevel()
{
	return finishedLevel;
}

