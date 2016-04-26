#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <OpenGL/gl.h>
#include "shader.h"

using namespace std;

//string projectPath = "/Users/islamaliev/dev/testing/cpp/game/game/";
extern string projectPath;

vector<GLuint> shaders;

GLint Result;
int InfoLogLength;

void _linkProgram(GLuint ProgramID);

void _checkProgram(GLuint ProgramID);

void _cleanUp();

string _getShaderCode(const char *file_path);

void _compileShader(string &shaderCode, GLuint &shaderID);

void _checkShader(GLuint &shaderID);

void _getShader(GLenum type, const char *file_path);

GLuint getProgram();

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path, const char *geometry_file_path) {
    Result = GL_FALSE;

    _getShader(GL_VERTEX_SHADER, vertex_file_path);
    _getShader(GL_FRAGMENT_SHADER, fragment_file_path);

    if (geometry_file_path != NULL) {
        _getShader(GL_GEOMETRY_SHADER_EXT, vertex_file_path);
    }

    return getProgram();
}

GLuint getProgram() {
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    _linkProgram(ProgramID);
    _checkProgram(ProgramID);
    _cleanUp();
    return ProgramID;
}

void _getShader(GLenum type, const char *file_path) {
    GLuint shaderID = glCreateShader(type);
    std::string shaderCode = _getShaderCode(file_path);

    printf("Compiling shader : %s\n", file_path);
    _compileShader(shaderCode, shaderID);

    _checkShader(shaderID);

    shaders.push_back(shaderID);
}

void _checkShader(GLuint &shaderID) {
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }
}

void _compileShader(string &shaderCode, GLuint &shaderID) {
    char const *sourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, NULL);
    glCompileShader(shaderID);
}

string _getShaderCode(const char *file_path) {
    std::string shaderCode;
    std::ifstream VertexShaderStream(projectPath + file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            shaderCode += "\n" + Line;
        VertexShaderStream.close();
    } else {
        printf("Impossible to open %s in %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file_path, projectPath.c_str());
        getchar();
        return 0;
    }
    return shaderCode;
}

void _cleanUp() {
    const unsigned long size = shaders.size();
    for (int i = size - 1; i >= 0; i--) {
        glDeleteShader(shaders[i]);
        shaders.pop_back();
    }
}

void _checkProgram(GLuint ProgramID) {
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
}

void _linkProgram(GLuint ProgramID) {
    const unsigned long size = shaders.size();
    for (int i = 0; i < size; i++) {
        glAttachShader(ProgramID, shaders[i]);
    }
    glLinkProgram(ProgramID);
}
