#include "shader.h"

Shader::Shader(/*const GLchar* vertexPath, */const GLchar* fragmentPath) {
  //string vertexCode;
  string fragmentCode;
  //ifstream vShaderFile;
  ifstream fShaderFile;

  //vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
  fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

  try {
    //vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    //stringstream vShaderStream;
    stringstream fShaderStream;

    //vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    //vShaderFile.close();
    fShaderFile.close();

    //vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch(ifstream::failure e) {
    cout << "ERROR: Shader could not load" << endl;
  }

  //const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  //unsigned int vertex;
  unsigned int fragment;

  int success;

  char infoLog[512];

  // Compiling
  /*
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    cout << "ERROR: Vertex shader compile error\n" << infoLog << endl;
  }
  */

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    cout << "ERROR: Fragment shader compile error\n" << infoLog << endl;
  }

  // Linking
  ID = glCreateProgram();
  //glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);

  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    cout << "ERROR: Linking shaders failed\n" << infoLog << endl;
  }

  //glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() {
  glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
/*void Shader::setTexture(const string &name, SDL_Texture texture) const {
  //glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}*/
