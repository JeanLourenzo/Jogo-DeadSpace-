#include <SFML/Graphics.hpp>

using namespace sf;

class Chefe
{
public:

	Chefe(Texture *texturas, Vector2u janelaTam);

public:

	Sprite corpo;
	int HP;
	int HPMax;

};