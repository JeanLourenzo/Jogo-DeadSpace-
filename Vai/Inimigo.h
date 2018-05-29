#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Inimigo : public Aliens {
public:

	Inimigo(Texture *texturas, Vector2u janelaTam) : Aliens(texturas, janelaTam) {
	}
	
	String texto() {
		return i;
	}

public:
	String i = "Attack!!";

};