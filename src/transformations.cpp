#include "transformations.hpp"

// Inicializa um vetor homogenizado na origem (0, 0, 0)
vec3::vec3(){
    this->data[0] = 0.0;
    this->data[1] = 0.0;
    this->data[2] = 0.0;
    this->data[3] = 1.0;
}

// Inicializa um vetor homogenizado nas coordenadas (x, y, 0)
vec3::vec3(float x, float y){
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = 0.0;
    this->data[3] = 1.0;
}

// Inicializa um vetor homogenizado nas coordenadas (x, y, z)
vec3::vec3(float x, float y, float z){
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
    this->data[3] = 1.0;
}

// Inicializa um vetor nas coordenadas (x, y, z) e parametro homogeneo h
vec3::vec3(float x, float y, float z, float h){
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
    this->data[3] = h;
}

// Multiplica o vetor pela matriz de transformacao e aplica a homogenizacao no final
vec3 vec3::transform(mat4 transformation){
    vec3 result;

    // Multiplicacao entre vetor (1x4) e matriz (4x4), resultando em outro vetor (1x4)
    for (int j = 0; j < 4; j++){
        float aux = 0.0;
        for (int k = 0; k < 4; k++){
            aux += this->data[k] * transformation.data[4*k+j];
        }
        result.data[j] = aux;
    }

    // Homogenizacao do vetor resultante
    for (int i = 0; i < 4; i++){
        result.data[i] /= result.data[3];
    }

    return result;
}

// Soma de vetores, mantendo o parametro homogeneo
vec3 vec3::operator+(vec3 other){
    return vec3(this->data[0] + other.data[0], this->data[1] + other.data[1], this->data[2] + other.data[2]);
}

// Multiplicacao de vetor por escalar, mantendo o parametro homogeneo
vec3 vec3::operator*(float f){
    return vec3(this->data[0] * f, this->data[1] * f, this->data[2] * f);
}

// Imprime o vetor no formato (x, y, z)
void vec3::print(){
    cout << "(" << this->data[0] << ", "
                << this->data[1] << ", "
                << this->data[2] << ")" << endl;
}

// -------------------------------------------------------------


// Inicializa uma matriz (4x4) nula
mat4::mat4(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            this->data[4*i+j] = 0;
        }
    }
}

// Inicializa uma matriz (4x4) no formato da identidade com o valor 'id' na diagonal principal
mat4::mat4(float id){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            this->data[4*i+j] = (i == j) * id;
        }
    }
}

// Inicializa uma matriz (4x4) com os dados fornecidos
mat4::mat4(float data[16]){
    for (int i = 0; i < 16; i++){
        this->data[i] = data[i];
    }
}


// Multiplica duas matrizes (4x4)
mat4 mat4::multiply(mat4 m1, mat4 m2){
    mat4 result;

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            float aux = 0.0;
            for (int k = 0; k < 4; k++){
                aux += m1.data[4*i+k] * m2.data[4*k+j];
            }
            result.data[4*i+j] = aux;
        }
    }

    return result;
}

// Aplica a funcao de translacao na matriz original na direcao 'direction' dada
mat4 mat4::translate(mat4 original, vec3 direction){
    float m[] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        direction.data[0], direction.data[1],
                        direction.data[2], 1.0};
    return multiply(original, mat4(m)); // Multiplica a matriz original pela matriz de translacao
}


// Aplica a funcao de rotacao pelo eixo Z por 'theta' radianos na matriz original
mat4 mat4::rotate(mat4 original, float theta){
    float m[] = {cos(theta), sin(theta), 0.0, 0.0,
                        -sin(theta), cos(theta), 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};
    return multiply(original, mat4(m)); // Multiplica a matriz original pela matriz de rotacao
}

// Aplica a funcao de rotacao pelo eixo Z por 'theta' radianos na matriz original, tomando o pivot dado
mat4 mat4::rotate(mat4 original, float theta, vec3 pivot){
    float m[] = {cos(theta), sin(theta), 0.0, 0.0,
                        -sin(theta), cos(theta), 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        pivot.data[0] - pivot.data[0] * cos(theta) + pivot.data[1] * sin(theta),
                        pivot.data[1] - pivot.data[1] * cos(theta) - pivot.data[0] * sin(theta),
                        0.0, 1.0};
    return multiply(original, mat4(m)); // Multiplica a matriz original pela matriz de rotacao
}


// Aplica a funcao de escala na matriz original, com valores dados em 'amount'
mat4 mat4::scale(mat4 original, vec3 amount){
    float m[] = {amount.data[0], 0.0, 0.0, 0.0,
                        0.0, amount.data[1], 0.0, 0.0,
                        0.0, 0.0, amount.data[2], 0.0,
                        0.0, 0.0, 0.0, 1.0};
    return multiply(original, mat4(m)); // Multiplica a matriz original pela matriz de escala
}


// Aplica a funcao de escala na matriz original, com valores dados em 'amount' e o 'pivot' fornecido
mat4 mat4::scale(mat4 original, vec3 amount, vec3 pivot){
    float m[] = {amount.data[0], 0.0, 0.0, 0.0,
                        0.0, amount.data[1], 0.0, 0.0,
                        0.0, 0.0, amount.data[2], 0.0,
                        pivot.data[0] * (1 - amount.data[0]),
                        pivot.data[1] * (1 - amount.data[1]),
                        pivot.data[2] * (1 - amount.data[2]), 1.0};
    return multiply(original, mat4(m)); // Multiplica a matriz original pela matriz de escala
}
