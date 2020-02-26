#pragma once
#include <SFML/Graphics.hpp>
namespace Animation
{
	enum Direction{Left, Right};						//typ wyliczeniowy okreœlaj¹cy w któr¹ strone jest zwrócona animacja
	enum Type{Idle,Move,Jump,Fall,Death,Hit,Crouch};	//typ wyliczeniowy okreœlaj¹cy w typ animacji
}
class AnimationHolder :
	public sf::Drawable,
	public sf::Transformable
{
private:
	sf::Sprite mSprite;						//zmienna która przechowuje aktualn¹ ramkê animacji oraz teksture i jest wyœlwietlana na ekranie
	sf::Vector2u frameSize;					//zmienna która przechowuje wielkoœæ jednej klatki animacji
	std::size_t frameNumber;				//zmienna która przechowuje iloœæ klatek w animacji
	std::size_t currFrame;					//zmienna która przechowuje numer aktualnej klatki animacji
	sf::Time animDuration;					//zmienna która przechowuje czas trwania ca³ej animacji
	sf::Time elapsedTime;					//zmienna która przechowuje ile czasu up³yne³o od pocz¹tku animacji
	Animation::Direction animDirection;		//zmienna która przechowuje stronê w któr¹ jest zwrócona animacja

	bool repeat, finished;					//zmienne która przechowuj¹ czy animacje nalezy powtarzaæ oraz czy ju¿ siê zakoñczy³a
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //funkcja nadpisuj¹ca biblioteczn¹ funkcjê draw

public:
	AnimationHolder(sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);


	void setColor(sf::Color _color);
	void setPosition(sf::Vector2f _pos);
	void update(sf::Time dt);				//funkcja która aktualizuje animacje w zale¿noœci od tego ile czasu up³yne³o
	void swap();							//funkcja która zmiena zwrot animacji
	void restart();							//funkcja która restartuje animacje
	bool isFinished();

	Animation::Direction getDirection();
};

