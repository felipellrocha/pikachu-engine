#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include "sdl2image.h"

using namespace std;

class Shader {
public:
  unsigned int ID;

  Shader(/*const GLchar* vertexPath, */const GLchar* fragmentPath);

  void use();

  void setBool(const string &name, bool value) const;
  void setInt(const string &name, int value) const;
  void setFloat(const string &name, float value) const;
  //void setTexture(const string &name, SDL_Texture texture) const;
};

#endif
