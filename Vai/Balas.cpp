#include <SFML/Graphics.hpp>
#include "Balas.h"


Balas::Balas(sf::Texture *textura, sf::Vector2f posição) {

	this->corpo.setTexture(*textura);
	this->corpo.setScale(0.3f, 0.3f);
	this->corpo.setPosition(posição);
}