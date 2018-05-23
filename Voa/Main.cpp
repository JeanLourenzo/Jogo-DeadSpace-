#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Jogador.h"
#include "Inimigo.h"
#include <vector>
#include <iostream>
#include <Math.h>
#include <cstdlib>

using namespace sf;


int main()
{

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1000, 500), "Space Pirates");
	window.setFramerateLimit(60);


	// Lendo e iniciando texturas
	sf::Texture NaveTexture;
	NaveTexture.loadFromFile("Imagens/Ship1.png");

	sf::Texture InimigoTexture;
	InimigoTexture.loadFromFile("Imagens/alien1.png");
	
	sf::Texture Bala1;
	Bala1.loadFromFile("Imagens/bala1.png");

	sf::Texture fundo;
	fundo.loadFromFile("Imagens/space1.png");
	Sprite background(fundo);
	background.setPosition(-400,-350);
	background.setScale(0.6f, 0.6f);


	// Criando objeto jogador
	Jogador p1(&NaveTexture);
	int tempoAtirando = 20;

	// Criando vetor para inimigos e tempo de spaw
	int inimigoSpaw = 0;
	std::vector <Inimigo> inimigos;


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


		//Checando para o player não sair da janela
	if (p1.corpo.getPosition().x <= 0) //Esquerda
		p1.corpo.setPosition(0.f, p1.corpo.getPosition().y);

	if (p1.corpo.getPosition().x >= window.getSize().x - p1.corpo.getGlobalBounds().width) //Direita
		p1.corpo.setPosition(window.getSize().x - p1.corpo.getGlobalBounds().width, p1.corpo.getPosition().y);

	if (p1.corpo.getPosition().y <= 0) //Topo
		p1.corpo.setPosition(p1.corpo.getPosition().x, 0.f);

	if (p1.corpo.getPosition().y >= window.getSize().y - p1.corpo.getGlobalBounds().height) //Baixo
		p1.corpo.setPosition(p1.corpo.getPosition().x, window.getSize().y - p1.corpo.getGlobalBounds().height);


	// Limitando os tiros

	if (tempoAtirando < 20) {
		tempoAtirando++;
	}

		if (sf::Keyboard::isKeyPressed(Keyboard::Space) && tempoAtirando >= 20) 
		{
		p1.balas.push_back(Balas(&Bala1,p1.corpo.getPosition()));
		tempoAtirando = 0; // Resetando 
		}

		// Update do movimento das balas 
		for (size_t i = 0; i < p1.balas.size(); i++)
		{
			//Velocidade do tiro
			p1.balas[i].corpo.move(20.0f, 0.f);

			// Apagando balas fora da janela
			if (p1.balas[i].corpo.getPosition().x > window.getSize().x)
			{
				p1.balas.erase(p1.balas.begin() + i);
				break;
			}
			
			// Bala nas inimiga
			for (size_t k = 0; k < inimigos.size(); k++)
			{
				// Apaga bala e inimigo por colisão
				if (p1.balas[i].corpo.getGlobalBounds().intersects(inimigos[k].corpo.getGlobalBounds()))
				{
					inimigos.erase(inimigos.begin() + k);
					p1.balas.erase(p1.balas.begin() + i);
					break;

				}

			}
		}		

		// Spaw das inimiga
		if (inimigoSpaw < 25)
		{
			inimigoSpaw++;
		}

		if (inimigoSpaw >= 25)
		{
			inimigos.push_back(Inimigo(&InimigoTexture, window.getSize()));
			inimigoSpaw = 0; // Resetando
		}


		// Movimentando inimigo
		for (size_t i = 0; i < inimigos.size(); i++)
		{
			inimigos[i].corpo.move(-6.0f, 0);

			// Deletando inimigo por colisões ou fora da tela
			if (inimigos[i].corpo.getPosition().x <= 0 - inimigos[i].corpo.getGlobalBounds().width)
			{
				inimigos.erase(inimigos.begin() + i);
				break;
			}

			if (inimigos[i].corpo.getGlobalBounds().intersects(p1.corpo.getGlobalBounds()))
			{
				inimigos.erase(inimigos.begin() + i);
				p1.HP--;
				break;
			}

		}
		
		// Imprimindo tudo na tela
		window.clear();
		window.draw(background);
		window.draw(p1.corpo);

		for (size_t i = 0; i < p1.balas.size(); i++) 
		{
			window.draw(p1.balas[i].corpo);
		}
	
		for (size_t i = 0; i < inimigos.size(); i++)
		{
			window.draw(inimigos[i].corpo);
		}

		window.display();
	}

	return 0;
}