#pragma once
#include <SFML/Graphics.hpp>

namespace Object
{
	enum Type { Wall, Player, Coin, SpawnPoint, Spikes, Enemy, Portal};		//typ wyliczeniowy kt�ry okre�la typ obiektu
}

class Entity : public sf::Drawable
{
protected:
	
	sf::RectangleShape obj;		//zmienna kt�ra przechowuje prostok�t ograniczaj�cy kolizje obiektu, oraz teksture w przypadku obiekt�w bez animacji
	bool destructionFlag;		//zmienna kt�ra przechowuje warto�� flagi okre�lajacej czy obiekt jest zniszczony czy nie
	Object::Type objType;		//zmienna kt�ra przechowuje typ obiektu
private:
	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj�ca biblioteczn� funkcj� draw
public:
	Entity(sf::Vector2f _position, sf::Vector2f _size, Object::Type _objType);
	void setPosition(sf::Vector2f _position);
	void setXPosition(float _x);
	void setYPosition(float _y);
	bool isDestroyed();
	void destroy();												//funkcja kt�ra ustawia flag� destrukcji na true
	Object::Type getType();
	sf::Vector2f getPosition();
	sf::FloatRect getBoundingRect();							//funkcja kt�ra zwraca sam zakres prostok�ta ograniczaj�cego kolzije obiektu
	sf::RectangleShape getRectangle();							//funkcja kt�ra zwraca prostok�t ograniczajacy kolizje obiektu
	float getLeft();											//funkcja kt�ra zwraca lew� kraw�d� obiektu
	float getRight();											//funkcja kt�ra zwraca praw� kraw�d� obiektu
	float getTop();												//funkcja kt�ra zwraca g�rn� kraw�d� obiektu
	float getBottom();											//funkcja kt�ra zwraca doln� kraw�d� obiektu
	sf::Vector2f getSize();
	sf::Vector2f getOrigin();									//funkcja kt�ra zwraca �rodek obiektu
	void setTexture(sf::Texture &_texture, bool _repeated);		//funkcja kt�ra ustawia teksture obiektu
	void setColor(sf::Color _color);							//funkcja kt�ra ustawia kolor tekstury obiektu
	bool onScreen(sf::View _currView);							//funkcja kt�ra zwraca true gdy obiekt lub jego cz�� znajduje si� na ekranie
};


