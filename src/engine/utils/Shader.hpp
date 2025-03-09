#ifndef SHADER_H
#define SHADER_H

#include <cstdlib>
#include <fstream>
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
  public:
	unsigned int ID;

	Shader() {};
	void Compile(const char *vertexShaderPath, const char *fragmentShaderPath) {
		std::string vertexShaderSource;
		std::string fragmentShaderSource;
		std::ifstream vStream;
		std::ifstream fStream;

		// Read vertex shader source code from path and store in
		// vertexShaderSource
		vStream.open(vertexShaderPath);
		if (!vStream) {
			std::cerr << "Failed to open vertex shader!" << std::endl;
		}
		std::stringstream vBuffer;
		vBuffer << vStream.rdbuf();

		vertexShaderSource = vBuffer.str();

		vStream.close();

		// Read fragment shader source code from path and store in
		// fragementShaderSource
		fStream.open(fragmentShaderPath);
		if (!fStream) {
			std::cerr << "Failed to open vertex shader!" << std::endl;
		}
		std::stringstream fBuffer;
		fBuffer << fStream.rdbuf();
		fragmentShaderSource = fBuffer.str();
		fStream.close();

		const char *vShaderCode = vertexShaderSource.c_str();
		const char *fShaderCode = fragmentShaderSource.c_str();

		// Create Shader Program with sources
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);

		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
					  << infoLog << std::endl;
		}
		// fragment shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);

		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
					  << infoLog << std::endl;
		}

		// link shaders
		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);

		// check for linking errors
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
					  << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	};

	void use() { glUseProgram(ID); };

	void setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setVec2(const std::string &name, glm::vec2 value) const {
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &name, glm::vec3 value) const {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string &name, glm::vec4 value) const {
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setMat4(const std::string &name, glm::mat4 &value) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
						   &value[0][0]);
	}
};

#endif
