#include <SFML/Graphics.hpp>
#include "Balas.h"
#include "Aliens.h"
#include <vector>
#include <iostream>

class Jogador : public Aliens {

public:

	Jogador(sf::Texture *textura, sf::Vector2u janelaTam) : Aliens(textura, janelaTam) {
	}

	String texto() {
		return a;
	}
	
public:
	String a = "Humans Will Triumph!!";
	std::vector <Balas> balas;
	
};
