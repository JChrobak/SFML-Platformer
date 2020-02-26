#pragma once
#include <map>
#include "Collidable.h"
#include "AnimationHolder.h"
#include "SpawnPoint.h"
#include "Coin.h"
#include "Portal.h"
namespace Key {
	enum Type { Left, Right, Down, Up, Attack, Enter }; //typ wyliczeniowy okre�laj�cy aktualnie wybrany klawisz na klawiaturze
}
class Player :
	public Collidable
{
private:
	int health, score;									//zmienne przechowuj�ce �ycie i punkty gracza
	static const float movementSpeed,gravityForce;		//zmienne przechowuj�ce pr�dko�� poruszania oraz spadania gracza
	static const int maximalJump,jumpPause, minimalJump;//zmienne przechowuj�ce wysoko�� maksymaln�, minimaln� oraz czas zawieszenia w powietrzu skoku
	static const int startingHealth, invulnerabilityLength; //zmienne przechowuj�ce startowe �ycie oraz d�ugo�� niewra�liwo�ci po otrzymaniu obra�e�
	int jumpCounter, totalJumpCounter;					//zmienne przechowuj�ce aktualny czas skoku oraz ca�� d�ugo�� aktualnego skoku 
	int	invulnerabilityCounter;							//zmienna przechowuj�ca aktualn� d�ugo�� niewra�liwo�ci
	bool jumping ,falling, onGround,crouching, finishedLevel; //flagi okre�laj�ce czy gracz skacze, spada, jest na ziemi, kuca i czy sko�czy� poziom
	Animation::Type currAnimation;						//zmienna przechowuj�ca aktualny typ animacji
	AnimationHolder *animations[7];						//zmienna przechowuj�ca wszystkie animacje gracza
	sf::Vector2f currSpawnPosition;						//zmienna przechowuj�ca aktualn� pozycje spawnu gracza
	sf::Vector2f  previousPosition;						//zmienna przechowuj�ca pozycj� gracza klat� temu
	SpawnPoint *currSpawnPoint;							//zmienna przechowujaca wska�nik na aktualny spawn gracza



	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj�ca biblioteczn� funkcj� draw
	void crouch();		//funkcja kt�ra obs�uguje kucanie gracza
	void stand();		//funkcja kt�ra obs�uguje wstwawanie po kucni�ciu gracza

public:
	Player(sf::Vector2f _position, sf::Vector2f _size);
	~Player();



	void resolveCollision(Entity &other) override;

	void addAnimation(Animation::Type _type, sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);//funkcja kt�ra dodaje animacje 
	void update(sf::Time _dt, bool keyPressed[6]);	//funkcja kt�ra aktualizuje ruch gracza
	void updateAnimation(sf::Time _dt);				//funkcja kt�ra aktualizuje animacje

	void jump();			//funkcja kt�ra obs�uguje skok gracza
	bool isJumping();		//funkcja kt�ra zwraca true gdy gracz skacze
	void checkGround();		//funkcja kt�ra zwraca true gdy gracz znajduje si� na ziemi
	void allowNextJump();	//funkcja kt�ra pozwala graczowi na wykonanie kolejengo skoku

	int remainingLives();	//funkcja kt�ra zwraca aktualn� ilo�� �ycia gracza
	void hurt();			//funkcja kt�ra obs�uguje zadawanie obra�e� graczowi
	bool respawn();			//funkcja kt�ra obs�uguje respawn gracza

	bool hasMoved();		//funkcja kt�ra zwraca true gdy gracz poruszy� si� od czasu poprzedniej klatki
	int getScore();
	void addScore(int points); //funkcja kt�ra dodaje punkty graczowi
	bool finishedCurrLevel();  //funkcja kt�ra zwraca true gdy gracz uko�czy� poziom
};

