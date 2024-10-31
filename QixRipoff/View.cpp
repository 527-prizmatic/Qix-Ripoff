#include "View.hpp"
#include "Window.hpp"

View::View() {
	this->size = sf::Vector2f(800.f, 600.f);
	this->center = sf::Vector2f(400.f, 300.f);
	this->view.setSize(this->size);
	this->view.setCenter(this->center);
}

View::View(Window& _w) {
	this->size = sf::Vector2f(_w.getSize().x, _w.getSize().y);
	this->center = this->size / 2.f;
	this->view.setSize(this->size);
	this->view.setCenter(this->center);
}

View::View(sf::Vector2f _size) {
	this->setSize(_size);
}

View::View(sf::Vector2f _tl, sf::Vector2f _br) {
	this->setCorners(_tl, _br);
}

const void View::setSize(sf::Vector2f _size) {
	this->size = _size;
	this->view.setSize(this->size);
}

const void View::setCenter(sf::Vector2f _center) {
	this->center = _center;
	this->view.setCenter(this->center);
}

const void View::setCorners(sf::Vector2f _tl, sf::Vector2f _br) {
	this->size = sf::Vector2f(_br.x - _tl.x, _br.y - _tl.y);
	this->center = itp::vector(_tl, _br, .5f, itp::formula::Linear);
	this->view.setSize(this->size);
	this->view.setCenter(this->center);
}