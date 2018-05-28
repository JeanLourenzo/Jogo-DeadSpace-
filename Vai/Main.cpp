#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML\Audio.hpp>
#include "Jogador.h"
#include "Inimigo.h"
#include "Chefe.h"
#include <vector>
#include <iostream>
#include <random>

using namespace sf;


int main()
{
inicio:

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1400, 800), "Dead Space");
	window.setFramerateLimit(60);


	// Lendo e iniciando texturas, e fonte
	sf::Texture NaveTexture;
	NaveTexture.loadFromFile("Imagens/ship1.png");

	sf::Texture ChefeTexture;
	ChefeTexture.loadFromFile("Imagens/boss1.png");

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
	gameOverTexto.setCharacterSize(60);
	gameOverTexto.setFillColor(Color::Red);
	gameOverTexto.setPosition(150.f, window.getSize().y / 2);
	gameOverTexto.setString("GAME OVER! JOGO REINICIANDO!");

	Text winnerTexto;
	winnerTexto.setFont(font);
	winnerTexto.setCharacterSize(60);
	winnerTexto.setFillColor(Color::Red);
	winnerTexto.setPosition(150.f, window.getSize().y / 2);
	winnerTexto.setString("UNIVERSO SALVO!");

	int delay = 0;
	int delay1 = 0;
	int mover = 1;

	// Criando objeto jogador
	Jogador p1(&NaveTexture);
	int tempoAtirando = 20;
	int score = 0;

	// Criando objeto chefe
	Chefe cf(&ChefeTexture, window.getSize());

	Text hpTexto;
	hpTexto.setFont(font);
	hpTexto.setCharacterSize(12);
	hpTexto.setFillColor(Color::White);

	Text bossHP;
	bossHP.setFont(font);
	bossHP.setCharacterSize(12);
	bossHP.setFillColor(Color::White);

	Text inimigoHP_Texto;
	inimigoHP_Texto.setFont(font);
	inimigoHP_Texto.setCharacterSize(12);
	inimigoHP_Texto.setFillColor(Color::White);


	// Criando vetor para inimigos e tempo de spaw
	int inimigoSpaw = 0;
	std::vector <Inimigo> inimigos;

	//Musica e tiro

	sf::Music music;
	music.openFromFile("som/1.wav");
	music.play();

	sf::SoundBuffer buffer;
	buffer.loadFromFile("som/tiro1.wav");

	sf::Sound sound;
	sound.setBuffer(buffer);



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

		//HPBOSS
		bossHP.setPosition(cf.corpo.getPosition().x, cf.corpo.getPosition().y - bossHP.getGlobalBounds().height);
		bossHP.setString("HP:" + std::to_string(cf.HP));


		//Checando para o player não sair da janela
		if (p1.corpo.getPosition().x <= 0) //Esquerda
			p1.corpo.setPosition(0.f, p1.corpo.getPosition().y);

		if (p1.corpo.getPosition().x >= window.getSize().x - p1.corpo.getGlobalBounds().width) //Direita
			p1.corpo.setPosition(window.getSize().x - p1.corpo.getGlobalBounds().width, p1.corpo.getPosition().y);

		if (p1.corpo.getPosition().y <= 0) //Topo
			p1.corpo.setPosition(p1.corpo.getPosition().x, 0.f);

		if (p1.corpo.getPosition().y >= window.getSize().y - p1.corpo.getGlobalBounds().height) //Baixo
			p1.corpo.setPosition(p1.corpo.getPosition().x, window.getSize().y - p1.corpo.getGlobalBounds().height);

		//Checando para o boss não sair da janela

		if (cf.corpo.getPosition().y <= 0) //Topo
			cf.corpo.setPosition(cf.corpo.getPosition().x, 0.f);

		if (cf.corpo.getPosition().y >= window.getSize().y - cf.corpo.getGlobalBounds().height) //Baixo
			cf.corpo.setPosition(cf.corpo.getPosition().x, window.getSize().y - cf.corpo.getGlobalBounds().height);


		// Limitando os tiros

		if (tempoAtirando < 20) {
			tempoAtirando++;
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Space) && tempoAtirando >= 20)
		{
			sound.play();
			p1.balas.push_back(Balas(&Bala1, p1.corpo.getPosition()));
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
					if (inimigos[k].HP <= 1)
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
		if (inimigoSpaw < 7)
		{
			inimigoSpaw++;
		}

		if (inimigoSpaw >= 7)
		{
			inimigos.push_back(Inimigo(&InimigoTexture, window.getSize()));
			inimigoSpaw = 0; // Resetando
		}


		// Movimentando inimigo
		for (size_t i = 0; i < inimigos.size(); i++)
		{
			inimigos[i].corpo.move(-16.0f, 0);

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


		// Movimentando Boss

		std::random_device numero;
		std::mt19937 eng(numero());

		// Sortendo números de 1 até 6.
		std::uniform_int_distribution<> xr(1, 5);


		if (xr(eng) == 1) {
			cf.corpo.move(0, -25.0f);
		}
		if (xr(eng) == 2 || xr(eng) == 4 || xr(eng) == 5) {
			cf.corpo.move(0, 0);
		}
		if (xr(eng) == 3) {
			cf.corpo.move(0, 25.0f);
		}

		// Deletando inimigo por colisões ou fora da tela

		for (size_t k = 0; k < p1.balas.size(); k++)
		{
			if (p1.balas[k].corpo.getGlobalBounds().intersects(cf.corpo.getGlobalBounds()))
			{
				p1.balas.erase(p1.balas.begin() + k);
				cf.HP--;
				break;
			}
	
		}

		// Imprimindo tudo na tela
		window.clear();
		window.draw(background);
		window.draw(p1.corpo);
		window.draw(cf.corpo);

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
		window.draw(bossHP);

		if (cf.HP == 0) {
			window.clear();
			window.draw(winnerTexto);

			if (delay1 == 200) {
				goto inicio;
			}

			delay1++;
		}

		if (p1.HP <= 0 && cf.HP > 0){
			window.draw(gameOverTexto);
			
			if (delay == 200) {
				goto inicio;
			}
			
			delay++;

		}

		window.display();
	}

	return 0;
}