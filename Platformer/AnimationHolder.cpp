#include "AnimationHolder.h"
#include <iostream>


void AnimationHolder::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	target.draw(mSprite, state);
}

AnimationHolder::AnimationHolder(sf::Texture&_texture,sf::Time _duration, unsigned int _frameNumber, bool _repeat): 
	mSprite(_texture),
	animDuration(_duration),
	repeat(_repeat),
	finished(false),
	frameNumber(_frameNumber),
	currFrame(0),
	elapsedTime(sf::Time::Zero), 
	animDirection(Animation::Direction::Right)
{
	sf::FloatRect spriteBounds = mSprite.getGlobalBounds();
	mSprite.setOrigin(spriteBounds.left + spriteBounds.height / 2.f, spriteBounds.top + spriteBounds.height / 2.f);
	mSprite.setScale(2, 2);
	frameSize = sf::Vector2u(_texture.getSize().x / frameNumber, _texture.getSize().y);
}


void AnimationHolder::setColor(sf::Color _color)
{
	mSprite.setColor(_color);
}

void AnimationHolder::setPosition(sf::Vector2f _pos)
{
	mSprite.setPosition(_pos);
}

void AnimationHolder::update(sf::Time dt)
{
	sf::Time frameDuration = animDuration / static_cast<float>(frameNumber);
	elapsedTime += dt;

	sf::Vector2u textureBounds(mSprite.getTexture()->getSize());
	sf::IntRect textureRect=mSprite.getTextureRect();

	if (currFrame == 0)
		textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);

	while (elapsedTime >= frameDuration && (currFrame <= frameNumber || repeat))
	{
		
		elapsedTime -= frameDuration;
		++currFrame;
			if (currFrame >= frameNumber)
			{
				if (repeat)
				{
					currFrame = 0;
					textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
				}
					
				else
				{	
					currFrame--;
					finished=true;
				}
				
			}
			else
				textureRect.left += textureRect.width;
		
	}
		
	mSprite.setTextureRect(textureRect);
}

void AnimationHolder::swap()
{
	mSprite.scale(sf::Vector2f{ -1,1 });
	if (animDirection == Animation::Direction::Left)
		animDirection = Animation::Direction::Right;
	else
		animDirection = Animation::Direction::Left;
}

void AnimationHolder::restart()
{
	currFrame = 0;
	finished = false;
}

bool AnimationHolder::isFinished()
{
	return finished;
}

Animation::Direction AnimationHolder::getDirection()
{
	return animDirection;
}

