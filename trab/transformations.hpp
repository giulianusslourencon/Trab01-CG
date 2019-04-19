#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include <cmath>
#include <iostream>

using namespace std;

class mat4;

class vec3 {
public:
    float data[4];

    vec3();
    vec3(float x, float y);
    vec3(float x, float y, float z);
    vec3(float x, float y, float z, float w);

    vec3 transform(mat4 transformation);

    vec3 operator+(vec3 other);

    void print();
};

class mat4 {
public:
    float data[16];

    mat4();
    mat4(float id);
    mat4(float data[16]);

    static mat4 multiply(mat4 m1, mat4 m2);

    static mat4 translate(mat4 original, vec3 direction);

    static mat4 rotate(mat4 original, float theta);
    static mat4 rotate(mat4 original, float theta, vec3 pivot);

    static mat4 scale(mat4 original, vec3 amount);
    static mat4 scale(mat4 original, vec3 amount, vec3 pivot);
};

#endif
