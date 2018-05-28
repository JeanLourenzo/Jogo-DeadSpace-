#include <SFML\Graphics.hpp>
#include "Chefe.h"

Chefe::Chefe(Texture *texturas, Vector2u janelaTam)

{
	this->HPMax = 20;
	this->HP = this->HPMax;
	this->corpo.setTexture(*texturas);
	this->corpo.setScale(0.43f, 0.43f);
	this->corpo.setPosition(janelaTam.x - this->corpo.getGlobalBounds().width, rand() % (int)(janelaTam.y - this->corpo.getGlobalBounds().height));
}