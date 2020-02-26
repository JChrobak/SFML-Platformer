#pragma once
#include <map>
#include <SFML/Graphics.hpp>
namespace Texture {
	enum ID{PlayerIdle,PlayerMove,PlayerJump,PlayerFall,PlayerDie,PlayerCrouch,Platform, Spikes, SpawnPoint, Bat, Bat2, Coin, PortalMove, PortalIdle, Background};
																									//typ wyliczeniowy przechowuj�cy id danej tekstury
}
class TextureHolder
{
private:
	std::map<Texture::ID, std::unique_ptr<sf::Texture>> textureMap;	//mapa przechowuj�ca wszystkie tekstury w grze wraz z odpowiadaj�ymi im id
public:
	void load(Texture::ID _id, const std::string &filename);	//funkcja dodaj�ca tekstur� do mapy 
	sf::Texture& get(Texture::ID _id);							//funkcja zwracaj�ca tekstur� o podanym id
	const sf::Texture& get(Texture::ID _id) const;				//statyczne prze�adowanie powy�szej funkcji
};

