#include <SFML\Graphics.hpp>
#include "Aliens.h"

Aliens::Aliens(Texture *texturas, Vector2u janelaTam)

{
	this->maxI = rand() % 2 + 1;
	this->HPi = this->maxI;

	this->maxC = 20;
	this->HPc = this->maxC;
	
	this->maxP = 10;
	this->HPp = this->maxP;

	this->corpoI.setTexture(*texturas);
	this->corpoC.setTexture(*texturas);
	this->corpoP.setTexture(*texturas);

	this->corpoI.setScale(0.05f, 0.05f);
	this->corpoC.setScale(0.5f, 0.5f);
	this->corpoP.setScale(0.05f, 0.05f);

	this->corpoI.setPosition(janelaTam.x - this->corpoI.getGlobalBounds().width, rand() % (int)(janelaTam.y - this->corpoI.getGlobalBounds().height));
	this->corpoC.setPosition(janelaTam.x - this->corpoC.getGlobalBounds().width, 200);
}
