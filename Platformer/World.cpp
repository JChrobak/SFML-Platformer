#include "World.h"
#include <iostream>
#include <chrono>

const  int World::pointTreshold = 1000;

void World::loadTextures()
{
	try
	{
		textures.load(Texture::PlayerDie, "Textures/die_sheet.png");
		textures.load(Texture::PlayerIdle, "Textures/idle_sheet.png");
		textures.load(Texture::PlayerMove, "Textures/run_sheet.png");
		textures.load(Texture::PlayerJump, "Textures/jump_sheet.png");
		textures.load(Texture::PlayerFall, "Textures/fall_sheet.png");
		textures.load(Texture::PlayerCrouch, "Textures/crouch_sheet.png");
		textures.load(Texture::Platform, "Textures/platform.png");
		textures.load(Texture::Spikes, "Textures/spikes.png");
		textures.load(Texture::SpawnPoint, "Textures/spawn_sheet.png");
		textures.load(Texture::Bat, "Textures/bat_sheet.png");
		textures.load(Texture::Bat2, "Textures/bat2_sheet.png");
		textures.load(Texture::Coin, "Textures/coin_sheet.png");
		textures.load(Texture::PortalIdle, "Textures/portal_idle.png");
		textures.load(Texture::PortalMove, "Textures/portal_move.png");
		textures.load(Texture::Background, "Textures/background.png");
	}
	catch (...)
	{
		throw;
	}

	return;
}




void World::multithreadEnemyCollisions(std::vector<Bat*> enemies, int firstIndex, int n)
{
	for (auto i = enemies.begin() + firstIndex; i < enemies.begin() + firstIndex + n; i++)
	{
		(*i)->resolveCollision(*mPlayer);
		for (auto j = mBlocks.begin(); j != mBlocks.end(); j++)
		{
			(*i)->resolveCollision(**j);
		}
	}
}


void World::handleBetterEnemyCollisions()
{
	int batsPerThread = mEnemies.size()/4;
	std::thread t4(&World::multithreadEnemyCollisions, this, mEnemies,3*batsPerThread,batsPerThread+mEnemies.size()%4);
	std::thread t1(&World::multithreadEnemyCollisions, this, mEnemies, 0, batsPerThread);
	std::thread t2(&World::multithreadEnemyCollisions, this, mEnemies, batsPerThread, batsPerThread);
	std::thread t3(&World::multithreadEnemyCollisions, this, mEnemies, 2*batsPerThread,batsPerThread);
	t4.join();
	t1.join();
	t2.join();
	t3.join();
}


void World::updateEnemies(sf::Time _dt)
{
	for (auto i = mEnemies.begin(); i != mEnemies.end(); i++)
		(*i)->update(_dt);
}

void World::handlePlayerCollisions()
{
	if (mPlayer->hasMoved())
	{
		for (auto i = mBlocks.begin(); i != mBlocks.end(); i++)
			mPlayer->resolveCollision(**i);
		for (auto i = mSpawnPoints.begin(); i != mSpawnPoints.end(); i++)
			mPlayer->resolveCollision(**i);
		for (auto i = mCoins.begin(); i != mCoins.end(); i++)
			mPlayer->resolveCollision(**i);
		mPlayer->resolveCollision(*mPortal);
	}
}


void World::updateAnimations(sf::Time _dt)
{
	updateBackground();
	if(mPlayer!=nullptr)
		mPlayer->updateAnimation(_dt);
	if (mPortal != nullptr&&mPortal->isOpen())
		mPortal->updateAnimation(_dt);
	for (auto i = mSpawnPoints.begin(); i != mSpawnPoints.end(); i++)
		(*i)->updateAnimation(_dt);
	for (auto i = mEnemies.begin(); i != mEnemies.end(); i++)
		(*i)->updateAnimation(_dt);
	for (auto i = mCoins.begin(); i != mCoins.end(); i++)
		(*i)->updateAnimation(_dt);
}

void World::cleanCoins()
{
	auto i = mCoins.begin();
	while (i != mCoins.end())
	{
		if ((*i)->isDestroyed())
		{
			i = mCoins.erase(i);
		}
		else
			i++;
	}
}

void World::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(background, state);
	for (auto i = mSpawnPoints.begin(); i != mSpawnPoints.end(); i++)
		if((*i)->onScreen(currView))
			target.draw(**i,state);
	if (mPortal != nullptr && mPortal->isOpen())
		target.draw(*mPortal, state);
	if (mPlayer != nullptr)
		target.draw(*mPlayer, state);
	for (auto i = mBlocks.begin(); i != mBlocks.end(); i++)
		if ((*i)->onScreen(currView))
			target.draw(**i,state);
	for (auto i = mCoins.begin(); i != mCoins.end(); i++)
		if ((*i)->onScreen(currView))
			target.draw(**i, state);
	for (auto i = mEnemies.begin(); i != mEnemies.end(); i++)
		if ((*i)->onScreen(currView))
			target.draw(**i, state);
	

}

void World::updateBackground(/*sf::Vector2f _position, sf::Vector2f _size*/)
{
	background.setPosition(sf::Vector2f{ -6000,-5000 });
	background.setTexture(textures.get(Texture::ID::Background));
	background.setTextureRect(sf::IntRect(sf::Vector2i{ 0, 0 }, sf::Vector2i{12000,12000}));

}


World::World()
{	
}


World::~World()
{
	delete mPlayer;
	delete mPortal;
	for (auto i = mSpawnPoints.begin(); i != mSpawnPoints.end(); i++)
		delete (*i);
	for (auto i = mBlocks.begin(); i != mBlocks.end(); i++)
		delete (*i);
	for (auto i = mEnemies.begin(); i != mEnemies.end(); i++)
		delete (*i);
	for (auto i = mCoins.begin(); i != mCoins.end(); i++)
		delete (*i);

}

bool World::update(sf::Time _dt, bool keyPressed[6])
{
	if (mPlayer != nullptr)
	{

		
		mPlayer->update(_dt, keyPressed);
		handlePlayerCollisions();
		if (mPlayer->getScore()>=pointTreshold)
			mPortal->openPortal();
		updateEnemies(_dt);
		handleBetterEnemyCollisions();
		updateAnimations(_dt);
		
		cleanCoins();
		
		if (!mPlayer->respawn())
			return false;
		else if (mPlayer->finishedCurrLevel())
			return false;
		else
			return true;
		
	}
	return false;
}

sf::Vector2f World::getPlayerPostition()
{
	return mPlayer->getPosition();
}

void World::addObject(Player * newPlayer)
{
	if (mPlayer != nullptr)
		delete mPlayer;
	mPlayer = newPlayer;
	mPlayer->addAnimation(Animation::Type::Idle, textures.get(Texture::ID::PlayerIdle), sf::Time(sf::seconds(0.5f)), 4, true);
	mPlayer->addAnimation(Animation::Type::Move, textures.get(Texture::ID::PlayerMove), sf::Time(sf::seconds(0.5f)), 6, true);
	mPlayer->addAnimation(Animation::Type::Fall, textures.get(Texture::ID::PlayerFall), sf::Time(sf::seconds(0.5f)), 2, true);
	mPlayer->addAnimation(Animation::Type::Jump, textures.get(Texture::ID::PlayerJump), sf::Time(sf::seconds(0.76f)), 13, false);
	mPlayer->addAnimation(Animation::Type::Death, textures.get(Texture::ID::PlayerDie), sf::Time(sf::seconds(0.76f)), 5, false);
	mPlayer->addAnimation(Animation::Type::Crouch, textures.get(Texture::ID::PlayerCrouch), sf::Time(sf::seconds(0.5f)), 4, true);
}

void World::addObject(Entity * newBlock)
{
	if (newBlock->getType() == Object::Type::Wall)
	{
		newBlock->setTexture(textures.get(Texture::ID::Platform), true);
		newBlock->setColor(sf::Color(47,57,66));
	}
	else
		newBlock->setTexture(textures.get(Texture::ID::Spikes), false);
	mBlocks.push_back(newBlock);
}

void World::addObject(SpawnPoint * newSpawnPoint)
{

	newSpawnPoint->addAnimation(textures.get(Texture::ID::SpawnPoint), sf::Time(sf::milliseconds(550)), 4, true);
	mSpawnPoints.push_back(newSpawnPoint);
}

void World::addObject(Bat * newEnemy)
{
	/*if (rand() % 2)
		(newEnemy)->addAnimation(textures.get(Texture::ID::Bat), sf::Time(sf::seconds(0.5f)), 5, true);
	else*/
	(newEnemy)->addAnimation(textures.get(Texture::ID::Bat2), sf::Time(sf::seconds(0.5f)), 5, true);
	mEnemies.push_back(newEnemy);
}

void World::addObject(Coin * newCoin)
{
	newCoin->addAnimation(textures.get(Texture::ID::Coin), sf::Time(sf::seconds(0.5f)), 5, true);
	mCoins.push_back(newCoin);
}

void World::addObject(Portal * newPortal)
{
	if (mPortal != nullptr)
		delete mPortal;
	mPortal = newPortal;
	mPortal->addAnimation(Animation::Type::Idle, textures.get(Texture::ID::PortalIdle), sf::Time(sf::seconds(0.75f)), 8, true);
	mPortal->addAnimation(Animation::Type::Move, textures.get(Texture::ID::PortalMove), sf::Time(sf::seconds(0.75f)), 8, false);
}

int World::playerHealth()
{
    return mPlayer->remainingLives();
}

int World::playerScore()
{
	return mPlayer->getScore();
}

void World::setCurrView(sf::View _currView)
{
	currView = _currView;
}

int World::getPointTreshold()
{
	return pointTreshold;
}

bool World::playerVictory()
{
	return mPlayer->finishedCurrLevel();
}

sf::Vector2f World::getPlayerVelocity()
{
	return mPlayer->getVelocity();
}
