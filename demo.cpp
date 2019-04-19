#include <cg_window.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    vec3 operator+=(vec3 other);
    vec3 operator*(float f);

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

vec3 vec3::operator+(vec3 other){
    return vec3(this->data[0] + other.data[0], this->data[1] + other.data[1], this->data[2] + other.data[2]);
}

vec3 vec3::operator+=(vec3 other){
    return vec3(this->data[0] + other.data[0], this->data[1] + other.data[1], this->data[2] + other.data[2]);
}

vec3 vec3::operator*(float f){
    return vec3(this->data[0] * f, this->data[1] * f, this->data[2] * f);
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







class Demo : public cgicmc::Window {
public:
  Demo() : cgicmc::Window() {}

  void run() override {

    float lastTime = (float)glfwGetTime();
    float thisTime = (float)glfwGetTime();

    float rotAmount = 0.0f;
    float vel = 1.0f;

    bool rotating = true;

    vec3 position;

    while (!glfwWindowShouldClose(_window)) {

        float deltaTime = thisTime - lastTime;
      // Comandos de entrada
      processInput();

      // Comandos de renderizacao vao aqui
      glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      // etc...

      mat4 transform = mat4(1.0f);

        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
            position = position + vec3(0.0, 1.0) * deltaTime;

        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
            position = position + vec3(0.0, -1.0) * deltaTime;

        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
            position = position + vec3(-1.0, 0.0) * deltaTime;

        if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
            position = position + vec3(1.0, 0.0) * deltaTime;

        if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
            rotating = !rotating;

        if (rotating){

            if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
                vel += 0.1;

            if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
                vel -= 0.1;

            rotAmount += vel * deltaTime;
        }

        transform = mat4::translate(transform, position);
        transform = mat4::rotate(transform, rotAmount, position);

      glUseProgram(shaderProgramId);
      unsigned int transformLoc =
          glGetUniformLocation(shaderProgramId, "transform");
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform.data);

      glBindVertexArray(_VAO);
      glDrawArrays(GL_TRIANGLES, 0, 12);
      // Controla eventos e troca os buffers para renderizacao
      glfwSwapBuffers(_window);
      glfwPollEvents();

      lastTime = thisTime;
      thisTime = (float)glfwGetTime();
    }
  }

  void prepare() {
    float array[] = {   0.0f, 0.0f, 0.0f,   0.5f, 0.0f, 0.0f,   0.5f, 0.5f, 0.0,
                        0.0f, 0.0f, 0.0f,   0.0f, 0.5f, 0.0f,   -0.5f, 0.5f, 0.0,
                        0.0f, 0.0f, 0.0f,   -0.5f, 0.0f, 0.0f,   -0.5f, -0.5f, 0.0,
                        0.0f, 0.0f, 0.0f,   0.0f, -0.5f, 0.0f,   0.5f, -0.5f, 0.0};
    _vertices.insert(_vertices.begin(), array, array + 36);

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertices.size(),
                 _vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  unsigned int loadVertexShader() {
    _vertexShader = "#version 330 core\n"
                    "layout(location = 0) in vec3 aPos;\n"
                    "uniform mat4 transform;\n"
                    "void main() {\n"
                    "gl_Position = transform * vec4(aPos, 1.0f);\n"
                    "}\0";

    unsigned int vertexShaderId;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &_vertexShader, NULL);
    glCompileShader(vertexShaderId);

    int succes;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &succes);
    if (!succes) {
      char infoLog[512];
      glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
      std::cerr << "Vertex shader error: " << infoLog << std::endl;
    }
    return vertexShaderId;
  }

  unsigned int loadFragmentShader() {
    const char *shaderSource = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "void main()\n"
                               "{\n"
                               "   FragColor = vec4(0.6f, 0.8f, 0.8f, 1.0f);\n"
                               "}\n\0";
    unsigned int fragmentShaderId;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &shaderSource, NULL);
    glCompileShader(fragmentShaderId);

    int success = 0;
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
      std::cout << "Shader source: " << shaderSource << std::endl;
      std::cerr << "Fragment shader error: " << infoLog << std::endl;
    }
    return fragmentShaderId;
  }

  void loadShaders() {
    unsigned int vshader, fshader;
    vshader = loadVertexShader();
    fshader = loadFragmentShader();

    shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, fshader);
    glAttachShader(shaderProgramId, vshader);
    glLinkProgram(shaderProgramId);

    int success;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
      std::cerr << "Program shader error: " << infoLog << std::endl;
    }

    glDeleteShader(vshader);
    glDeleteShader(fshader);
  }

protected:
  std::vector<float> _vertices;
  const char *_vertexShader;
  int shaderProgramId;
  unsigned int _VBO, _VAO;
};

int main(int argc, char const *argv[]) {
  Demo window;
  window.createWindow();
  window.loadShaders();
  window.prepare();
  window.run();
}
