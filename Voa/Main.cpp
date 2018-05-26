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


	// Lendo e iniciando texturas, e fonte
	sf::Texture NaveTexture;
	NaveTexture.loadFromFile("Imagens/Ship1.png");

	sf::Texture InimigoTexture;
	InimigoTexture.loadFromFile("Imagens/alien1.png");

	sf::Texture Bala1;
	Bala1.loadFromFile("Imagens/bala1.png");

	sf::Texture fundo;
	fundo.loadFromFile("Imagens/space1.png");
	Sprite background(fundo);
	background.setPosition(-400, -350);
	background.setScale(0.6f, 0.6f);

	Font font;
	font.loadFromFile("Fonts/Dosis-Light.ttf");

	//Iniciando os textos dos placares
	Text placar;
	placar.setFont(font);
	placar.setCharacterSize(20);
	placar.setFillColor(Color::White);
	placar.setPosition(10.f, 10.f);

	Text gameOverTexto;
	gameOverTexto.setFont(font);
	gameOverTexto.setCharacterSize(30);
	gameOverTexto.setFillColor(Color::Red);
	gameOverTexto.setPosition(100.f, window.getSize().y / 2);
	gameOverTexto.setString("GAME OVER!");


	// Criando objeto jogador
	Jogador p1(&NaveTexture);
	int tempoAtirando = 20;
	int score = 0;
	// aqui

	Text hpTexto;
	hpTexto.setFont(font);
	hpTexto.setCharacterSize(12);
	hpTexto.setFillColor(Color::White);

	Text inimigoHP_Texto;
	inimigoHP_Texto.setFont(font);
	inimigoHP_Texto.setCharacterSize(12);
	inimigoHP_Texto.setFillColor(Color::White);


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

		// Posição do texto e fazendo string
		hpTexto.setPosition(p1.corpo.getPosition().x, p1.corpo.getPosition().y - hpTexto.getGlobalBounds().height);
		hpTexto.setString("HP:" + std::to_string(p1.HP));


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
				// Apaga bala e inimigo, por colisão
				if (p1.balas[i].corpo.getGlobalBounds().intersects(inimigos[k].corpo.getGlobalBounds()))
				{
					//Inimigos tomando dano
					if (inimigos[i].HP <= 1)
					{
						score += inimigos[k].HPMax;
						inimigos.erase(inimigos.begin() + k);
					}
					else {
						inimigos[k].HP--;
					}

					p1.balas.erase(p1.balas.begin() + i);
					break;

				}

			}
		}		

		// Spaw das inimiga
		if (inimigoSpaw < 30)
		{
			inimigoSpaw++;
		}

		if (inimigoSpaw >= 30)
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
			//Placar Update
			placar.setString("Score: " + std::to_string(score));
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

			inimigoHP_Texto.setString("HP:" + std::to_string(inimigos[i].HP));
			inimigoHP_Texto.setPosition(inimigos[i].corpo.getPosition().x, inimigos[i].corpo.getPosition().y - inimigoHP_Texto.getGlobalBounds().height);
			window.draw(inimigoHP_Texto);
			window.draw(inimigos[i].corpo);

		}

		window.draw(placar);
		window.draw(hpTexto);

		if (p1.HP <= 0)
			window.draw(gameOverTexto);

		window.display();
	}

	return 0;
}