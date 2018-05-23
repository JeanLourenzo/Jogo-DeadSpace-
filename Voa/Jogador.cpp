#include <SFML\Graphics.hpp>
#include "Jogador.h"

using namespace sf;

Jogador::Jogador(sf::Texture *textura) {

	this->HPmax = 10;
	this->HP = this->HPmax;
	this->textura = textura;
	this->corpo.setTexture(*textura);
	this->corpo.setScale(0.05f, 0.05f);

}
/*
Jogador Update(Jogador p1){

if (Keyboard::isKeyPressed(Keyboard::W))
p1.corpo.move(0.f, -10.f);
if (Keyboard::isKeyPressed(Keyboard::A))
p1.corpo.move(-10.f, 0);
if (Keyboard::isKeyPressed(Keyboard::S))
p1.corpo.move(0.f, 10.f);
if (Keyboard::isKeyPressed(Keyboard::D))
p1.corpo.move(10.f, 0);

}
*/
