#include "transformations.hpp"

vec3::vec3(){
    this->data[0] = 0.0;
    this->data[1] = 0.0;
    this->data[2] = 0.0;
    this->data[3] = 1.0;
}

vec3::vec3(float x, float y){
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = 0.0;
    this->data[3] = 1.0;
}

vec3::vec3(float x, float y, float z){
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
    this->data[3] = 1.0;
}

vec3::vec3(float x, float y, float z, float w){
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
    this->data[3] = w;
}

vec3 vec3::transform(mat4 transformation){
    vec3 result;

    for (int j = 0; j < 4; j++){
        float aux = 0.0;
        for (int k = 0; k < 4; k++){
            aux += this->data[k] * transformation.data[4*k+j];
        }
        result.data[j] = aux;
    }

    for (int i = 0; i < 4; i++){
        result.data[i] /= result.data[3];
    }

    return result;
}

void vec3::print(){
    cout << "(" << this->data[0] << ", "
                << this->data[1] << ", "
                << this->data[2] << ")" << endl;
}

// -------------------------------------------------------------

mat4::mat4(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            this->data[4*i+j] = 0;
        }
    }
}

mat4::mat4(float id){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            this->data[4*i+j] = (i == j) * id;
        }
    }
}

mat4::mat4(float data[16]){
    for (int i = 0; i < 16; i++){
        this->data[i] = data[i];
    }
}

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

mat4 mat4::translate(mat4 original, vec3 direction){
    float m[] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        direction.data[0], direction.data[1],
                        direction.data[2], 1.0};
    return multiply(original, mat4(m));
}

mat4 mat4::rotate(mat4 original, float theta){
    float m[] = {cos(theta), sin(theta), 0.0, 0.0,
                        -sin(theta), cos(theta), 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};
    return multiply(original, mat4(m));
}

mat4 mat4::rotate(mat4 original, float theta, vec3 pivot){
    float m[] = {cos(theta), sin(theta), 0.0, 0.0,
                        -sin(theta), cos(theta), 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        pivot.data[0] - pivot.data[0] * cos(theta) + pivot.data[1] * sin(theta),
                        pivot.data[1] - pivot.data[1] * cos(theta) - pivot.data[0] * sin(theta),
                        0.0, 1.0};
    return multiply(original, mat4(m));
}

mat4 mat4::scale(mat4 original, vec3 amount){
    float m[] = {amount.data[0], 0.0, 0.0, 0.0,
                        0.0, amount.data[1], 0.0, 0.0,
                        0.0, 0.0, amount.data[2], 0.0,
                        0.0, 0.0, 0.0, 1.0};
    return multiply(original, mat4(m));
}

mat4 mat4::scale(mat4 original, vec3 amount, vec3 pivot){
    float m[] = {amount.data[0], 0.0, 0.0, 0.0,
                        0.0, amount.data[1], 0.0, 0.0,
                        0.0, 0.0, amount.data[2], 0.0,
                        pivot.data[0] * (1 - amount.data[0]),
                        pivot.data[1] * (1 - amount.data[1]),
                        pivot.data[2] * (1 - amount.data[2]), 1.0};
    return multiply(original, mat4(m));
}
