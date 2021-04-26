#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H
#include <pch.h>

#include <fstream>

static std::string loadShaderFile(std::string path)
{

	std::ifstream input(path);
	std::string output = "";
	for (std::string line; std::getline(input, line);)
	{

		output += line;
		output += "\n";
	}

	return output;
}

class OpenGLShader
{
public:
	OpenGLShader();
	~OpenGLShader(){};
	void loadVertexShaderSource(std::string filePath);
	void loadFragmentShaderSource(std::string filePath);

	unsigned int compileShader(unsigned int type, const std::string &source);
	unsigned int createShader();
	unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);
	std::string getVertexShaderSource();
	std::string getFragmentShaderSource();
	uint32_t getID() { return m_id; }
	void useProgram();

	void uploadUniform3fv(glm::vec3 clr, const char *location_name = "")
	{
		glUniform3fv(glGetUniformLocation(getID(), location_name), 1, glm::value_ptr(clr));
	};

public:
	uint32_t m_id;

private:
	std::string vertexShaderSource;

	std::string fragmentShaderSource;
};

#endif /* OPENGL_SHADER_H */