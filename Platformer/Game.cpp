#include "Game.h"

#include <iostream>

const sf::Time Game::timePerFrame = sf::seconds(1.0f / 30.0f);


Game::Game(sf::VideoMode _resolution, string _title): resized(true), currGameState(Menu)
{
	mWindow.create(_resolution, _title);
	if (fontNormal.loadFromFile("Fonts/munro.ttf"))
	{
		gameText[0].setFont(fontNormal);
		gameText[1].setFont(fontNormal);
		menuText[0].setFont(fontNormal);
		menuText[1].setFont(fontNormal);
		resultText[1].setFont(fontNormal);
		resultText[2].setFont(fontNormal);
	}
	if (fontTitle.loadFromFile("Fonts/pab.otf"))
	{
		gameTitle.setFont(fontTitle);
		resultText[0].setFont(fontTitle);
	}
	gameText[0].setFillColor(sf::Color::White);
	gameText[1].setFillColor(sf::Color::White);
	menuText[0].setFillColor(sf::Color::Yellow);
	menuText[1].setFillColor(sf::Color::White);
	gameTitle.setFillColor(sf::Color::Green);
	resultText[0].setFillColor(sf::Color::White);
	resultText[1].setFillColor(sf::Color::Yellow);
}

void Game::start()
{
	this->menu();
}

void Game::openLevel(string levelName)
{
	try {
		mWorld.loadTextures();
	}
	catch (...)
	{
		throw;
	}

	int xSize, ySize;
	ifstream file("Levels/" + levelName + ".lvl");
	if (file.good())
	{
		file >> xSize;
		file >> ySize;
		char** map;
		map = new char*[xSize];
		for (int i = 0; i < xSize; i++)
			map[i] = new char[ySize];

		for (int i = 0; i < ySize; i++)
		{
			for (int j = 0; j < xSize; j++)
			{
				char temp;
				file >> temp;
				if (temp != '\n')
					map[j][i] = temp;
			}
		}

		float currX = 12.5f, currY = 12.5f;
		for (int y = 0; y < ySize; y++)
		{
			for (int x = 0; x < xSize; x++)
			{

				switch (map[x][y])
				{
				case 'w':	if (x < xSize - 1 && map[x + 1][y] == 'w')
							{
								x++;
								int temp = x + 1;
								float objSize = 2.f;
								currX += 25.f;
								while (temp < xSize - 1 && map[temp][y] == 'w')
								{
									objSize++;
									temp++;
									x++;
									currX += 25.f;
								}
								mWorld.addObject(new Entity(sf::Vector2f{ (currX + 12.5f - 25.f / 2.f*objSize),currY }, sf::Vector2f{ 25 * objSize,25 }, Object::Type::Wall));
								break;
							}
							else if (y < ySize - 1 && map[x][y + 1] == 'w')
							{
								map[x][y] = '.';
								int temp = y + 1;
								float objSize = 1.f;
								while (temp < ySize   && map[x][temp] == 'w')
								{
									map[x][temp] = '.';
									objSize++;
									temp++;
								}
								mWorld.addObject(new Entity(sf::Vector2f{ currX,(currY + 25 * objSize / 2 - 12.5f) }, sf::Vector2f{ 25,25 * objSize }, Object::Type::Wall));
								break;
							}
							else
								mWorld.addObject(new Entity(sf::Vector2f{ currX,currY }, sf::Vector2f{ 25,25 }, Object::Type::Wall)); break;

				case 's':	if (x < xSize - 1 && map[x + 1][y] == 's')
							{
								x++;
								int temp = x + 1;
								float objSize = 2.f;
								currX += 25.f;
								while (temp < xSize && map[temp][y] == 's')
								{
									objSize++;
									temp++;
									x++;
									currX += 25.f;
								}
								mWorld.addObject(new Entity(sf::Vector2f{ (currX + 12.5f - 25.f / 2.f*objSize),currY }, sf::Vector2f{ 25 * objSize,25 }, Object::Type::Spikes));
								break;
							}
							else
								mWorld.addObject(new Entity(sf::Vector2f{ currX,currY }, sf::Vector2f{ 25,25 }, Object::Type::Spikes)); break;
				case 'c': mWorld.addObject(new Coin(sf::Vector2f{ currX,currY }, sf::Vector2f{ 20,20 })); break;
				case 'p': mWorld.addObject(new Player(sf::Vector2f{ currX,currY }, sf::Vector2f{ 18.f,60.f })); break;
				case 'r': mWorld.addObject(new SpawnPoint(sf::Vector2f{ currX,currY }, sf::Vector2f{ 10.f,22.f })); break;
				case 'b': mWorld.addObject(new Bat(sf::Vector2f{ currX,currY }, sf::Vector2f{ 1.f,10.f })); break;
				case 'e': mWorld.addObject(new Portal(sf::Vector2f{ currX,currY }, sf::Vector2f{ 10.f,22.f })); break;
				}
				currX += 25.f;
			}
			currY += 25.f;
			currX = 12.5f;

		}	
		mapTop = 0;
		mapBottom = 25.f * ySize;
		mapLeft = 0;
		mapRight = 25.f * xSize;
	}
	else
		throw;
}

void Game::menu()
{
	enum MenuOption { Play, Exit };
	MenuOption currOption=Play;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	gameTitle.setString("BATS & COINS");
	gameTitle.setCharacterSize(69);
	gameTitle.setOrigin(gameTitle.getLocalBounds().left + gameTitle.getLocalBounds().width / 2.f, gameTitle.getLocalBounds().top + gameTitle.getLocalBounds().height/2.f);
	gameTitle.setPosition(mWindow.getView().getCenter() - sf::Vector2f{ 0,200 });
	
	menuText[0].setString("Play Game");
	menuText[0].setOrigin(menuText[0].getLocalBounds().left + menuText[0].getLocalBounds().width / 2.f, menuText[0].getLocalBounds().top + menuText[0].getLocalBounds().height / 2.f);
	menuText[0].setPosition(mWindow.getView().getCenter() - sf::Vector2f{ 0,50 });
	
	menuText[1].setString("Exit Game");
	menuText[1].setOrigin(menuText[1].getLocalBounds().left + menuText[1].getLocalBounds().width / 2.f, menuText[1].getLocalBounds().top + menuText[1].getLocalBounds().height / 2.f);
	menuText[1].setPosition(mWindow.getView().getCenter() - sf::Vector2f{ 0,20 });

	while (currGameState == Menu && mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > timePerFrame)
		{

			timeSinceLastUpdate -= timePerFrame;
			handleEvents();
		}
		if (keyPressed[Key::Type::Up] && currOption>0)
		{
			menuText[currOption].setFillColor(sf::Color::White);
			currOption=MenuOption(currOption-1);
			menuText[currOption].setFillColor(sf::Color::Yellow);
		}
		if (keyPressed[Key::Type::Down] && currOption < Exit)
		{
			menuText[currOption].setFillColor(sf::Color::White);
			currOption = MenuOption(currOption + 1);
			menuText[currOption].setFillColor(sf::Color::Yellow);
		}
		if (keyPressed[Key::Type::Enter])
		{
			switch (currOption)
			{
			case MenuOption::Play: currGameState = GameState::PlayGame;
								   try
							   	   {
									   this->openLevel("level_02");
								   }
								   catch (...)
								   {
									   std::cout << "CRITICAL ERROR, CLOSING GAME!" << endl;
									   mWindow.close();
								   }
								   this->run();
								   break;
			case MenuOption::Exit: mWindow.close();
			}
		}
		mWindow.clear();
		mWindow.draw(gameTitle);
		mWindow.draw(menuText[0]);
		mWindow.draw(menuText[1]);
		mWindow.display();
	}
}
void Game::handleEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed: handlePlayerInput(event.key.code,true); break;
		case sf::Event::KeyReleased: handlePlayerInput(event.key.code, false); break;
		case sf::Event::Closed: mWindow.close(); break;
		case sf::Event::Resized: resized = true; break;
		}
	}

}

void Game::handlePlayerInput(sf::Keyboard::Key keyCode, bool isPressed)
{
	
	switch (keyCode)
	{
	case sf::Keyboard::A: keyPressed[Key::Left] = isPressed; return;
	case sf::Keyboard::D: keyPressed[Key::Right] = isPressed; return;
	case sf::Keyboard::W: keyPressed[Key::Up] = isPressed; return;
	case sf::Keyboard::S: keyPressed[Key::Down] = isPressed; return;
	case sf::Keyboard::Enter: keyPressed[Key::Enter] = isPressed; return;
	}
}

void Game::updateView()
{

	if (mWorld.getPlayerVelocity() != sf::Vector2f{ 0,0 }||resized)
	{
		
		sf::View nextView;
		sf::Vector2f windowSize = static_cast<sf::Vector2f>(mWindow.getSize());
		sf::Vector2f playerPos = mWorld.getPlayerPostition();
		sf::Vector2f prevCenter = mWindow.getView().getCenter();
		sf::Vector2f viewCenter = playerPos;
		
		if (playerPos.x + windowSize.x / 2 > mapRight && mapRight - mapLeft > windowSize.x)
			viewCenter.x = mapRight - windowSize.x / 2;
		if (playerPos.x - windowSize.x / 2 < mapLeft && mapRight - mapLeft > windowSize.x)
			viewCenter.x = mapLeft + windowSize.x / 2;
		if (playerPos.y - windowSize.y / 2 < mapTop && mapBottom - mapTop > windowSize.y)
			viewCenter.y = mapTop + windowSize.y / 2;
		if (playerPos.y + windowSize.y / 2 > mapBottom && mapBottom - mapTop > windowSize.y)
			viewCenter.y = mapBottom - windowSize.y / 2;

		nextView.setCenter(viewCenter);
		nextView.setSize(windowSize);
		mWorld.setCurrView(nextView);
		mWindow.setView(nextView);
		resized = false;
	}
}



void Game::renderGame()
{
	mWindow.clear(sf::Color(27,23,46));
	mWindow.draw(mWorld);
	mWindow.draw(gameText[0]);
	mWindow.draw(gameText[1]);
	mWindow.display();
	
}

void Game::updateGameText()
{
	gameText[0].setString("Lives: " + std::to_string(mWorld.playerHealth()));
	gameText[1].setString("Coins: " + std::to_string(mWorld.playerScore()/50)+"/"+std::to_string(mWorld.getPointTreshold()/50));
	gameText[0].setPosition(mWindow.getView().getCenter() - static_cast<sf::Vector2f>(mWindow.getSize()) / 2.f + sf::Vector2f{ 25.f,0.f });
	gameText[1].setPosition(mWindow.getView().getCenter() - static_cast<sf::Vector2f>(mWindow.getSize()) / 2.f + sf::Vector2f{ 25.f,25.f });
}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (currGameState==PlayGame && mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > timePerFrame)
		{
		
			//auto start = std::chrono::steady_clock::now();
			timeSinceLastUpdate -= timePerFrame;
			handleEvents();
			if (!mWorld.update(timePerFrame, keyPressed))
			{

				currGameState = GameState::Finished;
				gameResult(mWorld.playerVictory(), mWorld.playerScore());

			}
			//auto end = std::chrono::steady_clock::now();
			//auto diff = end - start;
			//if (std::chrono::duration <double, std::milli>(diff).count() > 3)
				//std::cout << std::chrono::duration <double, std::milli>(diff).count() << " ms" << std::endl;
		}
		

		updateView();
		updateGameText();
	
		renderGame();
	}
}

void Game::gameResult(bool levelComplete, int score)
{
	enum MenuOption { Play, Exit };
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	if (levelComplete)
	{
		resultText[0].setString("CONGRATULATIONS! YOU WIN!");
		resultText[0].setFillColor(sf::Color::Cyan);
		resultText[0].setCharacterSize(40);
		resultText[0].setOrigin(resultText[0].getLocalBounds().left + resultText[0].getLocalBounds().width / 2.f, resultText[0].getLocalBounds().top + resultText[0].getLocalBounds().height / 2.f);
		resultText[0].setPosition(mWindow.getView().getCenter() - sf::Vector2f{ 0,200 });
	}
	else
	{
		resultText[0].setString("GAME OVER! YOU LOSE!");
		resultText[0].setFillColor(sf::Color::Red);
		resultText[0].setCharacterSize(40);
		resultText[0].setOrigin(resultText[0].getLocalBounds().left + resultText[0].getLocalBounds().width / 2.f, resultText[0].getLocalBounds().top + resultText[0].getLocalBounds().height / 2.f);
		resultText[0].setPosition(mWindow.getView().getCenter() - sf::Vector2f{ 0,200 });
	}
	resultText[1].setString("YOUR SCORE: " + std::to_string(score + 100 * mWorld.playerHealth()));
	resultText[1].setOrigin(resultText[1].getLocalBounds().left + resultText[1].getLocalBounds().width / 2.f, resultText[1].getLocalBounds().top + resultText[1].getLocalBounds().height / 2.f);
	resultText[1].setPosition(mWindow.getView().getCenter() - sf::Vector2f{ 0,50 });

	resultText[2].setString("PRESS ENTER TO EXIT");
	resultText[2].setOrigin(resultText[2].getLocalBounds().left + resultText[2].getLocalBounds().width / 2.f, resultText[2].getLocalBounds().top + resultText[2].getLocalBounds().height / 2.f);
	resultText[2].setPosition(mWindow.getView().getCenter() - sf::Vector2f{ 0,20 });


	while (currGameState == GameState::Finished && mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			handleEvents();
		}
		if (keyPressed[Key::Type::Enter])
		{
			mWindow.close();
		}
		mWindow.clear();
		mWindow.draw(resultText[0]);
		mWindow.draw(resultText[1]);
		mWindow.draw(resultText[2]);
		mWindow.display();
	}
}



