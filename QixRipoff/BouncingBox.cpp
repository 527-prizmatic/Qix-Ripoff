#include "BouncingBox.hpp"

sf::RectangleShape BouncingBox::rectRender;
std::vector<BouncingBox> BouncingBox::list;

BouncingBox::BouncingBox(sf::Vector2f _pos, sf::Vector2f _size) {
	this->clr = (enum ColorState)(rand() % 6);
	this->pos = _pos;
	this->vel = sf::Vector2f(100.f, 90.f);
	this->size = _size;
	this->id = (int)BouncingBox::list.size();
}

BouncingBox::BouncingBox(sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _size) {
	this->clr = (enum ColorState)(rand() % 6);
	this->pos = _pos;
	this->vel = _vel;
	this->size = _size;
	this->id = (int)BouncingBox::list.size();
}

void BouncingBox::create(BouncingBox _box) {
	BouncingBox::list.push_back(_box);
}

void BouncingBox::clearList() { BouncingBox::list.clear(); }

void BouncingBox::updateAll(Window& _w) {
	for (BouncingBox& b : BouncingBox::list) {
		b.move(_w);
	}
}

void BouncingBox::renderAll(Window& _w) {
	for (BouncingBox& b : BouncingBox::list) {
		b.render(_w);
	}
}

void BouncingBox::move(Window& _w) {
	if (this->pos.x < 0.f || this->pos.x > _w.getSize().x - this->size.x) {
		this->vel.x = -this->vel.x;
		this->pos += this->vel * tutil::getDelta();
		this->nextColor();
	}
	if (this->pos.y < 0.f || this->pos.y > _w.getSize().y - this->size.y) {
		this->vel.y = -this->vel.y;
		this->pos += this->vel * tutil::getDelta();
		this->nextColor();
	}

	for (BouncingBox& b : BouncingBox::list) {
		if (b.id <= this->id) continue;

		sf::FloatRect hitboxThis(this->pos, this->size);
		sf::FloatRect hitboxB(b.pos, b.size);

		if (hitboxThis.intersects(hitboxB)) {
			bool colX = fabs(this->pos.x * this->size.x - b.pos.x * b.size.x) > fabs(this->pos.y * this->size.y - b.pos.y * b.size.y);
			bool colY = fabs(this->pos.y * this->size.y - b.pos.y * b.size.y) > fabs(this->pos.x * this->size.x - b.pos.x * b.size.x);

			if (colX) {
				this->vel.x = -this->vel.x;
				b.vel.x = -b.vel.x;
				this->pos += this->vel * tutil::getDelta();
				b.pos += b.vel * tutil::getDelta();
			}
			if (colY) {
				this->vel.y = -this->vel.y;
				b.vel.y = -b.vel.y;
				this->pos += this->vel * tutil::getDelta();
				b.pos += b.vel * tutil::getDelta();
			}
		}
	}

	this->pos += this->vel * tutil::getDelta();
}

void BouncingBox::render(Window& _w) {
	this->rectRender.setPosition(this->pos);
	this->rectRender.setSize(this->size);
	this->rectRender.setFillColor(this->getColor());
	this->rectRender.setOutlineColor(sf::Color::White);
	this->rectRender.setOutlineThickness(2.f);
	_w.draw(this->rectRender);
}



void BouncingBox::nextColor() {
	int clrNew = (int)this->clr;
	clrNew = ++clrNew % CLR_TOTAL;
	this->clr = (enum ColorState)clrNew;
}

sf::Color BouncingBox::getColor() {
	switch (this->clr) {
		case CLR_RED: return sf::Color::Red;
		case CLR_YEL: return sf::Color::Yellow;
		case CLR_GRN: return sf::Color::Green;
		case CLR_CYN: return sf::Color::Cyan;
		case CLR_BLU: return sf::Color::Blue;
		case CLR_MGT: return sf::Color::Magenta;
		default: return sf::Color::Black;
	}
}