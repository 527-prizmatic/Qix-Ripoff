#include "Textures.hpp"

sf::Texture Texture::placeholder;
std::list<Texture*> Texture::texList;

Texture::Texture() {
	this->id = "gustavo";
}

Texture::Texture(std::string _path, std::string _id) {
	this->tex.loadFromFile(_path);
	this->id = _id;
}

Texture::Texture(sf::Texture& _tex, std::string _id) {
	this->tex = _tex;
	this->id = _id;
}

void Texture::preinit() {
	Texture::placeholder.loadFromFile("../assets/textures/placeholder.png");
}

const sf::Texture& Texture::getTexture(std::string _id) {
	for (Texture* t: Texture::texList) {
		if (!t->id.compare(_id)) return t->tex;
	}
	return Texture::placeholder;
}

void Texture::preload(std::string _path, std::string _id) {
	Texture* tex = new Texture(_path, _id);
	Texture::texList.push_back(tex);
}

bool Texture::unload(std::string& _id) {
	for (Texture* t : Texture::texList) {
		if (!t->id.compare(_id)) {
			texList.remove(t);
			delete t;
			return true;
		}
	}
	return false;
}

bool Texture::clear() {
	bool deleted = false;
	if (Texture::texList.size() != 0) return false;
	for (Texture* t : Texture::texList) {
		texList.remove(t);
		delete t;
		deleted = true;
	}
	return deleted;
}

void Texture::treatPinkPixels(sf::Texture& _tex) {
	sf::Image image = _tex.copyToImage();
	for (unsigned int x = 0; x < image.getSize().x; x++)
	{
		for (unsigned int y = 0; y < image.getSize().y; y++)
		{
			if (image.getPixel(x, y) == sf::Color(171, 0, 66) || image.getPixel(x, y) == sf::Color(255, 0, 182))
			{
				image.setPixel(x, y, sf::Color::Transparent);
			}
		}
	}
	_tex.update(image);
}

void Texture::treatPinkPixels(std::string _id) {
	sf::Texture* tex = nullptr;
	for (Texture* t : Texture::texList) {
		if (!t->id.compare(_id)) tex = &(t->tex);
	}

	if (tex) Texture::treatPinkPixels(*tex);
}