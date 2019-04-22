#include "DinamicaCatavento.hpp"


DinamicaCatavento::DinamicaCatavento() : cgicmc::Window() {}

void DinamicaCatavento::run(){

    float lastTime = 0.0; // Tempo do ultimo frame
    float thisTime = (float)glfwGetTime(); // Tempo do frame atual

    float rotAmount = 0.0f; // Angulo de rotacao atual
    float vel = 1.0f; // Velocidade de rotacao atual

    bool rotating = true; // Flag para ver se esta rodando
    bool travado = false; // Variavel necessaria para parar corretamente o catavento

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
        if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS  && travado == false){
            travado = true;
            rotating = !rotating;
        }

        // Verifica se o space nao esta precionado, necessario para poder mudar de estado(parado/girando)
        if (glfwGetKey(_window, GLFW_KEY_SPACE) != GLFW_PRESS  && travado == true)
            travado = false;

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

        // Aplica a rotacao e a translacao no objeto baseado no vetor de posicao e no valor de rotacao atual
        transform = mat4::rotate(transform, rotAmount);
        transform = mat4::translate(transform, position);

     	glUseProgram(shaderProgramId);
     	unsigned int transformLoc = glGetUniformLocation(shaderProgramId, "transform");
      	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform.data);

      	glBindVertexArray(_VAO);
      	glDrawArrays(GL_TRIANGLES, 0, 12); // Desenha os triangulos do catavento
      	// Controla eventos e troca os buffers para renderizacao
      	glfwSwapBuffers(_window);
      	glfwPollEvents();

      	lastTime = thisTime;
      	thisTime = (float)glfwGetTime();
    }
}

// Aloca os valores dos triangulos do catavento
void DinamicaCatavento::prepare() {
    //  Vertices dos triangulos que compoem o catavento
    float array[] = {   0.0f, 0.0f, 0.0f,   0.5f, 0.0f, 0.0f,   0.5f, 0.5f, 0.0,
                        0.0f, 0.0f, 0.0f,   0.0f, 0.5f, 0.0f,   -0.5f, 0.5f, 0.0,
                        0.0f, 0.0f, 0.0f,   -0.5f, 0.0f, 0.0f,   -0.5f, -0.5f, 0.0,
                        0.0f, 0.0f, 0.0f,   0.0f, -0.5f, 0.0f,   0.5f, -0.5f, 0.0};
    _vertices.insert(_vertices.begin(), array, array + 36);

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Carrega o Vertex Shader
unsigned int DinamicaCatavento::loadVertexShader() {
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

// Carrega o Fragment Shader
unsigned int DinamicaCatavento::loadFragmentShader() {
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

// Carrega os shaders e os atribui ao programa
void DinamicaCatavento::loadShaders() {
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
