#pragma once
#include <SFML/Graphics.hpp>
namespace Animation
{
	enum Direction{Left, Right};						//typ wyliczeniowy okre�laj�cy w kt�r� strone jest zwr�cona animacja
	enum Type{Idle,Move,Jump,Fall,Death,Hit,Crouch};	//typ wyliczeniowy okre�laj�cy w typ animacji
}
class AnimationHolder :
	public sf::Drawable,
	public sf::Transformable
{
private:
	sf::Sprite mSprite;						//zmienna kt�ra przechowuje aktualn� ramk� animacji oraz teksture i jest wy�lwietlana na ekranie
	sf::Vector2u frameSize;					//zmienna kt�ra przechowuje wielko�� jednej klatki animacji
	std::size_t frameNumber;				//zmienna kt�ra przechowuje ilo�� klatek w animacji
	std::size_t currFrame;					//zmienna kt�ra przechowuje numer aktualnej klatki animacji
	sf::Time animDuration;					//zmienna kt�ra przechowuje czas trwania ca�ej animacji
	sf::Time elapsedTime;					//zmienna kt�ra przechowuje ile czasu up�yne�o od pocz�tku animacji
	Animation::Direction animDirection;		//zmienna kt�ra przechowuje stron� w kt�r� jest zwr�cona animacja

	bool repeat, finished;					//zmienne kt�ra przechowuj� czy animacje nalezy powtarza� oraz czy ju� si� zako�czy�a
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //funkcja nadpisuj�ca biblioteczn� funkcj� draw

public:
	AnimationHolder(sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);


	void setColor(sf::Color _color);
	void setPosition(sf::Vector2f _pos);
	void update(sf::Time dt);				//funkcja kt�ra aktualizuje animacje w zale�no�ci od tego ile czasu up�yne�o
	void swap();							//funkcja kt�ra zmiena zwrot animacji
	void restart();							//funkcja kt�ra restartuje animacje
	bool isFinished();

	Animation::Direction getDirection();
};

