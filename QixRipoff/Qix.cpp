#include "Qix.hpp"
#include "GameField.hpp"
#include "Player.hpp"

sf::VertexArray Qix::renderVA;
const int afterimageListSize = 20;

sf::Color hsl_to_rgb(sf::Color _hsl) {
	sf::Color ret;
	ret.a = _hsl.a;

	float hue = (float)(_hsl.r * 360.f) / 255.f;
	float saturation = (float)(_hsl.g) / 255.f;
	float luminance = (float)(_hsl.b) / 255.f;


	float chroma = (1.f - std::abs(2.f * luminance - 1.f)) * saturation;
	float x = chroma * (1.f - std::abs(std::fmod(hue, 2.f) - 1.f));
	float m = luminance - (.5f * chroma);

	sf::Color rgbPrime;
	if (hue < 60.f)			rgbPrime = sf::Color(chroma * 255.f, x * 255.f, 0);
	else if (hue < 120.f)	rgbPrime = sf::Color(x * 255.f, chroma * 255.f, 0);
	else if (hue < 180.f)	rgbPrime = sf::Color(0, chroma * 255.f, x * 255.f);
	else if (hue < 240.f)	rgbPrime = sf::Color(0, x * 255.f, chroma * 255.f);
	else if (hue < 300.f)	rgbPrime = sf::Color(x * 255.f, 0, chroma * 255.f);
	else					rgbPrime = sf::Color(chroma * 255.f, 0, x * 255.f);

	ret.r = (sf::Uint8)(rgbPrime.r + m);
	ret.g = (sf::Uint8)(rgbPrime.g + m);
	ret.b = (sf::Uint8)(rgbPrime.b + m);
	return ret;
}

Qix::Qix():Ennemy() {
	this->angle = 0.f;
	this->hue = 0.f;
	this->clr = sf::Color::Red;
	this->lifetime = 0.f;
	this->absPos = sf::Vector2f(this->pos);
	this->timerDirChange = 0.f;
	this->timerAngleChange = 0.f;
	this->timerColorChange = 0.f;
	this->timerAfterimages = 0.f;
}

Qix::Qix(Core* _core, GameField* _field):Ennemy(_core, _field, sf::Vector2u(_field->getSize().x / 2, _field->getSize().y / 2)) {
	this->angle = 0.f;
	this->hue = 0.f;
	this->clr = sf::Color::Red;
	this->lifetime = 0.f;
	this->absPos = sf::Vector2f(this->pos);
	this->timerDirChange = 0.f;
	this->timerAngleChange = 0.f;
	this->timerColorChange = 0.f;
	this->timerAfterimages = 0.f;

	this->field = field;
}

void Qix::update(GameField* _field, Player* _plr) {
	this->lifetime += tutil::getDelta();
	this->timerMove += tutil::getDelta();
	this->timerDirChange += tutil::getDelta();
	this->timerAngleChange += tutil::getDelta();
	this->timerColorChange += tutil::getDelta();
	this->timerAfterimages += tutil::getDelta();

	if (this->timerMove >= .025f) {
		this->timerMove -= .025f;
		this->absPos += this->direction;
		this->pos = sf::Vector2u(this->absPos);
	}

	sf::Vector2u posFuture = sf::Vector2u(this->absPos + this->direction * 20.f);
	FieldPixelState tileFuture = _field->getPixel(posFuture);
	if (this->timerDirChange > .5f || (tileFuture != UNCLAIMED && (tileFuture & TYPE_MASK) != STIX)) {
		this->timerDirChange = 0.f;
		bool valid = true;
		int attempts = 0;
		do {
			valid = true;
			this->direction = vect::polToRec(sf::Vector2f((float)(rand() % 15 + 1) / 10.f, (rand() % (int)(pi * 200)) * .01f));
			posFuture = sf::Vector2u(this->absPos + this->direction * 20.f);
			tileFuture = _field->getPixel(posFuture);
			if (tileFuture != UNCLAIMED && (tileFuture & TYPE_MASK) != STIX) {
				valid = false;
				attempts++;
			}
		} while (!valid && attempts < 50);
		if (attempts == 50) {
			this->direction = sf::Vector2f();
		}
	}

	if (this->timerAngleChange > .15f) {
		this->timerAngleChange -= .15f;
		this->angle += rand() % 61 - 30;
	}

	if (this->timerColorChange > .2f) {
		this->timerColorChange -= .2f;
		this->hue = std::fmod(this->hue + rand() % 31 - 10, 360.f);
		this->clr = hsl_to_rgb(sf::Color(this->hue * 255.f / 360.f, 255, 127));
	}

	if (this->timerAfterimages > .125f) {
		this->timerAfterimages -= .125f;
		this->afterimagesAngle.push_back(this->angle);
		if (this->afterimagesAngle.size() > afterimageListSize) this->afterimagesAngle.pop_front();
		this->afterimagesPos.push_back(this->pos);
		if (this->afterimagesPos.size() > afterimageListSize) this->afterimagesPos.pop_front();
		this->afterimagesColor.push_back(this->clr);
		if (this->afterimagesColor.size() > afterimageListSize) this->afterimagesColor.pop_front();
	}

	if (_plr->getTimerMove() > 0.f)
	{
		for (int i = 0; i < 49; i++) {
			sf::Vector2u vec(i % 7 - 3, i / 7 - 3);
			if ((_field->getPixel(this->pos + vec) & TYPE_MASK) == STIX) {
				_field->replaceAll(STIX_BLUE, UNCLAIMED);
				_field->replaceAll(STIX_RED, UNCLAIMED);
				_plr->returnToEdge();
				_field->generateTexture();
				break;
			}
		}
	}
}

void Qix::draw(GameField* _field) {
	Qix::renderVA.clear();
	Qix::renderVA.setPrimitiveType(sf::PrimitiveType::LineStrip);
	sf::Vector2f point1 = sf::Vector2f(this->pos + sf::Vector2u(vect::polToRec(sf::Vector2f(12, this->angle * pi / 180.f))) + _field->getRenderOffset());
	sf::Vector2f point2 = sf::Vector2f(this->pos - sf::Vector2u(vect::polToRec(sf::Vector2f(12, this->angle * pi / 180.f))) + _field->getRenderOffset());

	Qix::renderVA.append(sf::Vertex(point1, this->clr));
	Qix::renderVA.append(sf::Vertex(point2, this->clr));

	this->core->getWindow().draw(Qix::renderVA);

	for (int i = 0; i < this->afterimagesAngle.size(); i++) {
		Qix::renderVA.clear();
		Qix::renderVA.setPrimitiveType(sf::PrimitiveType::LineStrip);
		sf::Vector2f point1 = sf::Vector2f(this->afterimagesPos[i] + sf::Vector2u(vect::polToRec(sf::Vector2f(12, this->afterimagesAngle[i] * pi / 180.f))) + _field->getRenderOffset());
		sf::Vector2f point2 = sf::Vector2f(this->afterimagesPos[i] - sf::Vector2u(vect::polToRec(sf::Vector2f(12, this->afterimagesAngle[i] * pi / 180.f))) + _field->getRenderOffset());

		sf::Color clr = this->afterimagesColor[i];
		clr.a = 255 / this->afterimagesAngle.size() * i;
		Qix::renderVA.append(sf::Vertex(point1, clr));
		Qix::renderVA.append(sf::Vertex(point2, clr));

		this->core->getWindow().draw(Qix::renderVA);
	}
}