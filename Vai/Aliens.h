#include <SFML/Graphics.hpp>

using namespace sf;

class Aliens
{
public:

	Aliens(Texture *texturas, Vector2u janelaTam);

	virtual String texto() = 0;

public:

	Sprite corpoI, corpoC, corpoP;
	int HPi, HPc, HPp;
	int maxI, maxC, maxP;

};