# Jogo-Lab

Controles direcionais:
W = Cima;
A = Esquerda;
S = Baixo;
D = Direita
Espaço = Tiro de lasers;

Problema ao reconheçer a Biblioteca SFML:
- Todos salvam arquivos em lugares diferentes, assim os endereços de diretórios mudam. Se o projeto não rodar, 
arrume o diretório do Include e do Lib.

Include: 
Clicar com direito no projeto 'Vai' > Propriedades > C/C++ > Geral > Diretórios de inclusão Adicionais > Editar
> Clique em cima do nome e nos '...' > Vá até a pasta do jogo > sfml > Selecione a pasta 'include' > Ok.

Lib:
Clicar com direito no projeto 'Vai' > Propriedades > Vinculador > Diretórios de bibliotecas Adicionais > Editar
> Clieque em cima do nome e nos '..' > Vá até a pasta do jogo > sfml > Selecione a pasta 'lib' > Ok.
