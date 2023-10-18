    Nome e RA dos integrantes do grupo.
    Luiz Paulo Nambu 11069014
    Danilo Shinki Yoshizato 11108913


    Para jogar a aplicação, utilize o mouse para chegar até carta desejada, e o botão esquerdo do mouse para a escolher.

    A aplicação realizada é um jogo da memória, baseada no código de implementação da aula de tictactoe.
    O objetivo do jogo é encontrar todos os pares em no máximo 20 jogadas.
    O jogo contém um tabuleiro de 4x4, totalizando 16 cartas, que são randomizadas a cada partida utilizando a <random> da biblioteca padrão do C++, e realizando uma função shuffle do começo ao fim do grid de cartas.
    Cada carta é revelada ao clicar com o mouse, ao clicar na segunda carta, uma função de comparação é chamada, aumentando a pontuaçao do jogador, caso acerte.
    Se o jogador errar o par, as cartas são escondidas novamente utilizando o espaço em branco ' '.
    A cada jogada, é realizado o loop para verificar as condiçoes de fim de jogo. Caso o jogador complete 8 pontos, ele recebe uma mensagem de vitória, se ele realizar 20 jogadas e não alcansar 8 pontos, ele receberá uma mensagem de derrota.
    Ao final do jogo, o botão de reiniciar pode ser utilizado para jogar novamente.