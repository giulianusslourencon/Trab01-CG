#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include <cmath>
#include <iostream>

using namespace std;

class mat4;

// Classe que representa um vetor de 3 dimensões
class vec3 {
public:
    // Dados das coordenadas do vetor (x, y, z) + parametro de homogenizacao (h)
    float data[4];

    // Construtores da classe
    vec3();
    vec3(float x, float y);
    vec3(float x, float y, float z);
    vec3(float x, float y, float z, float h);

    // Multiplica o vetor por uma matriz de transformacao
    vec3 transform(mat4 transformation);

    // Sobrecarga de operadores
    vec3 operator+(vec3 other);
    vec3 operator*(float f);

    // Imprime o vetor na tela de output
    void print();
};

// Classe que representa uma matriz 4x4 utilizada nas transformacoes
class mat4 {
public:
    // Dados das posicoes da matriz, ja homogenizada
    float data[16];

    // Construtores da matriz
    mat4();
    mat4(float id);
    mat4(float data[16]);

    // Funcao de multiplicacao entre duas matrizes
    static mat4 multiply(mat4 m1, mat4 m2);

    // Transformacao de translacao
    static mat4 translate(mat4 original, vec3 direction);

    // Transformacoes de rotacao ao redor do eixo Z, sem e com pivot
    static mat4 rotate(mat4 original, float theta);
    static mat4 rotate(mat4 original, float theta, vec3 pivot);

    // Transformacoes de escala, sem e com pivot
    static mat4 scale(mat4 original, vec3 amount);
    static mat4 scale(mat4 original, vec3 amount, vec3 pivot);
};

#endif
