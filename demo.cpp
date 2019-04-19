#include <cg_window.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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






// Inicializa um vetor homogenizado na origem
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

// Aplica a funcao de translacao na matriz original na direcao direction dada
mat4 mat4::translate(mat4 original, vec3 direction){
    float m[] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        direction.data[0], direction.data[1],
                        direction.data[2], 1.0};
    return multiply(original, mat4(m));
}

// Aplica a funcao de rotacao pelo eixo Z por theta radianos na matriz original
mat4 mat4::rotate(mat4 original, float theta){
    float m[] = {cos(theta), sin(theta), 0.0, 0.0,
                        -sin(theta), cos(theta), 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};
    return multiply(original, mat4(m));
}

// Aplica a funcao de rotacao pelo eixo Z por theta radianos na matriz original, tomando o pivot dado
mat4 mat4::rotate(mat4 original, float theta, vec3 pivot){
    float m[] = {cos(theta), sin(theta), 0.0, 0.0,
                        -sin(theta), cos(theta), 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        pivot.data[0] - pivot.data[0] * cos(theta) + pivot.data[1] * sin(theta),
                        pivot.data[1] - pivot.data[1] * cos(theta) - pivot.data[0] * sin(theta),
                        0.0, 1.0};
    return multiply(original, mat4(m));
}

// Aplica a funcao de escala na matriz original, com valores dados em amount
mat4 mat4::scale(mat4 original, vec3 amount){
    float m[] = {amount.data[0], 0.0, 0.0, 0.0,
                        0.0, amount.data[1], 0.0, 0.0,
                        0.0, 0.0, amount.data[2], 0.0,
                        0.0, 0.0, 0.0, 1.0};
    return multiply(original, mat4(m));
}

// Aplica a funcao de escala na matriz original, com valores dados em amount e o pivot fornecido
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

    float lastTime = (float)glfwGetTime(); // Tempo do ultimo frame
    float thisTime = (float)glfwGetTime(); // Tempo do frame atual

    float rotAmount = 0.0f; // Angulo de rotacao atual
    float vel = 1.0f; // velocidade de rotacao atual

    bool rotating = true; // Flag para ver se esta rodando

    vec3 position; // Posicao atual

    while (!glfwWindowShouldClose(_window)) {

        float deltaTime = thisTime - lastTime; // Calcula o tempo percorrido entre os frames anterior e atual
      // Comandos de entrada
      processInput();

      // Comandos de renderizacao vao aqui
      glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      // etc...

      mat4 transform = mat4(1.0f); // Matriz identidade para transformacao

        // Verifica se a tecla W foi apertada para movimentar-se para cima
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
            position = position + vec3(0.0, 1.0) * deltaTime;

        // Verifica se a tecla S foi apertada para movimentar-se para baixo
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
            position = position + vec3(0.0, -1.0) * deltaTime;

        // Verifica se a tecla A foi apertada para movimentar-se para a esquerda
        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
            position = position + vec3(-1.0, 0.0) * deltaTime;

        // Verifica se a tecla W foi apertada para movimentar-se para a direita
        if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
            position = position + vec3(1.0, 0.0) * deltaTime;

        // Verifica se a barra de espaço foi apertada para controlar a rotação
        if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
            rotating = !rotating;

        // Apenas verificara a rotacao se a flag estiver ativada
        if (rotating){

            // Verifica se a tecla E foi apertada para aumentar a velocidade de rotacao
            if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
                vel += 0.1;

            // Verifica se a tecla Q foi apertada para diminuir a velocidade de rotacao
            if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
                vel -= 0.1;

            // Atualiza a rotacao atual baseado na velocidade
            rotAmount += vel * deltaTime;
        }

        // Aplica a translacao e a rotacao no objeto baseado no vetor de posicao e no valor de rotacao atual
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
