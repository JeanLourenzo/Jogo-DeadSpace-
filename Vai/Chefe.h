#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Chefe : public Aliens
{
public:

	Chefe(Texture *texturas, Vector2u janelaTam) : Aliens(texturas, janelaTam) {
	}

	String texto(){
		return c;
	}

public:
	String c = "ATTACK!!";

};