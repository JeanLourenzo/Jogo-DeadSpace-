#include <SFML/Graphics.hpp>
#include "Balas.h"


Balas::Balas(sf::Texture *textura) {

	this->corpo.setTexture(*textura);
	this->corpo.setScale(0.2f, 0.2f);

}