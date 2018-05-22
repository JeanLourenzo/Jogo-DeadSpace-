#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Jogador.h"
#include <vector>
#include <iostream>
#include <Math.h>
#include <cstdlib>

using namespace sf;

int main()
{

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1000, 500), "Navy Attack");
	window.setFramerateLimit(60);


	// Iniciando Texturas
	sf::Texture NaveTexture;
	NaveTexture.loadFromFile("Ship1.png");

	sf::Texture InimigoTexture;
	InimigoTexture.loadFromFile("alien1.png");
	
	sf::Texture Bala1;
	Bala1.loadFromFile("bala1.png");


	// Criando objeto Jogador
	Jogador p1(&NaveTexture);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Movimento do Jogador
		if (Keyboard::isKeyPressed(Keyboard::W))
			p1.corpo.move(0.f, -10.f);
		if (Keyboard::isKeyPressed(Keyboard::A))
			p1.corpo.move(-10.f, 0);
		if (Keyboard::isKeyPressed(Keyboard::S))
			p1.corpo.move(0.f, 10.f);
		if (Keyboard::isKeyPressed(Keyboard::D))
			p1.corpo.move(10.f, 0);


		//Colisão para não sair da janela
	if (p1.corpo.getPosition().x <= 0) //Esquerda
		p1.corpo.setPosition(0.f, p1.corpo.getPosition().y);

	if (p1.corpo.getPosition().x >= window.getSize().x - p1.corpo.getGlobalBounds().width) //Direita
		p1.corpo.setPosition(window.getSize().x - p1.corpo.getGlobalBounds().width, p1.corpo.getPosition().y);

	if (p1.corpo.getPosition().y <= 0) //Topo
		p1.corpo.setPosition(p1.corpo.getPosition().x, 0.f);

	if (p1.corpo.getPosition().y >= window.getSize().y - p1.corpo.getGlobalBounds().height) //Baixo
		p1.corpo.setPosition(p1.corpo.getPosition().x, window.getSize().y - p1.corpo.getGlobalBounds().height);

		//Tiros
		if (sf::Mouse::isButtonPressed(Mouse::Left)) 
		{
		p1.balas.push_back(Balas(&Bala1));
		}

		// Balas fora da janela 
		for (size_t i = 0; i < p1.balas.size(); i++) {

			if (p1.balas[i].corpo.getPosition().x > window.getSize().x) {

				p1.balas.erase(p1.balas.begin() + i);

			}

		}

		window.clear();
		window.draw(p1.corpo);

		for (size_t i = 0; i < p1.balas.size(); i++) {
			window.draw(p1.balas[i].corpo);
		}
	
		window.display();
	}

	return 0;
}