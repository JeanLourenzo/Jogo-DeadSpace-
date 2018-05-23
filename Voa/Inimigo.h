#include <SFML/Graphics.hpp>

using namespace sf;

class Inimigo
{
public:

	Inimigo(Texture *texturas, Vector2u janelaTam);
		
public:

	Sprite corpo;
	int HP;
	int HPMax;

};