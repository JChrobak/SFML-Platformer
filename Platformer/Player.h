#pragma once
#include <map>
#include "Collidable.h"
#include "AnimationHolder.h"
#include "SpawnPoint.h"
#include "Coin.h"
#include "Portal.h"
namespace Key {
	enum Type { Left, Right, Down, Up, Attack, Enter }; //typ wyliczeniowy okreœlaj¹cy aktualnie wybrany klawisz na klawiaturze
}
class Player :
	public Collidable
{
private:
	int health, score;									//zmienne przechowuj¹ce ¿ycie i punkty gracza
	static const float movementSpeed,gravityForce;		//zmienne przechowuj¹ce prêdkoœæ poruszania oraz spadania gracza
	static const int maximalJump,jumpPause, minimalJump;//zmienne przechowuj¹ce wysokoœæ maksymaln¹, minimaln¹ oraz czas zawieszenia w powietrzu skoku
	static const int startingHealth, invulnerabilityLength; //zmienne przechowuj¹ce startowe ¿ycie oraz d³ugoœæ niewra¿liwoœci po otrzymaniu obra¿eñ
	int jumpCounter, totalJumpCounter;					//zmienne przechowuj¹ce aktualny czas skoku oraz ca³¹ d³ugoœæ aktualnego skoku 
	int	invulnerabilityCounter;							//zmienna przechowuj¹ca aktualn¹ d³ugoœæ niewra¿liwoœci
	bool jumping ,falling, onGround,crouching, finishedLevel; //flagi okreœlaj¹ce czy gracz skacze, spada, jest na ziemi, kuca i czy skoñczy³ poziom
	Animation::Type currAnimation;						//zmienna przechowuj¹ca aktualny typ animacji
	AnimationHolder *animations[7];						//zmienna przechowuj¹ca wszystkie animacje gracza
	sf::Vector2f currSpawnPosition;						//zmienna przechowuj¹ca aktualn¹ pozycje spawnu gracza
	sf::Vector2f  previousPosition;						//zmienna przechowuj¹ca pozycjê gracza klatê temu
	SpawnPoint *currSpawnPoint;							//zmienna przechowujaca wskaŸnik na aktualny spawn gracza



	void draw(sf::RenderTarget & target, sf::RenderStates state) const override;//funkcja nadpisuj¹ca biblioteczn¹ funkcjê draw
	void crouch();		//funkcja która obs³uguje kucanie gracza
	void stand();		//funkcja która obs³uguje wstwawanie po kucniêciu gracza

public:
	Player(sf::Vector2f _position, sf::Vector2f _size);
	~Player();



	void resolveCollision(Entity &other) override;

	void addAnimation(Animation::Type _type, sf::Texture&_texture, sf::Time _duration, unsigned int _frameNumber, bool _repeat);//funkcja która dodaje animacje 
	void update(sf::Time _dt, bool keyPressed[6]);	//funkcja która aktualizuje ruch gracza
	void updateAnimation(sf::Time _dt);				//funkcja która aktualizuje animacje

	void jump();			//funkcja która obs³uguje skok gracza
	bool isJumping();		//funkcja która zwraca true gdy gracz skacze
	void checkGround();		//funkcja która zwraca true gdy gracz znajduje siê na ziemi
	void allowNextJump();	//funkcja która pozwala graczowi na wykonanie kolejengo skoku

	int remainingLives();	//funkcja która zwraca aktualn¹ iloœæ ¿ycia gracza
	void hurt();			//funkcja która obs³uguje zadawanie obra¿eñ graczowi
	bool respawn();			//funkcja która obs³uguje respawn gracza

	bool hasMoved();		//funkcja która zwraca true gdy gracz poruszy³ siê od czasu poprzedniej klatki
	int getScore();
	void addScore(int points); //funkcja która dodaje punkty graczowi
	bool finishedCurrLevel();  //funkcja która zwraca true gdy gracz ukoñczy³ poziom
};

