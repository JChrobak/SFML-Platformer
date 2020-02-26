#pragma once
#include <SFML/Graphics.hpp>

namespace Object
{
	enum Type { Wall, Player, Coin, SpawnPoint, Spikes, Enemy, Portal};		//typ wyliczeniowy który okreœla typ obiektu
}

class Entity : public sf::Drawable
{
protected:
	
	sf::RectangleShape obj;		//zmienna która przechowuje prostok¹t ograniczaj¹cy kolizje obiektu, oraz teksture w przypadku obiektów bez animacji
	bool destructionFlag;		//zmienna która przechowuje wartoœæ flagi okreœlajacej czy obiekt jest zniszczony czy nie
	Object::Type objType;		//zmienna która przechowuje typ obiektu
private:
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj¹ca biblioteczn¹ funkcjê draw
public:
	Entity(sf::Vector2f _position, sf::Vector2f _size, Object::Type _objType);
	void setPosition(sf::Vector2f _position);
	void setXPosition(float _x);
	void setYPosition(float _y);
	bool isDestroyed();
	void destroy();												//funkcja która ustawia flagê destrukcji na true
	Object::Type getType();
	sf::Vector2f getPosition();
	sf::FloatRect getBoundingRect();							//funkcja która zwraca sam zakres prostok¹ta ograniczaj¹cego kolzije obiektu
	sf::RectangleShape getRectangle();							//funkcja która zwraca prostok¹t ograniczajacy kolizje obiektu
	float getLeft();											//funkcja która zwraca lew¹ krawêdŸ obiektu
	float getRight();											//funkcja która zwraca praw¹ krawêdŸ obiektu
	float getTop();												//funkcja która zwraca górn¹ krawêdŸ obiektu
	float getBottom();											//funkcja która zwraca doln¹ krawêdŸ obiektu
	sf::Vector2f getSize();
	sf::Vector2f getOrigin();									//funkcja która zwraca œrodek obiektu
	void setTexture(sf::Texture &_texture, bool _repeated);		//funkcja która ustawia teksture obiektu
	void setColor(sf::Color _color);							//funkcja która ustawia kolor tekstury obiektu
	bool onScreen(sf::View _currView);							//funkcja która zwraca true gdy obiekt lub jego czêœæ znajduje siê na ekranie
};


