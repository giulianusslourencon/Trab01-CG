# Catavento
Trabalho 1 da disciplina de Computação Gráfica - SCC0250, oferecida no primeiro semestre do ano de 2019 no ICMC - Instituto de Ciências Matemáticas e de Computação da USP - Universidade de São Paulo, campus São Carlos.

## Contribuidores
Gabriel Alfonso Nascimento Salgueiro - 10284368<br>
Giuliano Lourençon - 10295590<br>
Pedro Francisco Darela Neto - 10295624

## Proposta
Implementar uma aplicação gráfica interativa 2D contendo um modelo simples de catavento composto por triângulos. O catavento deve girar em torno do próprio eixo seguindo uma velocidade angular pré-determinada pelo desenvolvedor. As estruturas de matrizes a serem utilizadas e todas as transformações necessárias devem ser implementadas, ou seja, sem utilização de bibliotecas auxiliares para manipulação de matrizes.
As seguintes ações interativas devem estar presentes no projeto:
* A cena mostra o catavento girando, e o usuário deve ser capaz de aumentar ou diminuir a velocidade angular de rotação do catavento utilizando comandos do teclado:
 * E, para aumentar a velocidade;
 * Q, para diminuir a velocidade;
 * Observe que, caso a velocidade fique negativa, o catavento deve girar na direção oposta. E em caso de velocidade nula, ele permanece parado, sem rotação.
* Ao pressionar a tecla de espaço, o catavento deve parar de girar;
 * Ao pressionar novamente a tecla de espaço, o catavento retoma a rotação;
* O catavento deve ser capaz de se mover pela cena 2D nas quatro direções paralelas aos eixos, por meio de ações de interação do usuário através das teclas:
 * W (para cima);
 * A (para esquerda);
 * S (para baixo); e
 * D (para direita);

## Compilação e Execução
### Linux
Para a compilação no Linux, é necessário ter instalado as bibliotecas...<br>
No terminal, vá para o diretório raiz do projeto (o qual se localiza o arquivo _Makefile_) e digite o comando "make" (sem aspas), para compilar.<br>
Para a execução do programa, digite "make run" (sem aspas) após a compilação.
