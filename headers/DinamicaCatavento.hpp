#ifndef _DINAMICACATAVENTO_HPP__
#define _DINAMICACATAVENTO_HPP__

#include "cg_window.hpp"
#include "transformations.hpp"
#include <vector>


class DinamicaCatavento : public cgicmc::Window {

protected:

  	std::vector<float> _vertices;
  	const char *_vertexShader;
  	int shaderProgramId;
  	unsigned int _VBO, _VAO;

public:

	DinamicaCatavento();
  	void run() override;
  	void prepare();
  	unsigned int loadVertexShader();
  	unsigned int loadFragmentShader(); 
  	void loadShaders();

};

#endif