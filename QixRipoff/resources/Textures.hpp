#pragma once
#include "../toolbox/toolbox.hpp"

class Texture {
private:
	sf::Texture tex;
	std::string id;

	static sf::Texture placeholder;
	static std::list<Texture*> texList;
public:
	Texture();
	Texture(std::string _path, std::string _id);
	Texture(sf::Texture& _tex, std::string _id);

	static void init();
	static void preload(std::string _path, std::string& _id);
	static bool unload(std::string& _id);
	static bool clear();

	static const sf::Texture& getTexture(std::string _id);
};