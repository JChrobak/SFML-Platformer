#pragma once
#include <map>
#include <SFML/Graphics.hpp>
namespace Texture {
	enum ID{PlayerIdle,PlayerMove,PlayerJump,PlayerFall,PlayerDie,PlayerCrouch,Platform, Spikes, SpawnPoint, Bat, Bat2, Coin, PortalMove, PortalIdle, Background};
																									//typ wyliczeniowy przechowuj¹cy id danej tekstury
}
class TextureHolder
{
private:
	std::map<Texture::ID, std::unique_ptr<sf::Texture>> textureMap;	//mapa przechowuj¹ca wszystkie tekstury w grze wraz z odpowiadaj¹ymi im id
public:
	void load(Texture::ID _id, const std::string &filename);	//funkcja dodaj¹ca teksturê do mapy 
	sf::Texture& get(Texture::ID _id);							//funkcja zwracaj¹ca teksturê o podanym id
	const sf::Texture& get(Texture::ID _id) const;				//statyczne prze³adowanie powy¿szej funkcji
};

