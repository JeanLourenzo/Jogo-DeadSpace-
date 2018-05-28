#include <SFML/Graphics.hpp>
#include "Balas.h"
#include <vector>

class Jogador {

public:

	Jogador(sf::Texture *textura);

	//Jogador Update(Jogador p1);

public:

	std::vector <Balas> balas;
	
	sf::Sprite corpo;
	int HP;
	int HPmax;

};
