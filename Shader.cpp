#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		std::stringstream vertexStream, fragmentStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
	}
	
	const char* vertexCodeChar = vertexCode.c_str();
	const char* fragmentCodeChar = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCodeChar, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCodeChar, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(m_ID);
}

void Shader::setUniform(const std::string& name, bool value1)
{
	int uniformLocation = glGetUniformLocation(m_ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR:SHADER::PROGRAM::UNIFORM_NOT_FOUND\n" << name << '\n';
	}
	glUniform1i(uniformLocation, (int)value1);
}

void Shader::setUniform(const std::string& name, int value1)
{
	int uniformLocation = glGetUniformLocation(m_ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR:SHADER::PROGRAM::UNIFORM_NOT_FOUND\n" << name << '\n';
	}
	glUniform1i(uniformLocation, value1);
}

void Shader::setUniform(const std::string& name, float value1)
{
	int uniformLocation = glGetUniformLocation(m_ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR:SHADER::PROGRAM::UNIFORM_NOT_FOUND\n" << name << '\n';
	}
	glUniform1f(uniformLocation, value1);
}

void Shader::setUniform(const std::string& name, float value1, float value2)
{
	int uniformLocation = glGetUniformLocation(m_ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR:SHADER::PROGRAM::UNIFORM_NOT_FOUND\n" << name << '\n';
	}
	glUniform2f(uniformLocation, value1, value2);
}

void Shader::setUniform(const std::string& name, float value1, float value2, float value3)
{
	int uniformLocation = glGetUniformLocation(m_ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR:SHADER::PROGRAM::UNIFORM_NOT_FOUND\n" << name << '\n';
	}
	glUniform3f(uniformLocation, value1, value2, value3);
}
void Shader::setUniform(const std::string& name, int value1, int value2)
{
	int uniformLocation = glGetUniformLocation(m_ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR:SHADER::PROGRAM::UNIFORM_NOT_FOUND\n" << name << '\n';
	}
	glUniform2i(uniformLocation, value1, value2);
}
void Shader::setUniform(const std::string& name, double value1)
{
	int uniformLocation = glGetUniformLocation(m_ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR:SHADER::PROGRAM::UNIFORM_NOT_FOUND\n" << name << '\n';
	}
	glUniform1d(uniformLocation, value1);
}

void Shader::setUniform(const std::string& name, double value1, double value2)
{
	int uniformLocation = glGetUniformLocation(m_ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR:SHADER::PROGRAM::UNIFORM_NOT_FOUND\n" << name << '\n';
	}
	glUniform2d(uniformLocation, value1, value2);
}

void Shader::setUniform(const std::string& name, double value1, double value2, double value3)
{
	int uniformLocation = glGetUniformLocation(m_ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR:SHADER::PROGRAM::UNIFORM_NOT_FOUND\n" << name << '\n';
	}
	glUniform3d(uniformLocation, value1, value2, value3);
}