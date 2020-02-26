#include "TextureHolder.h"



void TextureHolder::load(Texture::ID _id, const std::string & filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename))
		throw ("Error loading texture "+_id);
	texture->setRepeated(true);
	textureMap.insert(std::make_pair(_id,std::move(texture)));
}

const sf::Texture & TextureHolder::get(Texture::ID _id) const
{
	auto result = textureMap.find(_id);
	return *result->second;
}
sf::Texture& TextureHolder::get(Texture::ID id)
{
	auto found = textureMap.find(id);   
	return *found->second; 
}




