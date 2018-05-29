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
	// Apenas para dar um loop facilmente no final do progama
	inicio:

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
	font.loadFromFile("Fonts/one.ttf");

	Font font1;
	font1.loadFromFile("Fonts/two.ttf");

	//Iniciando os textos dos placares
	Text placar;
	placar.setFont(font1);
	placar.setCharacterSize(30);
	placar.setFillColor(Color::White);
	placar.setPosition(10.f, 10.f);

	Text gameOverTexto;
	gameOverTexto.setFont(font);
	gameOverTexto.setCharacterSize(100);
	gameOverTexto.setFillColor(Color::Red);
	gameOverTexto.setPosition(150.f, window.getSize().y / 2);
	gameOverTexto.setString("GAME OVER! JOGO REINICIANDO!");

	Text winnerTexto;
	winnerTexto.setFont(font);
	winnerTexto.setCharacterSize(100);
	winnerTexto.setFillColor(Color::Red);
	winnerTexto.setPosition(150.f, window.getSize().y / 2);
	winnerTexto.setString("UNIVERSO SALVO!");


	int delay = 0;
	int delay1 = 0;
	int delayTexto = 0;

	// Criando objeto jogador
	Jogador p1(&NaveTexture, window.getSize());
	int tempoAtirando = 20;
	int score = 0;

	// Criando objeto chefe
	Chefe cf(&ChefeTexture, window.getSize());

	Text hpTexto;
	hpTexto.setFont(font1);
	hpTexto.setCharacterSize(12);
	hpTexto.setFillColor(Color::White);

	Text bossHP;
	bossHP.setFont(font1);
	bossHP.setCharacterSize(12);
	bossHP.setFillColor(Color::White);

	Text inimigoHP_Texto;
	inimigoHP_Texto.setFont(font1);
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

	sf::SoundBuffer rugido;
	rugido.loadFromFile("som/rugido1.wav");

	sf::Sound roar;
	roar.setBuffer(rugido);

	// Mensagem através de Polimorfismo

	std::vector <Aliens*> aliens;

	aliens.push_back(new Jogador(&NaveTexture, window.getSize()));
	aliens.push_back(new Inimigo(&InimigoTexture, window.getSize()));
	aliens.push_back(new Chefe(&ChefeTexture, window.getSize()));

	aliens[1]->texto();
	aliens[2]->texto();

	Text Jog;
	Jog.setFont(font);
	Jog.setCharacterSize(32);
	Jog.setFillColor(Color::Red);
	Jog.setString(aliens[0]->texto());

	Text Ini;
	Ini.setFont(font);
	Ini.setCharacterSize(26);
	Ini.setFillColor(Color::Red);
	Ini.setString(aliens[1]->texto());

	Text Chef;
	Chef.setFont(font);
	Chef.setCharacterSize(32);
	Chef.setFillColor(Color::Red);
	Chef.setString(aliens[2]->texto());


	while (window.isOpen())
	{
		sf::Clock clock;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Movimento do Jogador
		if (Keyboard::isKeyPressed(Keyboard::W))
			p1.corpoP.move(0.f, -10.f);
		if (Keyboard::isKeyPressed(Keyboard::A))
			p1.corpoP.move(-10.f, 0);
		if (Keyboard::isKeyPressed(Keyboard::S))
			p1.corpoP.move(0.f, 10.f);
		if (Keyboard::isKeyPressed(Keyboard::D))
			p1.corpoP.move(10.f, 0);

		// Posição do texto e fazendo string
		hpTexto.setPosition(p1.corpoP.getPosition().x, p1.corpoP.getPosition().y - hpTexto.getGlobalBounds().height);
		hpTexto.setString("HP:" + std::to_string(p1.HPp));

		//HPBOSS
		bossHP.setPosition(cf.corpoC.getPosition().x, cf.corpoC.getPosition().y - bossHP.getGlobalBounds().height);
		bossHP.setString("HP:" + std::to_string(cf.HPc));

		// Mensagens seguindo player

		Jog.setPosition(p1.corpoP.getPosition().x, p1.corpoP.getPosition().y -30 - Jog.getGlobalBounds().height);
		Chef.setPosition(cf.corpoC.getPosition().x- 30, cf.corpoC.getPosition().y + -30 - Chef.getGlobalBounds().height);


		//Checando para o player não sair da janela
		if (p1.corpoP.getPosition().x <= 0) //Esquerda
			p1.corpoP.setPosition(0.f, p1.corpoP.getPosition().y);

		if (p1.corpoP.getPosition().x >= window.getSize().x - p1.corpoP.getGlobalBounds().width) //Direita
			p1.corpoP.setPosition(window.getSize().x - p1.corpoP.getGlobalBounds().width, p1.corpoP.getPosition().y);

		if (p1.corpoP.getPosition().y <= 0) //Topo
			p1.corpoP.setPosition(p1.corpoP.getPosition().x, 0.f);

		if (p1.corpoP.getPosition().y >= window.getSize().y - p1.corpoP.getGlobalBounds().height) //Baixo
			p1.corpoP.setPosition(p1.corpoP.getPosition().x, window.getSize().y - p1.corpoP.getGlobalBounds().height);

		//Checando para o boss não sair da janela

		if (cf.corpoC.getPosition().y <= 0) //Topo
			cf.corpoC.setPosition(cf.corpoC.getPosition().x, 0.f);

		if (cf.corpoC.getPosition().y >= window.getSize().y - cf.corpoC.getGlobalBounds().height) //Baixo
			cf.corpoC.setPosition(cf.corpoC.getPosition().x, window.getSize().y - cf.corpoC.getGlobalBounds().height);


		// Limitando os tiros

		if (tempoAtirando < 20) {
			tempoAtirando++;
		}

		sf::Time passou = clock.getElapsedTime();

		if (passou.asMilliseconds() >= 0.1) {
			roar.play();
			clock.restart();
		}



		if (sf::Keyboard::isKeyPressed(Keyboard::Space) && tempoAtirando >= 20)
		{
			sound.play();
			p1.balas.push_back(Balas(&Bala1, p1.corpoP.getPosition()));
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
				if (p1.balas[i].corpo.getGlobalBounds().intersects(inimigos[k].corpoI.getGlobalBounds()))
				{
					//Inimigos tomando dano
					if (inimigos[k].HPi <= 1)
					{
						score += inimigos[k].maxI;
						inimigos.erase(inimigos.begin() + k);
					}
					else {
						inimigos[k].HPi--;
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
			inimigos[i].corpoI.move(-16.0f, 0);

			// Deletando inimigo por colisões ou fora da tela
			if (inimigos[i].corpoI.getPosition().x <= 0 - inimigos[i].corpoI.getGlobalBounds().width)
			{
				inimigos.erase(inimigos.begin() + i);
				break;
			}

			if (inimigos[i].corpoI.getGlobalBounds().intersects(p1.corpoP.getGlobalBounds()))
			{
				inimigos.erase(inimigos.begin() + i);
				p1.HPp--;
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
			cf.corpoC.move(0, -25.0f);
		}
		if (xr(eng) == 2 || xr(eng) == 4 || xr(eng) == 5) {
			cf.corpoC.move(0, 0);
		}
		if (xr(eng) == 3) {
			cf.corpoC.move(0, 25.0f);
		}

		// Boss levando dano

		for (size_t k = 0; k < p1.balas.size(); k++)
		{
			if (p1.balas[k].corpo.getGlobalBounds().intersects(cf.corpoC.getGlobalBounds()))
			{
				p1.balas.erase(p1.balas.begin() + k);
				cf.HPc--;
				break;
			}
	
		}


		// Imprimindo tudo na tela
		window.clear();
		window.draw(background);
		window.draw(p1.corpoP);
		window.draw(cf.corpoC);

		for (size_t i = 0; i < p1.balas.size(); i++)
		{
			window.draw(p1.balas[i].corpo);

		}

		for (size_t i = 0; i < inimigos.size(); i++)
		{

			Ini.setPosition(inimigos[i].corpoI.getPosition().x - 30, inimigos[i].corpoI.getPosition().y + -30 );
			inimigoHP_Texto.setString("HP:" + std::to_string(inimigos[i].HPi));
			inimigoHP_Texto.setPosition(inimigos[i].corpoI.getPosition().x, inimigos[i].corpoI.getPosition().y - inimigoHP_Texto.getGlobalBounds().height);
			window.draw(inimigoHP_Texto);
			window.draw(inimigos[i].corpoI);

		}

		// Temmpo para ficar mensagem na tela.

		if (delayTexto < 300) {
			window.draw(Jog);
			window.draw(Ini);
			window.draw(Chef);
			delayTexto++;
		}

		window.draw(placar);
		window.draw(hpTexto);
		window.draw(bossHP);


		if (p1.HPp <= 0 && cf.HPc > 0){
			window.draw(gameOverTexto);
			
			if (delay == 200) {
				goto inicio;
			}
			
			delay++;

		}

		if (cf.HPc <= 0) {

			window.draw(winnerTexto);
			if (delay == 200) {
				goto inicio;
			}

			delay++;
		}

		window.display();

	}

	return 0;
}